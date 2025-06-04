//**************************************************************************************
// thread1_motor_drive
//
//  Created on: July 24, 2024
//      Author: LeDD
//
//
//**************************************************************************************

//***********************************************************************************************************************
// Include
//***********************************************************************************************************************
#include "appDefines.h"
#include "motor_control.h"
#include "controller_driver.h"
#include <cstdlib>
#include <chrono>
#include <thread>
#include <vector>
#include <numeric>
#include "common_data.h"
//***********************************************************************************************************************
// Global variables
//***********************************************************************************************************************
auto lastActionTime = std::chrono::high_resolution_clock::now();
extern volatile bool           power_interrupt = false;
extern volatile bool           wake_interrupt = false;
extern bool             failedCal;
bool                    initialCompleted = false;
static uint32_t         meter_resolution = 0;
bool                    pwrInt;
double                  signalValadc = 0;               // ADC value
double                  signalVal;
extern int              IntsignalVal = 0;       
int                     cnt = 0;
bool                    flex_sensor;
extern bool             withinRange = 1;                // Within range flag
extern bool             calComplete = 0;                // Calibration complete flag
uint32_t                numberStep;
extern uint32_t         totalSteps;
uint32_t                lb = 5, ub = 200;
extern uint32_t         currPos = 0;
uint32_t                hysteresis = 2;
uint32_t                nextRandNum;
extern uint32_t         newRange = 0;                   // New range of the stepper motor from optical sensor to optical sensor (after cal)
uint32_t                inputVoltRangemV = 460;         // 0 to 460 mV is the input voltage range; Based on max input current of 1 mA
extern uint32_t         actualMeterRangeDeg = 250;      // 0 to 250 degrees is the actual meter range
extern uint32_t         sensorRangeDeg = 316;           // 0 to 316 degrees
double                  scaleDown;                      // Scale down the sensor range to the actual meter range
extern uint16_t         maxSteps = 800;                 // Maximum steps of the stepper motor
uint16_t                elapsedTime = 0;
bool                    sleepState = 0;
bool                    accelerationState = true; 
extern uint8_t          motorStepDelay = 2;
bool                    atTargetLocation = true;      // Flag to check if the motor has stepped out of the initial position
uint8_t                 accelerationTimer = 0;        

// Define the size of the moving average filter
const int filterSize = 5;
std::vector<double> filterBuffer(filterSize, 0.0);
int filterIndex = 0;

// Function prototype for applyMovingAverageFilter
double applyMovingAverageFilter(double newValue);

// Define an enum for motor states
enum MotorState
{
    CW,    // Clockwise
    CCW,   // Counterclockwise
    Still  // No movement
};

// Create a variable to hold the motor state
MotorState motorState = Still;

//***********************************************************************************************************************
// Object
//***********************************************************************************************************************
motorCtrl       motorCtrl;
driverHandler   driver;

using namespace std;

//***********************************************************************************************************************
// thread1_motor_drive_entry
//***********************************************************************************************************************
void thread1_motor_drive_entry(void)
{
    uint32_t status = 0;


    tx_thread_sleep (10);
    status += driver.sdadc_initial();
    tx_thread_sleep (5);
    status += driver.peripheral_initial();
    tx_thread_sleep (5);
    status += driver.dac12_initial();

    if (status != FSP_SUCCESS)
    {
        //Do something

    }
    tx_thread_sleep (5);
    status = driver.dac12_output (AMPLIFIER_VOCM_MV);
    tx_thread_sleep (5);
    R_PORT4->PCNTR1 |= GREEN_LED_P4;

    R_PORT1->PCNTR1 |= MTR_DRV_EN_A_P1;
    R_PORT1->PCNTR1 |= MTR_DRV_EN_B_P1;

    motorCtrl.pwmFrequency(24000);
    motorCtrl.pwmDutyCycle(60);
    motorCtrl.pwmOutputStart();


    tx_thread_sleep (100);

    newRange = motorCtrl.testMeterResolution();

    tx_thread_sleep (10);
    calComplete = 1;

    #ifndef HALF_STEP_MOTOR_CTRL
        maxSteps = 400;
    #endif

    while (1)
    {
        while (!(R_PORT1->PIDR_b.PIDR12))
        {
            //if (sleepState == true && wake_interrupt == true)
            if (wake_interrupt == true)
            {
                wake_interrupt = false;
                accelerationState = false;
                currPos = 0;
                totalSteps = 0;
                calComplete = 0;
                newRange = motorCtrl.testMeterResolution();
                calComplete = 1;
                sleepState = false;
            }
            if(failedCal == true)
            {
                failedCal = false;
                break;
            }
            #ifndef PosLossDevMode
            //Read adc value
            signalValadc = driver.sdadc_read();
            signalVal = signalValadc;
            if(signalVal > 550)
            {
                signalVal = 0;
            }

            //signalVal = applyMovingAverageFilter(signalVal);
            #ifndef FULL_360_OPERATION
                //Rescale value to match stepper scaling (0 to x steps). Based on calibration. ~350 steps
                signalVal = (signalVal * (double)(((double)newRange) / ((double)inputVoltRangemV))) ;

                scaleDown = double(actualMeterRangeDeg) / double(sensorRangeDeg);

                signalVal = (signalVal * scaleDown);
            #else
                //Rescale value to match stepper scaling (0 to x steps depending on stepping mode). Based on calibration. Should be ~350 steps
                signalVal = (signalVal * (double)(((double)maxSteps) / ((double)inputVoltRangemV))) ; 
                if (signalVal > maxSteps)
                {
                    signalVal = maxSteps;
                }
                else if (signalVal <= 2) // round to 0      
                {
                    signalVal = 0;
                }
                
                
            #endif

            //Convert value to integer.
            IntsignalVal = (int) signalVal;
            //Make sure value is always positive
            if (IntsignalVal < 0)
            {
                //IntsignalVal = 0;
                withinRange = 0;
            }
            else if (IntsignalVal > maxSteps)
            {
                withinRange = 0;
            }
            else
            {
                withinRange = 1;
            }
            
            #else

                
                // Check if 250 ms have passed
            if (elapsedTime >= 200) {
                if (elapsedTime >= 4000) {
                    IntsignalVal = 0;
                    // Reset the last action time
                    elapsedTime = 0;
                } else if (elapsedTime >= 3800) {
                    IntsignalVal = maxSteps/8;
                } else if (elapsedTime >= 3600) {
                    IntsignalVal = maxSteps/4;
                } else if (elapsedTime >= 3400) {
                    IntsignalVal = (maxSteps/8) *3;
                } else if (elapsedTime >= 3200) {
                    IntsignalVal = maxSteps/2;
                } else if (elapsedTime >= 3000) {
                    IntsignalVal = (maxSteps/8) *5;
                } else if (elapsedTime >= 2800) {
                    IntsignalVal = (maxSteps/8) *6;
                } else if (elapsedTime >= 2600) {
                    IntsignalVal = (maxSteps/8) *7;
                } else if (elapsedTime >= 2400) {
                    IntsignalVal = maxSteps;
                } else if (elapsedTime >= 2200) {
                    IntsignalVal = (maxSteps/8) *7;
                } else if (elapsedTime >= 2000) {
                    IntsignalVal = (maxSteps/8) *6;
                } else if (elapsedTime >= 1800) {
                    IntsignalVal = (maxSteps/8) *5;
                } else if (elapsedTime >= 1600) {
                    IntsignalVal = maxSteps/2;
                } else if (elapsedTime >= 1400) {
                    IntsignalVal = (maxSteps/8) *3;
                } else if (elapsedTime >= 1200) {
                    IntsignalVal = maxSteps/4;
                } else if (elapsedTime >= 1000) {
                    IntsignalVal = maxSteps/8;
                } else if (elapsedTime >= 800) {
                    IntsignalVal = 0;
                }
                // Update the last action time
            }
            elapsedTime ++;
            motorCtrl.stepDelay (1);
            #endif

                //Only move when a change is greater than 2 steps
            if ((IntsignalVal > currPos) && ((IntsignalVal - currPos) > hysteresis)) // want to Spin CW
            {
                
                if (accelerationState == true)
                {
                    motorStepDelay = 2;
                }
                else if (motorState == CCW)
                {
                    motorStepDelay = 2;
                    accelerationTimer = 0;
                }
                else
                {
                    motorStepDelay = 1;
                }
                
                motorCtrl.spinCW(IntsignalVal - currPos);
                motorState = CW;
                //currPos = IntsignalVal;
                atTargetLocation = false;
            }
                //Only move when a change is greater than 2 steps
            else if ((IntsignalVal < currPos) && ((currPos - IntsignalVal) > hysteresis)) // want to spin CCW
            {
                
                if (accelerationState == true)
                {
                    motorStepDelay = 2;
                }
                else if (motorState == CW)
                {
                    motorStepDelay = 2;
                    accelerationTimer = 0;
                }
                else
                {
                    motorStepDelay = 1;
                }
                
                motorCtrl.spinCCW(currPos - IntsignalVal);
                motorState = CCW;
                //currPos = IntsignalVal;
                atTargetLocation = false;
            } 
            else
            {
                atTargetLocation = true;
                accelerationTimer = 0;
                motorState = Still;
            }

            if(atTargetLocation == false)
            {
                accelerationTimer ++;
            }

            if(accelerationTimer >= 2)
            {
                accelerationState = false;
            }
            else
            {
                accelerationState = true;
            }
            /*
            if (abs(IntsignalVal - (int)currPos) < 5)
            {
                accelerationState = true;
            }
            else
            {
                accelerationState = false;
            }
            */

        }
        if (power_interrupt)
        {
            power_interrupt = false;
            accelerationState = false;
            motorCtrl.spinCCW(currPos);
            currPos = 0;
            sleepState = true;
        }
        tx_thread_sleep (10);
    }
}

//***********************************************************************************************************************
//  applyMovingAverageFilter () Function
//  Parameters: newValue
//  Return: moving average variable
//  Description: Function to apply the moving average filter
//***********************************************************************************************************************
double applyMovingAverageFilter(double newValue) 
{
    // Update the buffer with the new value
    filterBuffer[filterIndex] = newValue;
    filterIndex = (filterIndex + 1) % filterSize;

    // Calculate the average of the values in the buffer
    double sum = std::accumulate(filterBuffer.begin(), filterBuffer.end(), 0.0);
    return sum / filterSize;
}

//***********************************************************************************************************************
//  powerIRQ_callBack () Function
//  Parameters: adc_callback_args_t
//  Return: none
//  Description: Function trigger on the power interrupt event
//***********************************************************************************************************************
void powerIRQ_callBack (external_irq_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);

    bsp_io_level_t level;

    g_ioport.p_api->pinRead(g_ioport.p_ctrl, BSP_IO_PORT_01_PIN_12, &level);


    if(level == BSP_IO_LEVEL_LOW) // Power supply is connected
    {
        wake_interrupt = true;
    }
    else // Power supply is disconnected
    {
        power_interrupt = true;
    }

    
}









/*
 * motor_control.cpp
 *
 *  Created on: Jul 23, 2024
 *      Author: LeDD
 */

//***********************************************************************************************************************
// Include
//***********************************************************************************************************************
#include "motor_control.h"

// Global variable
extern volatile bool           power_interrupt;
extern bool         failedCal = false;
static uint8_t      iStep = 5;
extern uint32_t     totalSteps = 0;
volatile bool       pointerBoundaryDetect = false;
volatile bool       pointerBoundaryDetect_lowerlimit = false;
volatile uint32_t   timeDelay_ms = 0;
extern int          IntsignalVal;
extern bool         withinRange;
extern bool         calComplete;
extern uint32_t     currPos;
extern uint32_t     newRange;  
extern uint32_t     actualMeterRangeDeg;
extern uint32_t     sensorRangeDeg;
bool                steppedOutInitial = false;
extern uint16_t     maxSteps;                 // Maximum steps of the stepper motor
uint32_t            resolutionCount = 0;
extern uint8_t      motorStepDelay;


//***********************************************************************************************************************
//  driveDutyCycle () Function
//  Parameters: uint32_t
//  Return: none
//  Description: Function to set the PWM duty cycle of the motor drive

//***********************************************************************************************************************
void motorCtrl::pwmDutyCycle (uint32_t dutyCycle)
{
    timer_info_t info           = {(timer_direction_t)0, 0, 0};
    uint32_t                    iPeriod;
    uint32_t                    setDutyCycle;

    R_GPT_InfoGet(&timer0_pwm_M1_ctrl, &info);
    iPeriod = info.period_counts;
    setDutyCycle = (uint32_t) ((uint64_t) (iPeriod * dutyCycle) / 100);

    R_GPT_DutyCycleSet(&timer0_pwm_M1_ctrl, setDutyCycle, GPT_IO_PIN_GTIOCA);
    R_GPT_DutyCycleSet(&timer0_pwm_M1_ctrl, setDutyCycle, GPT_IO_PIN_GTIOCB);

    R_GPT_DutyCycleSet(&timer3_pwm_M2_ctrl, setDutyCycle, GPT_IO_PIN_GTIOCA);
    R_GPT_DutyCycleSet(&timer3_pwm_M2_ctrl, setDutyCycle, GPT_IO_PIN_GTIOCB);

}

//***********************************************************************************************************************
//  pwmFrequency () Function
//  Parameters: uint32_t
//  Return: none
//  Description: Function to set the frequency (Hz) of the PWM signal

//***********************************************************************************************************************
void motorCtrl::pwmFrequency (uint32_t freq)
{
    uint32_t timerPeriodCnt;
    timerPeriodCnt = PCLKD_CLOCK/freq;
    R_GPT_PeriodSet(&timer0_pwm_M1_ctrl, timerPeriodCnt);
    R_GPT_PeriodSet(&timer3_pwm_M2_ctrl, timerPeriodCnt);
}

//***********************************************************************************************************************
//  pwmOutputStart () Function
//  Parameters: uint32_t
//  Return: none
//  Description: Function to start the PWM signal
//***********************************************************************************************************************
void motorCtrl::pwmOutputStart (void)
{
    R_GPT_Start (timer0_pwm_M1.p_ctrl);
    R_GPT_Start (timer3_pwm_M2.p_ctrl);
}
//***********************************************************************************************************************
//  spinCW () Function
//  Parameters: uint32_t
//  Return: none
//  Description: The step sequence start 1 step below from last stop.
//               Clockwise spin runs from step 4 to 1 and restarts from step 4 at each new sequence
//***********************************************************************************************************************
void motorCtrl::spinCW (uint32_t numStep)
{
    R_PORT4->PCNTR1 &= ~RED_LED_P4;
    while (numStep)    // Step out of of reflex sensor
    {
        #ifdef HALF_STEP_MOTOR_CTRL
            if (iStep > 1)
                iStep--;
            else
                iStep = 8;
            motorHalfStepCtrl (motorStepSequence_t (iStep));
        #else
            if (iStep > 1)
                iStep--;
            else
                iStep = 4;
            motorStepCtrl (motorStepSequence_t (iStep));
        #endif
 
        numStep--;
        currPos++;
        
        if(numStep < 5)
        {
            stepDelay (2);
        } 
        else
        {
            stepDelay (motorStepDelay);
        }
    }
}

//***********************************************************************************************************************
//  spinCCW () Function
//  Parameters: uint32_t
//  Return: none
//  Description:The step sequence start 1 step above from last stop.
//              Counter Clockwise spin runs from step 1 to 4 and restart at step1 at each new sequence
//***********************************************************************************************************************
void motorCtrl::spinCCW (uint32_t numStep)
{
    R_PORT4->PCNTR1 &= ~RED_LED_P4;
    while (numStep )
    {
        #ifdef HALF_STEP_MOTOR_CTRL
            if (iStep < 8)
                iStep++;
            else
                iStep = 1;
            motorHalfStepCtrl (motorStepSequence_t (iStep));
        #else
            if (iStep < 4)
                iStep++;
            else
                iStep = 1;
            motorStepCtrl (motorStepSequence_t (iStep));
        #endif

        numStep--;
        currPos--;
        if (calComplete == 0)
        {

            stepDelay (MOTOR_STEP_DELAY_CAL);
        }
        else if(numStep < 5)
        {
            stepDelay (2);
        }
        else
        {
            stepDelay (motorStepDelay);
        }

    }

}

//***********************************************************************************************************************
//  checkZero () Function
//  Parameters: none
//  Return: uint32_t
//  Description: Set pointer to zero position.
//***********************************************************************************************************************
uint32_t motorCtrl::setZero (void)
{
    R_PORT4->PCNTR1 &= ~RED_LED_P4;
    while (R_PORT1->PIDR_b.PIDR10 == 0)    // Step out of of reflex sensor if it is
    {
        #ifdef HALF_STEP_MOTOR_CTRL
            if (iStep < 8)
                iStep++;
            else
                iStep = 1;
            motorHalfStepCtrl (motorStepSequence_t (iStep));
        #else
            if (iStep < 4)
                iStep++;
            else
                iStep = 1;
            motorStepCtrl (motorStepSequence_t (iStep));
        #endif
        stepDelay (motorStepDelay);
    }
    while (R_PORT1->PIDR_b.PIDR10 == 1)
    {
        #ifdef HALF_STEP_MOTOR_CTRL
            if (iStep < 8)
                iStep++;
            else
                iStep = 1;
            motorHalfStepCtrl (motorStepSequence_t (iStep));
        #else
            if (iStep < 4)
                iStep++;
            else
                iStep = 1;
            motorStepCtrl (motorStepSequence_t (iStep));
        #endif
        stepDelay (motorStepDelay);
    }

    return 0;
}

//***********************************************************************************************************************
//  checkMax () Function
//  Parameters: none
//  Return: uint32_t
//  Description:Test the Max position of the needle pointer and count the total steps require to run from zero to max
//              position. Needle must be at zero position (using setZero) before running checkMax
//***********************************************************************************************************************
void motorCtrl::setMax (void)
{
    #ifdef HALF_STEP_MOTOR_CTRL
        if (iStep > 1)
            iStep--;
        else
            iStep = 8;
        motorHalfStepCtrl (motorStepSequence_t (iStep));
    #else
        if (iStep > 1)
            iStep--;
        else
            iStep = 4;
        motorStepCtrl (motorStepSequence_t (iStep));
    #endif
    currPos++;

}
//***********************************************************************************************************************
//  checkMin () Function
//  Parameters: none
//  Return: none
//  Description:Test the Min position of the needle pointer 
//***********************************************************************************************************************
uint32_t motorCtrl::setMin (void)
{
    #ifdef HALF_STEP_MOTOR_CTRL
        if (iStep < 8)
            iStep++;
        else
            iStep = 1;
        motorHalfStepCtrl (motorStepSequence_t (iStep));
    #else
        if (iStep < 4)
            iStep++;
        else
            iStep = 1;
        motorStepCtrl (motorStepSequence_t (iStep));
    #endif

    totalSteps++;
    currPos--;


    return totalSteps;

}

//***********************************************************************************************************************
//  checkMeterResolution () Function
//  Parameters: none
//  Return: none
//  Description: Test the total number of steps required to move the needle pointer from zero to max position
//***********************************************************************************************************************
uint32_t motorCtrl::testMeterResolution(void)
{

    steppedOutInitial = true;
    pointerBoundaryDetect = false;
    pointerBoundaryDetect_lowerlimit = false;

    while ((pointerBoundaryDetect == false) && (!power_interrupt)) 
    {
        setMax();
        stepDelay (MOTOR_STEP_DELAY_CAL);
    }
    pointerBoundaryDetect = false;
    pointerBoundaryDetect_lowerlimit = false;

    while ((pointerBoundaryDetect_lowerlimit == false) && (!power_interrupt))
    {
        resolutionCount = setMin();
        stepDelay (MOTOR_STEP_DELAY_CAL);
    }
    pointerBoundaryDetect_lowerlimit = false;
    pointerBoundaryDetect = false;

    if(power_interrupt)
    {
        spinCCW(currPos);
        failedCal = true;
        currPos = 0;
    }
    else
    {
    // Set the correct Zero location for the needle pointer depending on the Operation Mode
        #ifdef FULL_360_OPERATION
            spinCCW((((double)maxSteps - (double)resolutionCount) / 2));
            currPos = 0;
        #else
            #ifndef HALF_STEP_MOTOR_CTRL   
                spinCW((sensorRangeDeg - actualMeterRangeDeg) / 2);
                currPos = 0;
            #else
                spinCW((sensorRangeDeg - actualMeterRangeDeg));
                currPos = 0;
            #endif
        #endif
    }
    return resolutionCount;
}

//***********************************************************************************************************************
//  motorStepCtrl () Function
//  Parameters: none
//  Return: uint32_t
//  Description: full step coil logic control for bi-polar stepper motor.
//***********************************************************************************************************************
void motorCtrl::motorStepCtrl (motorStepSequence_t step)
{
    switch (step)
    {
        case STEP_1:
            R_PORT1->PCNTR3 = MTOR_COIL_CTRL_STEP1;
            break;
        case STEP_2:
            R_PORT1->PCNTR3 = MTOR_COIL_CTRL_STEP2;
            break;
        case STEP_3:
            R_PORT1->PCNTR3 = MTOR_COIL_CTRL_STEP3;
            break;
        case STEP_4:
            R_PORT1->PCNTR3 = MTOR_COIL_CTRL_STEP4;
            break;
    }
}

//***********************************************************************************************************************
//  motorHalfStepCtrl () Function
//  Parameters: none
//  Return: uint32_t
//  Description: Half step coil logic control for bi-polar stepper motor.
//***********************************************************************************************************************
void motorCtrl::motorHalfStepCtrl (motorStepSequence_t step)
{
    switch (step)
    {
        case STEP_1:
            R_PORT1->PCNTR3 = MTOR_COIL_CTRL_STEP1_H;
            break;
        case STEP_2:
            R_PORT1->PCNTR3 = MTOR_COIL_CTRL_STEP2_H;
            break;
        case STEP_3:
            R_PORT1->PCNTR3 = MTOR_COIL_CTRL_STEP3_H;
            break;
        case STEP_4:
            R_PORT1->PCNTR3 = MTOR_COIL_CTRL_STEP4_H;
            break;
        case STEP_5:
            R_PORT1->PCNTR3 = MTOR_COIL_CTRL_STEP5_H;
            break;
        case STEP_6:
            R_PORT1->PCNTR3 = MTOR_COIL_CTRL_STEP6_H;
            break;
        case STEP_7:
            R_PORT1->PCNTR3 = MTOR_COIL_CTRL_STEP7_H;
            break;
        case STEP_8:
            R_PORT1->PCNTR3 = MTOR_COIL_CTRL_STEP8_H;
            break;
    }
}

//***********************************************************************************************************************
//  stepDelay () Function
//  Parameters: uint32_t
//  Return: none
//  Description: Delay using timer6 configure as one-short timer that expires in 1 mili-second.
//***********************************************************************************************************************
void motorCtrl::stepDelay (uint32_t delay_ms)
{
    timeDelay_ms = delay_ms;
    R_GPT6->GTCNT_b.GTCNT = 0;      // reset timer counter
    R_GPT6->GTCR_b.CST = 1;         //start timer6
    while (timeDelay_ms);
    R_GPT6->GTCR_b.CST = 0;  //stop timer6
}

//***********************************************************************************************************************
//  timer6_callBack () Function
//  Parameters: timer_callback_args_t
//  Return: none
//  Description: Timer6 callBack function trigger when the one-short timing is expired
//***********************************************************************************************************************
void timer6_callBack(timer_callback_args_t * p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
    if (timeDelay_ms > 0)
        timeDelay_ms--;
}

//***********************************************************************************************************************
//  pointerIRQ_callBack () Function
//  Parameters: external_irq_callback_args_t
//  Return: none
//  Description: Interrupt IRQ2 callBack function trigger on the LOW input event. The optical sensor when detect. 100% Limit
//***********************************************************************************************************************
void pointerIRQ_callBack (external_irq_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
    if(steppedOutInitial == true)
    {
        pointerBoundaryDetect = true;
        R_PORT4->PCNTR1 |= RED_LED_P4;
        #ifndef FULL_360_OPERATION
            if((calComplete == 1) && (withinRange == 0))
            {
                currPos = newRange;
            }
        #endif
    }
}

//***********************************************************************************************************************
//  pointerIRQ_callBack_2 () Function
//  Parameters: external_irq_callback_args_t
//  Return: none
//  Description: Interrupt IRQ3 callBack function trigger on the LOW input event. The optical sensor when detect. 0% Limit
//***********************************************************************************************************************
void pointerIRQ_callBack_2 (external_irq_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
    if(steppedOutInitial == true)
    {
        pointerBoundaryDetect_lowerlimit = true;
        R_PORT4->PCNTR1 |= RED_LED_P4;
        #ifndef FULL_360_OPERATION
            if((calComplete == 1) && (withinRange == 0))
            {
                currPos = 0;
            }
        #endif
    }
}




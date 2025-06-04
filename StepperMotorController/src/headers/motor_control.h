/*
 * motor_control.h
 *
 *  Created on: Jul 22, 2024
 *      Author: LeDD
 */

#ifndef HEADERS_MOTOR_CONTROL_H_
#define HEADERS_MOTOR_CONTROL_H_

//***********************************************************************************************************************
// Include
//***********************************************************************************************************************
#include "appDefines.h"
#include "controller_driver.h"


//***********************************************************************************************************************
//* Macro definitions
//************************************************************************************************************************
// Using port control register 3 (PCNTR3)
#define MTOR_COIL_CTRL_STEP1    0x00280014  //102 = HIGH, 103 = LOW, 104 = HIGH, 105 = LOW
#define MTOR_COIL_CTRL_STEP2    0x00180024  //102 = HIGH, 103 = LOW, 104 = LOW, 105 = HIGH
#define MTOR_COIL_CTRL_STEP3    0x00140028  //102 = LOW, 103 = HIGH, 104 = LOW, 105 = HIGH
#define MTOR_COIL_CTRL_STEP4    0x00240018  //102 = LOW, 103 = HIGH, 104 = HIGH, 105 = LOW

// Port control register 3 for Half Stepping Sequences 
#define MTOR_COIL_CTRL_STEP1_H  0x00380004  //102 = HIGH, 103 = LOW, 104 = Low, 105 = LOW
#define MTOR_COIL_CTRL_STEP8_H  0x00280014  //102 = HIGH, 103 = LOW, 104 = HIGH, 105 = LOW
#define MTOR_COIL_CTRL_STEP7_H  0x002C0010  //102 = LOW, 103 = LOW, 104 = HIGH, 105 = LOW
#define MTOR_COIL_CTRL_STEP6_H  0x00240018  //102 = LOW, 103 = HIGH, 104 = HIGH, 105 = LOW
#define MTOR_COIL_CTRL_STEP5_H  0x00340008  //102 = LOW, 103 = LOW, 104 = HIGH, 105 = LOW
#define MTOR_COIL_CTRL_STEP4_H  0x00140028  //102 = HIGH, 103 = LOW, 104 = HIGH, 105 = LOW
#define MTOR_COIL_CTRL_STEP3_H  0x001C0020  //102 = HIGH, 103 = LOW, 104 = LOW, 105 = LOW
#define MTOR_COIL_CTRL_STEP2_H  0x00180024  //102 = HIGH, 103 = LOW, 104 = LOW, 105 = HIGH


#define MOTOR_COIL_A_P1         0x00080004  //102 = HIGH, 103 = LOW
#define MOTOR_COIL_NA_P1        0x00040008  //103 = HIGH, 102 = LOW
#define MOTOR_COIL_B_P1         0x00200010  //104 = HIGH, 105 = LOW
#define MOTOR_COIL_NB_P1        0x00100020  //105 = HIGH, 104 = LOW

// Defines weather or not the needle will operate in the full 360 degree rangle or just the 250 degree range
#define FULL_360_OPERATION                  // Full 360 Degree Operation   
#define HALF_STEP_MOTOR_CTRL                // Half Step Motor Control Toggle
//#define PosLossDevMode                    // Manually sets the position of the motor to a certain values. Used for testing purposes only


//***********************************************************************************************************************
//* Type definitions
//************************************************************************************************************************
typedef enum
{
    M_SUUCCESS          = 0,
    M_SPIN_ERR,
    M_SENSOR_ERR,
}motorCtrlError;

typedef enum
{
    FIX_VOLTAGE         = 0,
    PWM                 = 1,
}motorDriveMode_t;

typedef enum
{
    STEP_1              = 1,
    STEP_2              = 2,
    STEP_3              = 3,
    STEP_4              = 4,
    STEP_5              = 5,
    STEP_6              = 6,
    STEP_7              = 7,
    STEP_8              = 8,
}motorStepSequence_t;

//***********************************************************************************************************************
//* Class
//***********************************************************************************************************************
class motorCtrl:public driverHandler
{
    private:
        void motorStepCtrl (motorStepSequence_t step);
        void motorHalfStepCtrl (motorStepSequence_t step);
    public:
        void motorDriveMode (motorDriveMode_t mode);
        void pwmDutyCycle (uint32_t dutyCycle);
        void pwmFrequency (uint32_t freq);
        void pwmOutputStart (void);
        void spinCW (uint32_t numStep);
        void spinCCW (uint32_t numStep);
        uint32_t setZero (void);
        void setMax (void);
        uint32_t setMin (void);
        uint32_t testMeterResolution (void);
        void stepDelay (uint32_t ms);
};

//***********************************************************************************************************************
// Function Prototypes
//***********************************************************************************************************************



#endif /* HEADERS_MOTOR_CONTROL_H_ */






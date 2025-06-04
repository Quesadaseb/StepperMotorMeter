/*
 * appDefines.h
 *
 *  Created on: Jul 18, 2024
 *      Author: LeDD
 */

#ifndef HEADERS_APPDEFINES_H_
#define HEADERS_APPDEFINES_H_

//***********************************************************************************************************************
// Include libraries
//***********************************************************************************************************************
#include <iostream>
#include "r_ioport.h"
#include "bsp_api.h"

//***********************************************************************************************************************
/* Include header threads*/
//***********************************************************************************************************************
#include <thread0_main.h>
#include <thread1_motor_drive.h>
#include <thread2_monitor.h>
#include "hal_data.h"

//***********************************************************************************************************************
/* EXTERN threads*/
//***********************************************************************************************************************
extern TX_THREAD thread0_main;
extern TX_THREAD thread1_motor_drive;
extern TX_THREAD thread2_monitor;


//***********************************************************************************************************************
//* Macro definitions
//***********************************************************************************************************************

// Pin number register PCNTR1
#define PIN00_PCNTR1_REG                (uint32_t) 0x00010000
#define PIN00                           PIN00_PCNTR1_REG
#define PIN01                           (uint32_t)(PIN00_PCNTR1_REG<<1)
#define PIN02                           (uint32_t)(PIN00_PCNTR1_REG<<2)
#define PIN03                           (uint32_t)(PIN00_PCNTR1_REG<<3)
#define PIN04                           (uint32_t)(PIN00_PCNTR1_REG<<4)
#define PIN05                           (uint32_t)(PIN00_PCNTR1_REG<<5)
#define PIN06                           (uint32_t)(PIN00_PCNTR1_REG<<6)
#define PIN07                           (uint32_t)(PIN00_PCNTR1_REG<<7)
#define PIN08                           (uint32_t)(PIN00_PCNTR1_REG<<8)
#define PIN09                           (uint32_t)(PIN00_PCNTR1_REG<<9)
#define PIN10                           (uint32_t)(PIN00_PCNTR1_REG<<10)
#define PIN11                           (uint32_t)(PIN00_PCNTR1_REG<<11)
#define PIN12                           (uint32_t)(PIN00_PCNTR1_REG<<12)
#define PIN13                           (uint32_t)(PIN00_PCNTR1_REG<<13)
#define PIN14                           (uint32_t)(PIN00_PCNTR1_REG<<14)
#define PIN15                           (uint32_t)(PIN00_PCNTR1_REG<<15)

// GPIO pins
#define GREEN_LED_P4                    PIN08
#define RED_LED_P4                      PIN09
#define VMOTOR_EN_P4                    PIN00
#define MTR_DRV_EN_A_P1                 PIN06
#define MTR_DRV_EN_B_P1                 PIN07
#define MTR_CTRL_PWM1_P4                PIN02
#define MTR_CTRL_PWM2_P4                PIN03
#define MTR_CTRL_PWM3_P2                PIN06
#define MTR_CTRL_PWM4_P2                PIN05
#define CHRG_ISET400_P0                 PIN00
#define CHRG_ISET750_P0                 PIN01
#define CHRG_DISABLE_P2                 PIN04
#define CHRG_COMPLETE_P1                PIN11

// ADC 16bit
#define ADC_VREF                        4096.0f         // Value is mV
#define ADC_16_BIT_MAX                  32767           // 16 bit single ended range 0 to 32767
#define ADC_16_BIT_MASK                 0x7fff
#define MOTOR_STEP_DELAY                2               // Control the speed of the motor. Value x 1.5ms
#define MOTOR_STEP_DELAY_CAL            3               // Control the speed of the motor during calibration stage. Value x 1.5ms
#define AMPLIFIER_VOCM_MV               1000.0f         // Set value for differential amplifier VOCM

// Timer Clock
#define PCLKD_CLOCK                     24000000        // Must match with configuration

typedef struct
{
    float    mon_motorCurrA;
    float    mon_motorCurrB;
    float    mon_24V;
    float    mon_5VD;
    float    mon_Vcap;
    float    mon_Vmotor;
}monitor_t;

//***********************************************************************************************************************
// Function Prototypes
//***********************************************************************************************************************
void adc16b_initialize (void);
uint16_t read_ADC16b (void);

#endif /* HEADERS_APPDEFINES_H_ */












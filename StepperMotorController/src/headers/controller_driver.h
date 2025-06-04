/*
 * controller_driver.h
 *
 *  Created on: Jul 29, 2024
 *      Author: LeDD
 */

//***********************************************************************************************************************
// Include
//***********************************************************************************************************************
#include "appDefines.h"

#ifndef HEADERS_CONTROLLER_DRIVER_H_
#define HEADERS_CONTROLLER_DRIVER_H_

#define SDADC_RESOLUTION                (16777216U)                     // 24-bits. Must match with value set in configuration
#define OFFSET_VOLTAGE                  0.2f
#define SDADC_VREF                      2000.0f                         // Full scale range in mV. Must match with value set in configuration
#define VOL_PER_BIT                     SDADC_VREF/SDADC_RESOLUTION
#define SDADC_TOTAL_GAIN                1                               // Must match with value set in configuration
#define AMPLIFIER_GAIN                  2                               // Differential amplifier gain (hardware)
#define SDADC_GAIN_OFFSET               0
#define BUFF_SIZE                       30U
#define MASK                            0x00FFFFFF

// DAC12
#define DAC_MIN_VAL                     1
#define DAC_MAX_VAL                     4095
#define DAC_VREF                        4096.0f                         // Value in mV



//***********************************************************************************************************************
//* Class
//***********************************************************************************************************************
class driverHandler
{
    private:
        double sdadc_decimalToVoltCal (uint32_t decimalVal);
    public:
        uint32_t sdadc_initial (void);
        uint32_t adc16_initial (void);
        uint32_t dac12_initial (void);
        uint32_t peripheral_initial(void);
        double sdadc_read (void);
        uint32_t dac12_output (float outVal);
};


#endif /* HEADERS_CONTROLLER_DRIVER_H_ */

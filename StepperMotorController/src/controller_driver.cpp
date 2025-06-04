/*
 * controller_driver.cpp
 *
 *  Created on: Jul 29, 2024
 *      Author: LeDD
 */

//***********************************************************************************************************************
// Include
//***********************************************************************************************************************
#include "controller_driver.h"


//***********************************************************************************************************************
// Global variables
//***********************************************************************************************************************
volatile bool sdadc_scan_complete = false;
volatile bool sdadc_calib_complete = false;
uint16_t decimalCode;
//**************************************************************************************
//  sdadc_decimalToVoltCal () function
//  Parameter: uint32_t, uint8_t
//  This function calculate the ADC conversion in 2's complement to decimal value
//
//  Input voltage for the SDADC24 according to the SDADC24 manual:
//  A/D conversion result is 2's complement and range from
//  Vin+ < Vin-        Vin+ = Vin-   Vin+ > Vin-
//  -0.8V/(Gtotal)       0V          +0.8V/(Gtotal)
//  0x800000             0x000000    0x7fffff
//  and calculated:
//
//  For Vin+ > Vin-
//                         1.8V        DEC Value
//  Differential Input = ---------- × ------------
//                       ADC_GAIN        2^24
//
//  For Vin+ < Vin-
//
//                                   1.8V        DEC Value
//  (DEC Value - ((2^24)-1 + 1)) x ---------- × ------------
//                                 ADC_GAIN       (2^24)-1
//
//  SDADC_TOTAL_GAIN: This gain must match with value set configuration.
//**************************************************************************************
double driverHandler::sdadc_decimalToVoltCal (uint32_t decimalVal)
{
    double analogVal;
    // Positive number calculation. (in+ > in-)
    analogVal = (double)decimalVal * ((SDADC_VREF / SDADC_TOTAL_GAIN) / SDADC_RESOLUTION);
    return analogVal;
}

//***********************************************************************************************************************
//  sdadcInitial () function
//  Parameter: none
//  Return: uint32_t
//  This function configure the 24-bits differential inputs SDADC:
//  1. Open the module
//  2. Calibration to differential channel 0. Internal calibration is
//     executed during module open in step 1.
//  3. Configure active channel.
//  4. Set the gain offset to channel.
//  Offset value must be between -15 to 15
//  Offset (mV) = 10.9376mV * (offset_step / stage 1 gain)
//  Channel 0 is connecting to 0-1mA signal harness
//***********************************************************************************************************************
uint32_t driverHandler::sdadc_initial(void)
{
    uint32_t status = 0;
    sdadc_calibrate_args_t calibrate_args;

    status += R_SDADC_Open (&sdadc0_ctrl, &sdadc0_cfg);
//    status += R_SDADC_ScanCfg (&sdadc0_ctrl, &sdadc0_cfg);

    calibrate_args.mode = SDADC_CALIBRATION_INTERNAL_GAIN_OFFSET;
    calibrate_args.channel = ADC_CHANNEL_0;

    status += R_SDADC_Calibrate(&sdadc0_ctrl, &calibrate_args);

    while (sdadc_calib_complete == false);           // Allow until ADC calibration complete
    sdadc_calib_complete = false;                    // Reset flag

    status += R_SDADC_OffsetSet (&sdadc0_ctrl, ADC_CHANNEL_0, SDADC_GAIN_OFFSET);

    return status;
}

//***********************************************************************************************************************
//  peripheralInitial () Function
//  Parameters: none
//  Return: none
//  Description: initialize TIMER6 and IRQ2
//***********************************************************************************************************************
uint32_t driverHandler::peripheral_initial (void)
{
    uint32_t status = 0;
    status += R_GPT_Open(timer0_pwm_M1.p_ctrl, timer0_pwm_M1.p_cfg);
    status += R_GPT_Open(timer3_pwm_M2.p_ctrl, timer3_pwm_M2.p_cfg);
    status += R_GPT_Open(timer6.p_ctrl, timer6.p_cfg);
    status += R_ICU_ExternalIrqOpen(&pointer_irq2_ctrl, &pointer_irq2_cfg);
    status += R_ICU_ExternalIrqOpen(&pointer_irq3_ctrl, &pointer_irq3_cfg);
    status += R_ICU_ExternalIrqOpen(&power_irq7_ctrl, &power_irq7_cfg);
    status += R_ICU_ExternalIrqEnable(&pointer_irq2_ctrl);
    status += R_ICU_ExternalIrqEnable(&pointer_irq3_ctrl);
    status += R_ICU_ExternalIrqEnable(&power_irq7_ctrl);
    return status;
}

//***********************************************************************************************************************
//  sdadcInitial () Function
//  Parameters: none
//  Return: uint32_t
//  Description: Configure the SDADC.
//***********************************************************************************************************************
double driverHandler::sdadc_read(void)
{
    uint32_t status;
    uint32_t adc24Bit;
    double analogVal_mV;
    uint32_t timeout_value = UINT32_MAX;

    status = R_SDADC_ScanStart (&sdadc0_ctrl);

    while ((sdadc_scan_complete == false) && (timeout_value > 0));
    sdadc_scan_complete = false;

    if (status == FSP_SUCCESS)
    {
        status = R_SDADC_Read32 (&sdadc0_ctrl, ADC_CHANNEL_0, (uint32_t*)&adc24Bit);
    }
    if (status == FSP_SUCCESS)
    {
        analogVal_mV = sdadc_decimalToVoltCal (adc24Bit)/AMPLIFIER_GAIN;
    }
    return analogVal_mV;
}

//***********************************************************************************************************************
//  sdadcInitial () Function
//  Parameters: none
//  Return: uint32_t
//  Description: Configure the DAC12.
//***********************************************************************************************************************
uint32_t driverHandler::dac12_initial (void)
{
    uint32_t status;
    status = R_DAC_Open (&dac0_ctrl, &dac0_cfg);
    return status;
}

//***********************************************************************************************************************
//  adc12_output () Function
//  Parameters: float
//  Return: uint32_t
//  Description: control the output at DAC121. Value in mV
//                      mV
//  decimal code = --------------- x DAC_MAX_VAL
//                    DAC_VREF
//***********************************************************************************************************************
uint32_t driverHandler::dac12_output (float outPutValmV)
{
    uint32_t status = 0;

    decimalCode = (uint16_t)((outPutValmV / DAC_VREF) * DAC_MAX_VAL);
    status += R_DAC_Write (&dac0_ctrl, decimalCode);
    status += R_DAC_Start (&dac0_ctrl);
    return status;
}

//***********************************************************************************************************************
//  sdadc_callBack () Function
//  Parameters: adc_callback_args_t
//  Return: none
//  Description: the call back is fired on the event of SDADC
//***********************************************************************************************************************
void sdadc_callBack (adc_callback_args_t *p_args)
{

    if (p_args->event == ADC_EVENT_CONVERSION_COMPLETE)
        sdadc_scan_complete = true;
    else if (p_args->event == ADC_EVENT_CALIBRATION_COMPLETE)
        sdadc_calib_complete = true;
}











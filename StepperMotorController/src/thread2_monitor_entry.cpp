//***********************************************************************************************************************
// Include
//***********************************************************************************************************************
#include "appDefines.h"

//***********************************************************************************************************************
// Global variables
//***********************************************************************************************************************
volatile bool       adc16b_conversion_complete = false;
monitor_t           Vmonitor;

using namespace std;
void thread2_monitor_entry(void)
{
    adc16b_initialize ();

    while (1)
    {
        read_ADC16b ();
        tx_thread_sleep (100);
    }
}

//***********************************************************************************************************************
//  adc16b_initialize () Function
//  Parameters: none
//  Return: none
//  Description: Initial ADC 16 bit
//***********************************************************************************************************************
void adc16b_initialize (void)
{
    adc_status_t adc_status;

    R_ADC_Open (&adc0_ctrl, &adc0_cfg);
    // Configure ADC high voltage reference
    // 0 0: AVCC0 is selected as the high-potential reference voltage
    // 0 1: VREFH0 is selected as the high-potential reference voltage
    // 1 0: Internal reference voltage is selected as the high-potential reference voltage
    // 1 1: Internal node discharged (no reference voltage pin is selected).
    R_ADC0->ADHVREFCNT_b.HVSEL = 1;
    // Configure ADC low voltage reference
    // 0: AVSS0 is selected as the low-potential reference voltage
    // 1: VREFL0 is selected as the low-potential reference voltage.
    R_ADC0->ADHVREFCNT_b.LVSEL = 1;

    // Configure ADC conversion mode power
    // 0: High speed A/D conversion
    // 1: Low-power A/D conversion mode
    R_ADC0->ADCSR_b.ADHSC = 0;

    // Configure ADC sampling time (16-bit conversion; ADCLK at High-speed mode)
    // 18 ADCLK clocks per conversion (RA2A1 manual table 32.15)
    R_ADC0->ADSSTRO_b.SST = 18;
    R_ADC0->ADSSTRO_b.SST = 18;

    R_ADC_ScanCfg (&adc0_ctrl, &adc0_channel_cfg);
    R_ADC_Calibrate (&adc0_ctrl, NULL);

    do
    {
        R_ADC_StatusGet (&adc0_ctrl, &adc_status);

    } while (ADC_STATE_IDLE != adc_status.state); //Allow calibration complete.It takes 24msec to 780msec based on clock

}

//***********************************************************************************************************************
//  adc_callBack () Function
//  Parameters: adc_callback_args_t
//  Return: none
//  Description: Function trigger on the ADC16 conversion event
//***********************************************************************************************************************
uint16_t read_ADC16b (void)
{
    uint8_t         adc16b_chan[] = {1, 2, 3, 6, 7, 8};
    uint16_t        adc16bBuffer[6];
    R_ADC_ScanStart (&adc0_ctrl);

    while (!adc16b_conversion_complete)
    {
        /* Wait for conversion to complete */
    }

    /* Reset flag for next conversion */
    adc16b_conversion_complete = false;

    for (uint8_t i = 0; i < 6; i++)
    {
        R_ADC_Read (&adc0_ctrl, adc_channel_t(adc16b_chan[i]), &adc16bBuffer[i]);
//        if (adc16bBuffer[i] > ADC_16_BIT_MAX)
//            adc16bBuffer[i] = 0;
    }
    Vmonitor.mon_motorCurrA = (float)((adc16bBuffer[0] * ADC_VREF)/ADC_16_BIT_MAX);
    Vmonitor.mon_motorCurrB = (float)((adc16bBuffer[1] * ADC_VREF)/ADC_16_BIT_MAX);
    Vmonitor.mon_24V = (float)((adc16bBuffer[2] * ADC_VREF)/ADC_16_BIT_MAX);
    Vmonitor.mon_5VD = (float)((adc16bBuffer[3]* ADC_VREF)/ADC_16_BIT_MAX);
    Vmonitor.mon_Vcap = (float)((adc16bBuffer[4]* ADC_VREF)/ADC_16_BIT_MAX);
    Vmonitor.mon_Vmotor = (float)((adc16bBuffer[5] * ADC_VREF)/ADC_16_BIT_MAX);

    R_ADC_ScanStop(&adc0_ctrl);

    return 0;
}

//***********************************************************************************************************************
//  adc_callBack () Function
//  Parameters: adc_callback_args_t
//  Return: none
//  Description: Function trigger on the ADC16 conversion event
//***********************************************************************************************************************
void adc_callBack (adc_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
    adc16b_conversion_complete = true;
}

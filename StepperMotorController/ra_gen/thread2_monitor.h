/* generated thread header file - do not edit */
#ifndef THREAD2_MONITOR_H_
#define THREAD2_MONITOR_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus
                extern "C" void thread2_monitor_entry(void);
                #else
extern void thread2_monitor_entry(void);
#endif
#include "r_adc.h"
#include "r_adc_api.h"
FSP_HEADER
/** ADC on ADC Instance. */
extern const adc_instance_t adc0;

/** Access the ADC instance using these structures when calling API functions directly (::p_api is not used). */
extern adc_instance_ctrl_t adc0_ctrl;
extern const adc_cfg_t adc0_cfg;
extern const adc_channel_cfg_t adc0_channel_cfg;

#ifndef adc_callBack
void adc_callBack(adc_callback_args_t *p_args);
#endif

#ifndef NULL
#define ADC_DMAC_CHANNELS_PER_BLOCK_NULL  6
#endif
FSP_FOOTER
#endif /* THREAD2_MONITOR_H_ */

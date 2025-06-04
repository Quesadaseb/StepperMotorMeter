/* generated thread header file - do not edit */
#ifndef THREAD1_MOTOR_DRIVE_H_
#define THREAD1_MOTOR_DRIVE_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus
                extern "C" void thread1_motor_drive_entry(void);
                #else
extern void thread1_motor_drive_entry(void);
#endif
#include "r_gpt.h"
#include "r_timer_api.h"
#include "r_sdadc.h"
#include "r_adc_api.h"
FSP_HEADER
/** Timer on GPT Instance. */
extern const timer_instance_t timer3_pwm_M2;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t timer3_pwm_M2_ctrl;
extern const timer_cfg_t timer3_pwm_M2_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t timer0_pwm_M1;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t timer0_pwm_M1_ctrl;
extern const timer_cfg_t timer0_pwm_M1_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
/** ADC on ADC Instance. */
extern const adc_instance_t sdadc0;
extern sdadc_instance_ctrl_t sdadc0_ctrl;
extern const adc_cfg_t sdadc0_cfg;
extern const sdadc_scan_cfg_t sdadc0_channel_cfg;
#ifndef sdadc_callBack
void sdadc_callBack(adc_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t timer6;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t timer6_ctrl;
extern const timer_cfg_t timer6_cfg;

#ifndef timer6_callBack
void timer6_callBack(timer_callback_args_t *p_args);
#endif
FSP_FOOTER
#endif /* THREAD1_MOTOR_DRIVE_H_ */

/* generated thread header file - do not edit */
#ifndef THREAD0_MAIN_H_
#define THREAD0_MAIN_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus
                extern "C" void thread0_main_entry(void);
                #else
extern void thread0_main_entry(void);
#endif
#include "r_dac.h"
#include "r_dac_api.h"
FSP_HEADER
/** DAC on DAC Instance. */
extern const dac_instance_t dac0;

/** Access the DAC instance using these structures when calling API functions directly (::p_api is not used). */
extern dac_instance_ctrl_t dac0_ctrl;
extern const dac_cfg_t dac0_cfg;
FSP_FOOTER
#endif /* THREAD0_MAIN_H_ */

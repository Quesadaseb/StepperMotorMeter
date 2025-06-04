/* generated common header file - do not edit */
#ifndef COMMON_DATA_H_
#define COMMON_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "r_icu.h"
#include "r_external_irq_api.h"
#include "r_ioport.h"
#include "bsp_pin_cfg.h"
FSP_HEADER
/** External IRQ on ICU Instance. */
extern const external_irq_instance_t pointer_irq3;

/** Access the ICU instance using these structures when calling API functions directly (::p_api is not used). */
extern icu_instance_ctrl_t pointer_irq3_ctrl;
extern const external_irq_cfg_t pointer_irq3_cfg;

#ifndef pointerIRQ_callBack_2
void pointerIRQ_callBack_2(external_irq_callback_args_t *p_args);
#endif
/** External IRQ on ICU Instance. */
extern const external_irq_instance_t power_irq7;

/** Access the ICU instance using these structures when calling API functions directly (::p_api is not used). */
extern icu_instance_ctrl_t power_irq7_ctrl;
extern const external_irq_cfg_t power_irq7_cfg;

#ifndef powerIRQ_callBack
void powerIRQ_callBack(external_irq_callback_args_t *p_args);
#endif
/** External IRQ on ICU Instance. */
extern const external_irq_instance_t pointer_irq2;

/** Access the ICU instance using these structures when calling API functions directly (::p_api is not used). */
extern icu_instance_ctrl_t pointer_irq2_ctrl;
extern const external_irq_cfg_t pointer_irq2_cfg;

#ifndef pointerIRQ_callBack
void pointerIRQ_callBack(external_irq_callback_args_t *p_args);
#endif
#define IOPORT_CFG_NAME g_bsp_pin_cfg
#define IOPORT_CFG_OPEN R_IOPORT_Open
#define IOPORT_CFG_CTRL g_ioport_ctrl

/* IOPORT Instance */
extern const ioport_instance_t g_ioport;

/* IOPORT control structure. */
extern ioport_instance_ctrl_t g_ioport_ctrl;
void g_common_init(void);
FSP_FOOTER
#endif /* COMMON_DATA_H_ */

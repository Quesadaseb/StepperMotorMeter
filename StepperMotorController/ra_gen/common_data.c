/* generated common source file - do not edit */
#include "common_data.h"
icu_instance_ctrl_t pointer_irq3_ctrl;
const external_irq_cfg_t pointer_irq3_cfg =
{ .channel = 3, .trigger = EXTERNAL_IRQ_TRIG_FALLING, .filter_enable = true, .clock_source_div =
          EXTERNAL_IRQ_CLOCK_SOURCE_DIV_64,
  .p_callback = pointerIRQ_callBack_2,
  /** If NULL then do not add & */
#if defined(NULL)
    .p_context           = NULL,
#else
  .p_context = &NULL,
#endif
  .p_extend = NULL,
  .ipl = (1),
#if defined(VECTOR_NUMBER_ICU_IRQ3)
    .irq                 = VECTOR_NUMBER_ICU_IRQ3,
#else
  .irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const external_irq_instance_t pointer_irq3 =
{ .p_ctrl = &pointer_irq3_ctrl, .p_cfg = &pointer_irq3_cfg, .p_api = &g_external_irq_on_icu };
icu_instance_ctrl_t power_irq7_ctrl;
const external_irq_cfg_t power_irq7_cfg =
{ .channel = 7, .trigger = EXTERNAL_IRQ_TRIG_BOTH_EDGE, .filter_enable = true, .clock_source_div =
          EXTERNAL_IRQ_CLOCK_SOURCE_DIV_1,
  .p_callback = powerIRQ_callBack,
  /** If NULL then do not add & */
#if defined(NULL)
    .p_context           = NULL,
#else
  .p_context = &NULL,
#endif
  .p_extend = NULL,
  .ipl = (2),
#if defined(VECTOR_NUMBER_ICU_IRQ7)
    .irq                 = VECTOR_NUMBER_ICU_IRQ7,
#else
  .irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const external_irq_instance_t power_irq7 =
{ .p_ctrl = &power_irq7_ctrl, .p_cfg = &power_irq7_cfg, .p_api = &g_external_irq_on_icu };
icu_instance_ctrl_t pointer_irq2_ctrl;
const external_irq_cfg_t pointer_irq2_cfg =
{ .channel = 2, .trigger = EXTERNAL_IRQ_TRIG_FALLING, .filter_enable = true, .clock_source_div =
          EXTERNAL_IRQ_CLOCK_SOURCE_DIV_64,
  .p_callback = pointerIRQ_callBack,
  /** If NULL then do not add & */
#if defined(NULL)
    .p_context           = NULL,
#else
  .p_context = &NULL,
#endif
  .p_extend = NULL,
  .ipl = (1),
#if defined(VECTOR_NUMBER_ICU_IRQ2)
    .irq                 = VECTOR_NUMBER_ICU_IRQ2,
#else
  .irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const external_irq_instance_t pointer_irq2 =
{ .p_ctrl = &pointer_irq2_ctrl, .p_cfg = &pointer_irq2_cfg, .p_api = &g_external_irq_on_icu };
ioport_instance_ctrl_t g_ioport_ctrl;
const ioport_instance_t g_ioport =
{ .p_api = &g_ioport_on_ioport, .p_ctrl = &g_ioport_ctrl, .p_cfg = &g_bsp_pin_cfg, };
void g_common_init(void)
{
}

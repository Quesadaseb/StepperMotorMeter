/* generated thread source file - do not edit */
#include "thread2_monitor.h"

TX_THREAD thread2_monitor;
void thread2_monitor_create(void);
static void thread2_monitor_func(ULONG thread_input);
static uint8_t thread2_monitor_stack[1024] BSP_PLACE_IN_SECTION(".stack.thread2_monitor") BSP_ALIGN_VARIABLE(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
adc_instance_ctrl_t adc0_ctrl;
const adc_extended_cfg_t adc0_cfg_extend =
{ .add_average_count = ADC_ADD_OFF,
  .clearing = ADC_CLEAR_AFTER_READ_ON,
  .trigger = ADC_START_SOURCE_DISABLED,
  .trigger_group_b = ADC_START_SOURCE_DISABLED,
  .double_trigger_mode = ADC_DOUBLE_TRIGGER_DISABLED,
  .adc_vref_control = ADC_VREF_CONTROL_VREFH,
  .enable_adbuf = 0,
#if defined(VECTOR_NUMBER_ADC0_WINDOW_A)
    .window_a_irq        = VECTOR_NUMBER_ADC0_WINDOW_A,
#else
  .window_a_irq = FSP_INVALID_VECTOR,
#endif
  .window_a_ipl = (3),
#if defined(VECTOR_NUMBER_ADC0_WINDOW_B)
    .window_b_irq      = VECTOR_NUMBER_ADC0_WINDOW_B,
#else
  .window_b_irq = FSP_INVALID_VECTOR,
#endif
  .window_b_ipl = (BSP_IRQ_DISABLED), };
const adc_cfg_t adc0_cfg =
{ .unit = 0,
  .mode = ADC_MODE_SINGLE_SCAN,
  .resolution = ADC_RESOLUTION_16_BIT,
  .alignment = (adc_alignment_t) (0),
  .trigger = (adc_trigger_t) 0xF, // Not used
  .p_callback = adc_callBack,
  /** If NULL then do not add & */
#if defined(NULL)
    .p_context           = NULL,
#else
  .p_context = &NULL,
#endif
  .p_extend = &adc0_cfg_extend,
#if defined(VECTOR_NUMBER_ADC0_SCAN_END)
    .scan_end_irq        = VECTOR_NUMBER_ADC0_SCAN_END,
#else
  .scan_end_irq = FSP_INVALID_VECTOR,
#endif
  .scan_end_ipl = (3),
#if defined(VECTOR_NUMBER_ADC0_SCAN_END_B)
    .scan_end_b_irq      = VECTOR_NUMBER_ADC0_SCAN_END_B,
#else
  .scan_end_b_irq = FSP_INVALID_VECTOR,
#endif
  .scan_end_b_ipl = (BSP_IRQ_DISABLED), };
#if ((R_ADC0_ADCMPCR_CMPAE_Msk | R_ADC0_ADCMPCR_CMPAIE_Msk) | (0))
const adc_window_cfg_t adc0_window_cfg =
{
    .compare_mask        = ADC_MASK_CHANNEL_1 |  0,
    .compare_mode_mask   =  0,
    .compare_cfg         = (0) | (R_ADC0_ADCMPCR_CMPAE_Msk | R_ADC0_ADCMPCR_CMPAIE_Msk) | (0) | (ADC_COMPARE_CFG_EVENT_OUTPUT_OR),
    .compare_ref_low     = 0,
    .compare_ref_high    = 4096,
    .compare_b_channel   = (ADC_WINDOW_B_CHANNEL_0),
    .compare_b_mode      = (ADC_WINDOW_B_MODE_LESS_THAN_OR_OUTSIDE),
    .compare_b_ref_low   = 0,
    .compare_b_ref_high  = 0,
};
#endif
const adc_channel_cfg_t adc0_channel_cfg =
{ .scan_mask = ADC_MASK_CHANNEL_1 | ADC_MASK_CHANNEL_2 | ADC_MASK_CHANNEL_3 | ADC_MASK_CHANNEL_6 | ADC_MASK_CHANNEL_7
        | ADC_MASK_CHANNEL_8 | 0,
  .scan_mask_group_b = 0, .priority_group_a = ADC_GROUP_A_PRIORITY_OFF, .add_mask = ADC_MASK_CHANNEL_1
          | ADC_MASK_CHANNEL_2 | ADC_MASK_CHANNEL_3 | ADC_MASK_CHANNEL_6 | ADC_MASK_CHANNEL_7 | ADC_MASK_CHANNEL_8 | 0,
  .sample_hold_mask = 0, .sample_hold_states = 24,
#if ((R_ADC0_ADCMPCR_CMPAE_Msk | R_ADC0_ADCMPCR_CMPAIE_Msk) | (0))
    .p_window_cfg        = (adc_window_cfg_t *) &adc0_window_cfg,
#else
  .p_window_cfg = NULL,
#endif
        };
/* Instance structure to use this module. */
const adc_instance_t adc0 =
{ .p_ctrl = &adc0_ctrl, .p_cfg = &adc0_cfg, .p_channel_cfg = &adc0_channel_cfg, .p_api = &g_adc_on_adc };
extern bool g_fsp_common_initialized;
extern uint32_t g_fsp_common_thread_count;
extern TX_SEMAPHORE g_fsp_common_initialized_semaphore;

void thread2_monitor_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_fsp_common_thread_count++;

    /* Initialize each kernel object. */

    UINT err;
    err = tx_thread_create (&thread2_monitor, (CHAR*) "Monitor Thread", thread2_monitor_func, (ULONG) NULL,
                            &thread2_monitor_stack, 1024, 4, 4, 1, TX_DONT_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&thread2_monitor, 0);
    }
}

static void thread2_monitor_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    FSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */

    /* Enter user code for this thread. */
    thread2_monitor_entry ();
}

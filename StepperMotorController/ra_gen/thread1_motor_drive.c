/* generated thread source file - do not edit */
#include "thread1_motor_drive.h"

/* Macro to tie dynamic ELC link to ADC_TRIGGER_SYNC_ELC option in adc_trigger_t. */
#define ADC_TRIGGER_SDADC0     ADC_TRIGGER_SYNC_ELC
TX_THREAD thread1_motor_drive;
void thread1_motor_drive_create(void);
static void thread1_motor_drive_func(ULONG thread_input);
static uint8_t thread1_motor_drive_stack[1024] BSP_PLACE_IN_SECTION(".stack.thread1_motor_drive") BSP_ALIGN_VARIABLE(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
gpt_instance_ctrl_t timer3_pwm_M2_ctrl;
#if 0
const gpt_extended_pwm_cfg_t timer3_pwm_M2_pwm_extend =
{
    .trough_ipl          = (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_GPT3_COUNTER_UNDERFLOW)
    .trough_irq          = VECTOR_NUMBER_GPT3_COUNTER_UNDERFLOW,
#else
    .trough_irq          = FSP_INVALID_VECTOR,
#endif
    .poeg_link           = GPT_POEG_LINK_POEG0,
    .output_disable      = (gpt_output_disable_t) ( GPT_OUTPUT_DISABLE_NONE),
    .adc_trigger         = (gpt_adc_trigger_t) ( GPT_ADC_TRIGGER_NONE),
    .dead_time_count_up  = 0,
    .dead_time_count_down = 0,
    .adc_a_compare_match = 0,
    .adc_b_compare_match = 0,
    .interrupt_skip_source = GPT_INTERRUPT_SKIP_SOURCE_NONE,
    .interrupt_skip_count  = GPT_INTERRUPT_SKIP_COUNT_0,
    .interrupt_skip_adc    = GPT_INTERRUPT_SKIP_ADC_NONE,
    .gtioca_disable_setting = GPT_GTIOC_DISABLE_PROHIBITED,
    .gtiocb_disable_setting = GPT_GTIOC_DISABLE_PROHIBITED,
};
#endif
const gpt_extended_cfg_t timer3_pwm_M2_extend =
        { .gtioca =
        { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE), .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE), .capture_a_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE), .capture_a_ipl = (BSP_IRQ_DISABLED), .capture_b_ipl =
                  (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_GPT3_CAPTURE_COMPARE_A)
    .capture_a_irq       = VECTOR_NUMBER_GPT3_CAPTURE_COMPARE_A,
#else
          .capture_a_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_GPT3_CAPTURE_COMPARE_B)
    .capture_b_irq       = VECTOR_NUMBER_GPT3_CAPTURE_COMPARE_B,
#else
          .capture_b_irq = FSP_INVALID_VECTOR,
#endif
          .compare_match_value =
          { /* CMP_A */0x0, /* CMP_B */0x0 },
          .compare_match_status = (0U << 1U) | 0U, .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE, .capture_filter_gtiocb =
                  GPT_CAPTURE_FILTER_NONE,
#if 0
    .p_pwm_cfg                   = &timer3_pwm_M2_pwm_extend,
#else
          .p_pwm_cfg = NULL,
#endif
#if 0
    .gtior_setting.gtior_b.gtioa  = (0U << 4U) | (0U << 2U) | (0U << 0U),
    .gtior_setting.gtior_b.oadflt = (uint32_t) GPT_PIN_LEVEL_LOW,
    .gtior_setting.gtior_b.oahld  = 0U,
    .gtior_setting.gtior_b.oae    = (uint32_t) true,
    .gtior_setting.gtior_b.oadf   = (uint32_t) GPT_GTIOC_DISABLE_PROHIBITED,
    .gtior_setting.gtior_b.nfaen  = ((uint32_t) GPT_CAPTURE_FILTER_NONE & 1U),
    .gtior_setting.gtior_b.nfcsa  = ((uint32_t) GPT_CAPTURE_FILTER_NONE >> 1U),
    .gtior_setting.gtior_b.gtiob  = (0U << 4U) | (0U << 2U) | (0U << 0U),
    .gtior_setting.gtior_b.obdflt = (uint32_t) GPT_PIN_LEVEL_LOW,
    .gtior_setting.gtior_b.obhld  = 0U,
    .gtior_setting.gtior_b.obe    = (uint32_t) true,
    .gtior_setting.gtior_b.obdf   = (uint32_t) GPT_GTIOC_DISABLE_PROHIBITED,
    .gtior_setting.gtior_b.nfben  = ((uint32_t) GPT_CAPTURE_FILTER_NONE & 1U),
    .gtior_setting.gtior_b.nfcsb  = ((uint32_t) GPT_CAPTURE_FILTER_NONE >> 1U),
#else
          .gtior_setting.gtior = 0U,
#endif
        };

const timer_cfg_t timer3_pwm_M2_cfg =
{ .mode = TIMER_MODE_PWM,
/* Actual period: 0.000041666666666666665 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x3e8,
  .duty_cycle_counts = 0x1f4, .source_div = (timer_source_div_t) 0, .channel = 3, .p_callback = NULL,
  /** If NULL then do not add & */
#if defined(NULL)
    .p_context           = NULL,
#else
  .p_context = &NULL,
#endif
  .p_extend = &timer3_pwm_M2_extend,
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_GPT3_COUNTER_OVERFLOW)
    .cycle_end_irq       = VECTOR_NUMBER_GPT3_COUNTER_OVERFLOW,
#else
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t timer3_pwm_M2 =
{ .p_ctrl = &timer3_pwm_M2_ctrl, .p_cfg = &timer3_pwm_M2_cfg, .p_api = &g_timer_on_gpt };
gpt_instance_ctrl_t timer0_pwm_M1_ctrl;
#if 0
const gpt_extended_pwm_cfg_t timer0_pwm_M1_pwm_extend =
{
    .trough_ipl          = (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_GPT0_COUNTER_UNDERFLOW)
    .trough_irq          = VECTOR_NUMBER_GPT0_COUNTER_UNDERFLOW,
#else
    .trough_irq          = FSP_INVALID_VECTOR,
#endif
    .poeg_link           = GPT_POEG_LINK_POEG0,
    .output_disable      = (gpt_output_disable_t) ( GPT_OUTPUT_DISABLE_NONE),
    .adc_trigger         = (gpt_adc_trigger_t) ( GPT_ADC_TRIGGER_NONE),
    .dead_time_count_up  = 0,
    .dead_time_count_down = 0,
    .adc_a_compare_match = 0,
    .adc_b_compare_match = 0,
    .interrupt_skip_source = GPT_INTERRUPT_SKIP_SOURCE_NONE,
    .interrupt_skip_count  = GPT_INTERRUPT_SKIP_COUNT_0,
    .interrupt_skip_adc    = GPT_INTERRUPT_SKIP_ADC_NONE,
    .gtioca_disable_setting = GPT_GTIOC_DISABLE_PROHIBITED,
    .gtiocb_disable_setting = GPT_GTIOC_DISABLE_PROHIBITED,
};
#endif
const gpt_extended_cfg_t timer0_pwm_M1_extend =
        { .gtioca =
        { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE), .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE), .capture_a_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE), .capture_a_ipl = (BSP_IRQ_DISABLED), .capture_b_ipl =
                  (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_GPT0_CAPTURE_COMPARE_A)
    .capture_a_irq       = VECTOR_NUMBER_GPT0_CAPTURE_COMPARE_A,
#else
          .capture_a_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_GPT0_CAPTURE_COMPARE_B)
    .capture_b_irq       = VECTOR_NUMBER_GPT0_CAPTURE_COMPARE_B,
#else
          .capture_b_irq = FSP_INVALID_VECTOR,
#endif
          .compare_match_value =
          { /* CMP_A */0x0, /* CMP_B */0x0 },
          .compare_match_status = (0U << 1U) | 0U, .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE, .capture_filter_gtiocb =
                  GPT_CAPTURE_FILTER_NONE,
#if 0
    .p_pwm_cfg                   = &timer0_pwm_M1_pwm_extend,
#else
          .p_pwm_cfg = NULL,
#endif
#if 0
    .gtior_setting.gtior_b.gtioa  = (0U << 4U) | (0U << 2U) | (0U << 0U),
    .gtior_setting.gtior_b.oadflt = (uint32_t) GPT_PIN_LEVEL_LOW,
    .gtior_setting.gtior_b.oahld  = 0U,
    .gtior_setting.gtior_b.oae    = (uint32_t) true,
    .gtior_setting.gtior_b.oadf   = (uint32_t) GPT_GTIOC_DISABLE_PROHIBITED,
    .gtior_setting.gtior_b.nfaen  = ((uint32_t) GPT_CAPTURE_FILTER_NONE & 1U),
    .gtior_setting.gtior_b.nfcsa  = ((uint32_t) GPT_CAPTURE_FILTER_NONE >> 1U),
    .gtior_setting.gtior_b.gtiob  = (0U << 4U) | (0U << 2U) | (0U << 0U),
    .gtior_setting.gtior_b.obdflt = (uint32_t) GPT_PIN_LEVEL_LOW,
    .gtior_setting.gtior_b.obhld  = 0U,
    .gtior_setting.gtior_b.obe    = (uint32_t) true,
    .gtior_setting.gtior_b.obdf   = (uint32_t) GPT_GTIOC_DISABLE_PROHIBITED,
    .gtior_setting.gtior_b.nfben  = ((uint32_t) GPT_CAPTURE_FILTER_NONE & 1U),
    .gtior_setting.gtior_b.nfcsb  = ((uint32_t) GPT_CAPTURE_FILTER_NONE >> 1U),
#else
          .gtior_setting.gtior = 0U,
#endif
        };

const timer_cfg_t timer0_pwm_M1_cfg =
{ .mode = TIMER_MODE_PWM,
/* Actual period: 0.000041666666666666665 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x3e8,
  .duty_cycle_counts = 0x1f4, .source_div = (timer_source_div_t) 0, .channel = 0, .p_callback = NULL,
  /** If NULL then do not add & */
#if defined(NULL)
    .p_context           = NULL,
#else
  .p_context = &NULL,
#endif
  .p_extend = &timer0_pwm_M1_extend,
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_GPT0_COUNTER_OVERFLOW)
    .cycle_end_irq       = VECTOR_NUMBER_GPT0_COUNTER_OVERFLOW,
#else
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t timer0_pwm_M1 =
{ .p_ctrl = &timer0_pwm_M1_ctrl, .p_cfg = &timer0_pwm_M1_cfg, .p_api = &g_timer_on_gpt };
const sdadc_channel_cfg_t g_sdadc_channel_cfg0 =
{ .pgac_setting_b.stage_2_gain = SDADC_CHANNEL_STAGE_2_GAIN_1,
  .pgac_setting_b.stage_1_gain = SDADC_CHANNEL_STAGE_1_GAIN_1,
  .pgac_setting_b.oversampling = SDADC_CHANNEL_OVERSAMPLING_256,
  .pgac_setting_b.polarity = SDADC_CHANNEL_POLARITY_POSITIVE,
  .pgac_setting_b.input = SDADC_CHANNEL_INPUT_DIFFERENTIAL,
  .pgac_setting_b.average = SDADC_CHANNEL_AVERAGE_8,
  .pgac_setting_b.invert = SDADC_CHANNEL_INVERSION_OFF,
  .pgac_setting_b.coefficient_m = 8,
  .pgac_setting_b.coefficient_n = 0,
  .pgac_setting_b.count_formula = SDADC_CHANNEL_COUNT_FORMULA_LINEAR, };
sdadc_instance_ctrl_t sdadc0_ctrl;
const sdadc_extended_cfg_t sdadc0_cfg_extend =
{
#if defined(VECTOR_NUMBER_SDADC0_ADI)
    .conv_end_irq        = VECTOR_NUMBER_SDADC0_ADI,
#else
  .conv_end_irq = FSP_INVALID_VECTOR,
#endif
  .conv_end_ipl = (2),
  .vref_src = SDADC_VREF_SRC_EXTERNAL, .vref_voltage = SDADC_VREF_VOLTAGE_2000_MV,
#define RA_NOT_DEFINED (0xFFFFFFFF)
#if (RA_NOT_DEFINED == 0)
#define SDADC_CHANNEL_MASK_0   (0)
    .p_channel_cfgs[0]       = NULL,
#else
#define SDADC_CHANNEL_MASK_0   (1U << 0)
  .p_channel_cfgs[0] = &g_sdadc_channel_cfg0,
#endif
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
#define SDADC_CHANNEL_MASK_1   (0)
  .p_channel_cfgs[1] = NULL,
#else
#define SDADC_CHANNEL_MASK_1   (1U << 1)
    .p_channel_cfgs[1]       = &g_sdadc_channel_cfg1,
#endif
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
#define SDADC_CHANNEL_MASK_2   (0)
  .p_channel_cfgs[2] = NULL,
#else
#define SDADC_CHANNEL_MASK_2   (1U << 2)
    .p_channel_cfgs[2]       = &g_sdadc_channel_cfg2,
#endif
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
#define SDADC_CHANNEL_MASK_3   (0)
  .p_channel_cfgs[3] = NULL,
#else
#define SDADC_CHANNEL_MASK_3   (1U << 3)
    .p_channel_cfgs[3]       = &g_sdadc_channel_cfg3,
#endif
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
#define SDADC_CHANNEL_MASK_4   (0)
  .p_channel_cfgs[4] = NULL,
#else
#define SDADC_CHANNEL_MASK_4   (1U << 4)
    .p_channel_cfgs[4]       = &g_sdadc_channel_cfg4,
#endif
#undef RA_NOT_DEFINED
        };
#define SDADC_CHANNEL_MASK  (SDADC_CHANNEL_MASK_0 | SDADC_CHANNEL_MASK_1 | SDADC_CHANNEL_MASK_2 | SDADC_CHANNEL_MASK_3 | SDADC_CHANNEL_MASK_4)
const adc_cfg_t sdadc0_cfg =
{ .unit = 0,
  .mode = ADC_MODE_SINGLE_SCAN,
  .resolution = ADC_RESOLUTION_24_BIT,
  .alignment = ADC_ALIGNMENT_RIGHT,
  .trigger = ADC_TRIGGER_SOFTWARE,
#if defined(VECTOR_NUMBER_SDADC0_SCANEND)
    .scan_end_irq        = VECTOR_NUMBER_SDADC0_SCANEND,
#else
  .scan_end_irq = FSP_INVALID_VECTOR,
#endif
  .scan_end_ipl = (2),
#if defined(VECTOR_NUMBER_SDADC0_CALIEND)
    .scan_end_b_irq      = VECTOR_NUMBER_SDADC0_CALIEND,
#else
  .scan_end_b_irq = FSP_INVALID_VECTOR,
#endif
  .scan_end_b_ipl = (2),
  .p_callback = sdadc_callBack,
  .p_context = NULL,
  .p_extend = &sdadc0_cfg_extend, };
const sdadc_scan_cfg_t sdadc0_channel_cfg =
{ .scan_mask = SDADC_CHANNEL_MASK, };
/* Instance structure to use this module. */
const adc_instance_t sdadc0 =
{ .p_ctrl = &sdadc0_ctrl, .p_cfg = &sdadc0_cfg, .p_channel_cfg = &sdadc0_channel_cfg, .p_api = &g_adc_on_sdadc };
gpt_instance_ctrl_t timer6_ctrl;
#if 0
const gpt_extended_pwm_cfg_t timer6_pwm_extend =
{
    .trough_ipl          = (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_GPT6_COUNTER_UNDERFLOW)
    .trough_irq          = VECTOR_NUMBER_GPT6_COUNTER_UNDERFLOW,
#else
    .trough_irq          = FSP_INVALID_VECTOR,
#endif
    .poeg_link           = GPT_POEG_LINK_POEG0,
    .output_disable      = (gpt_output_disable_t) ( GPT_OUTPUT_DISABLE_NONE),
    .adc_trigger         = (gpt_adc_trigger_t) ( GPT_ADC_TRIGGER_NONE),
    .dead_time_count_up  = 0,
    .dead_time_count_down = 0,
    .adc_a_compare_match = 0,
    .adc_b_compare_match = 0,
    .interrupt_skip_source = GPT_INTERRUPT_SKIP_SOURCE_NONE,
    .interrupt_skip_count  = GPT_INTERRUPT_SKIP_COUNT_0,
    .interrupt_skip_adc    = GPT_INTERRUPT_SKIP_ADC_NONE,
    .gtioca_disable_setting = GPT_GTIOC_DISABLE_PROHIBITED,
    .gtiocb_disable_setting = GPT_GTIOC_DISABLE_PROHIBITED,
};
#endif
const gpt_extended_cfg_t timer6_extend =
        { .gtioca =
        { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE), .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE), .capture_a_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE), .capture_a_ipl = (BSP_IRQ_DISABLED), .capture_b_ipl =
                  (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_GPT6_CAPTURE_COMPARE_A)
    .capture_a_irq       = VECTOR_NUMBER_GPT6_CAPTURE_COMPARE_A,
#else
          .capture_a_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_GPT6_CAPTURE_COMPARE_B)
    .capture_b_irq       = VECTOR_NUMBER_GPT6_CAPTURE_COMPARE_B,
#else
          .capture_b_irq = FSP_INVALID_VECTOR,
#endif
          .compare_match_value =
          { /* CMP_A */0x0, /* CMP_B */0x0 },
          .compare_match_status = (0U << 1U) | 0U, .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE, .capture_filter_gtiocb =
                  GPT_CAPTURE_FILTER_NONE,
#if 0
    .p_pwm_cfg                   = &timer6_pwm_extend,
#else
          .p_pwm_cfg = NULL,
#endif
#if 0
    .gtior_setting.gtior_b.gtioa  = (0U << 4U) | (0U << 2U) | (0U << 0U),
    .gtior_setting.gtior_b.oadflt = (uint32_t) GPT_PIN_LEVEL_LOW,
    .gtior_setting.gtior_b.oahld  = 0U,
    .gtior_setting.gtior_b.oae    = (uint32_t) false,
    .gtior_setting.gtior_b.oadf   = (uint32_t) GPT_GTIOC_DISABLE_PROHIBITED,
    .gtior_setting.gtior_b.nfaen  = ((uint32_t) GPT_CAPTURE_FILTER_NONE & 1U),
    .gtior_setting.gtior_b.nfcsa  = ((uint32_t) GPT_CAPTURE_FILTER_NONE >> 1U),
    .gtior_setting.gtior_b.gtiob  = (0U << 4U) | (0U << 2U) | (0U << 0U),
    .gtior_setting.gtior_b.obdflt = (uint32_t) GPT_PIN_LEVEL_LOW,
    .gtior_setting.gtior_b.obhld  = 0U,
    .gtior_setting.gtior_b.obe    = (uint32_t) false,
    .gtior_setting.gtior_b.obdf   = (uint32_t) GPT_GTIOC_DISABLE_PROHIBITED,
    .gtior_setting.gtior_b.nfben  = ((uint32_t) GPT_CAPTURE_FILTER_NONE & 1U),
    .gtior_setting.gtior_b.nfcsb  = ((uint32_t) GPT_CAPTURE_FILTER_NONE >> 1U),
#else
          .gtior_setting.gtior = 0U,
#endif
        };

const timer_cfg_t timer6_cfg =
{ .mode = TIMER_MODE_PERIODIC,
/* Actual period: 0.0015 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x8ca0,
  .duty_cycle_counts = 0x4650, .source_div = (timer_source_div_t) 0, .channel = 6, .p_callback = timer6_callBack,
  /** If NULL then do not add & */
#if defined(NULL)
    .p_context           = NULL,
#else
  .p_context = &NULL,
#endif
  .p_extend = &timer6_extend,
  .cycle_end_ipl = (2),
#if defined(VECTOR_NUMBER_GPT6_COUNTER_OVERFLOW)
    .cycle_end_irq       = VECTOR_NUMBER_GPT6_COUNTER_OVERFLOW,
#else
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t timer6 =
{ .p_ctrl = &timer6_ctrl, .p_cfg = &timer6_cfg, .p_api = &g_timer_on_gpt };
extern bool g_fsp_common_initialized;
extern uint32_t g_fsp_common_thread_count;
extern TX_SEMAPHORE g_fsp_common_initialized_semaphore;

void thread1_motor_drive_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_fsp_common_thread_count++;

    /* Initialize each kernel object. */

    UINT err;
    err = tx_thread_create (&thread1_motor_drive, (CHAR*) "Motor Drive Thread", thread1_motor_drive_func, (ULONG) NULL,
                            &thread1_motor_drive_stack, 1024, 3, 3, 1, TX_DONT_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&thread1_motor_drive, 0);
    }
}

static void thread1_motor_drive_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    FSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */

    /* Enter user code for this thread. */
    thread1_motor_drive_entry ();
}

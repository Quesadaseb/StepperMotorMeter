/* generated thread source file - do not edit */
#include "thread0_main.h"

TX_THREAD thread0_main;
void thread0_main_create(void);
static void thread0_main_func(ULONG thread_input);
static uint8_t thread0_main_stack[2048] BSP_PLACE_IN_SECTION(".stack.thread0_main") BSP_ALIGN_VARIABLE(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
dac_instance_ctrl_t dac0_ctrl;
const dac_extended_cfg_t dac0_ext_cfg =
{ .enable_charge_pump = 0,
  .data_format = DAC_DATA_FORMAT_FLUSH_RIGHT,
  .output_amplifier_enabled = 0,
  .internal_output_enabled = false,
  .ref_volt_sel = DAC_VREF_VREFH_VREFL };
const dac_cfg_t dac0_cfg =
{ .channel = 0, .ad_da_synchronized = false, .p_extend = &dac0_ext_cfg };
/* Instance structure to use this module. */
const dac_instance_t dac0 =
{ .p_ctrl = &dac0_ctrl, .p_cfg = &dac0_cfg, .p_api = &g_dac_on_dac };
extern bool g_fsp_common_initialized;
extern uint32_t g_fsp_common_thread_count;
extern TX_SEMAPHORE g_fsp_common_initialized_semaphore;

void thread0_main_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_fsp_common_thread_count++;

    /* Initialize each kernel object. */

    UINT err;
    err = tx_thread_create (&thread0_main, (CHAR*) "Main Thread", thread0_main_func, (ULONG) NULL, &thread0_main_stack,
                            2048, 4, 4, 1, TX_AUTO_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&thread0_main, 0);
    }
}

static void thread0_main_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    FSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */

    /* Enter user code for this thread. */
    thread0_main_entry ();
}

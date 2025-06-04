/* generated vector source file - do not edit */
#include "bsp_api.h"
/* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
#if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = gpt_counter_overflow_isr, /* GPT6 COUNTER OVERFLOW (Overflow) */
            [1] = sdadc_adi_isr, /* SDADC0 ADI (End of SD A/D conversion (type 1)) */
            [2] = sdadc_scanend_isr, /* SDADC0 SCANEND (End of SD A/D scan) */
            [3] = sdadc_caliend_isr, /* SDADC0 CALIEND (End of SD A/D A/D calibration) */
            [4] = r_icu_isr, /* ICU IRQ2 (External pin interrupt 2) */
            [5] = r_icu_isr, /* ICU IRQ7 (External pin interrupt 7) */
            [6] = r_icu_isr, /* ICU IRQ3 (External pin interrupt 3) */
            [7] = adc_scan_end_isr, /* ADC0 SCAN END (End of A/D scanning operation) */
            [8] = adc_window_compare_isr, /* ADC0 WINDOW A (Window A Compare match interrupt) */
        };
        #if BSP_FEATURE_ICU_HAS_IELSR
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] =
        {
            [0] = BSP_PRV_VECT_ENUM(EVENT_GPT6_COUNTER_OVERFLOW,GROUP0), /* GPT6 COUNTER OVERFLOW (Overflow) */
            [1] = BSP_PRV_VECT_ENUM(EVENT_SDADC0_ADI,GROUP1), /* SDADC0 ADI (End of SD A/D conversion (type 1)) */
            [2] = BSP_PRV_VECT_ENUM(EVENT_SDADC0_SCANEND,GROUP2), /* SDADC0 SCANEND (End of SD A/D scan) */
            [3] = BSP_PRV_VECT_ENUM(EVENT_SDADC0_CALIEND,GROUP3), /* SDADC0 CALIEND (End of SD A/D A/D calibration) */
            [4] = BSP_PRV_VECT_ENUM(EVENT_ICU_IRQ2,GROUP4), /* ICU IRQ2 (External pin interrupt 2) */
            [5] = BSP_PRV_VECT_ENUM(EVENT_ICU_IRQ7,GROUP5), /* ICU IRQ7 (External pin interrupt 7) */
            [6] = BSP_PRV_VECT_ENUM(EVENT_ICU_IRQ3,GROUP6), /* ICU IRQ3 (External pin interrupt 3) */
            [7] = BSP_PRV_VECT_ENUM(EVENT_ADC0_SCAN_END,GROUP7), /* ADC0 SCAN END (End of A/D scanning operation) */
            [8] = BSP_PRV_VECT_ENUM(EVENT_ADC0_WINDOW_A,GROUP0), /* ADC0 WINDOW A (Window A Compare match interrupt) */
        };
        #endif
        #endif

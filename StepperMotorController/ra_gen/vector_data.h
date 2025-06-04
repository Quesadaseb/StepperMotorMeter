/* generated vector header file - do not edit */
#ifndef VECTOR_DATA_H
#define VECTOR_DATA_H
#ifdef __cplusplus
        extern "C" {
        #endif
/* Number of interrupts allocated */
#ifndef VECTOR_DATA_IRQ_COUNT
#define VECTOR_DATA_IRQ_COUNT    (9)
#endif
/* ISR prototypes */
void gpt_counter_overflow_isr(void);
void sdadc_adi_isr(void);
void sdadc_scanend_isr(void);
void sdadc_caliend_isr(void);
void r_icu_isr(void);
void adc_scan_end_isr(void);
void adc_window_compare_isr(void);

/* Vector table allocations */
#define VECTOR_NUMBER_GPT6_COUNTER_OVERFLOW ((IRQn_Type) 0) /* GPT6 COUNTER OVERFLOW (Overflow) */
#define GPT6_COUNTER_OVERFLOW_IRQn          ((IRQn_Type) 0) /* GPT6 COUNTER OVERFLOW (Overflow) */
#define VECTOR_NUMBER_SDADC0_ADI ((IRQn_Type) 1) /* SDADC0 ADI (End of SD A/D conversion (type 1)) */
#define SDADC0_ADI_IRQn          ((IRQn_Type) 1) /* SDADC0 ADI (End of SD A/D conversion (type 1)) */
#define VECTOR_NUMBER_SDADC0_SCANEND ((IRQn_Type) 2) /* SDADC0 SCANEND (End of SD A/D scan) */
#define SDADC0_SCANEND_IRQn          ((IRQn_Type) 2) /* SDADC0 SCANEND (End of SD A/D scan) */
#define VECTOR_NUMBER_SDADC0_CALIEND ((IRQn_Type) 3) /* SDADC0 CALIEND (End of SD A/D A/D calibration) */
#define SDADC0_CALIEND_IRQn          ((IRQn_Type) 3) /* SDADC0 CALIEND (End of SD A/D A/D calibration) */
#define VECTOR_NUMBER_ICU_IRQ2 ((IRQn_Type) 4) /* ICU IRQ2 (External pin interrupt 2) */
#define ICU_IRQ2_IRQn          ((IRQn_Type) 4) /* ICU IRQ2 (External pin interrupt 2) */
#define VECTOR_NUMBER_ICU_IRQ7 ((IRQn_Type) 5) /* ICU IRQ7 (External pin interrupt 7) */
#define ICU_IRQ7_IRQn          ((IRQn_Type) 5) /* ICU IRQ7 (External pin interrupt 7) */
#define VECTOR_NUMBER_ICU_IRQ3 ((IRQn_Type) 6) /* ICU IRQ3 (External pin interrupt 3) */
#define ICU_IRQ3_IRQn          ((IRQn_Type) 6) /* ICU IRQ3 (External pin interrupt 3) */
#define VECTOR_NUMBER_ADC0_SCAN_END ((IRQn_Type) 7) /* ADC0 SCAN END (End of A/D scanning operation) */
#define ADC0_SCAN_END_IRQn          ((IRQn_Type) 7) /* ADC0 SCAN END (End of A/D scanning operation) */
#define VECTOR_NUMBER_ADC0_WINDOW_A ((IRQn_Type) 8) /* ADC0 WINDOW A (Window A Compare match interrupt) */
#define ADC0_WINDOW_A_IRQn          ((IRQn_Type) 8) /* ADC0 WINDOW A (Window A Compare match interrupt) */
#ifdef __cplusplus
        }
        #endif
#endif /* VECTOR_DATA_H */

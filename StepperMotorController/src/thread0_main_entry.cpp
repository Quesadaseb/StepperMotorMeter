#include "appDefines.h"

//***********************************************************************************************************************
// Global variables
//***********************************************************************************************************************
bool    capChrgDone = false;
extern  monitor_t        Vmonitor;


using namespace std;
/* Main Thread entry function */
void thread0_main_entry(void)
{

    tx_thread_sleep (10);
    R_PORT4->PCNTR1 |= VMOTOR_EN_P4;
    tx_thread_sleep (10);
    tx_thread_resume (&thread1_motor_drive);
    tx_thread_sleep (3000);
    tx_thread_resume (&thread2_monitor);

    tx_thread_sleep (10);

//    if (R_PORT1->PIDR_b.PIDR12 == 0)            // If power is good
//    {
//        R_PORT2->PCNTR1 &= ~CHRG_DISABLE_P2;    // Capacitor charge enable, active low
//        tx_thread_sleep (100);
//        R_PORT0->PCNTR1 |= CHRG_ISET400_P0;
//        tx_thread_sleep (100);
//        R_PORT0->PCNTR1 |= CHRG_ISET750_P0;
//    }
//    while (R_PORT1->PIDR_b.PIDR11)              // Capacitor is still charging
//    {
//        capChrgDone = !(R_PORT1->PIDR_b.PIDR11);
//        tx_thread_sleep (10);
//    }
    while (1)
    {
        capChrgDone = !(R_PORT1->PIDR_b.PIDR11);
        tx_thread_sleep (10);
    }
}



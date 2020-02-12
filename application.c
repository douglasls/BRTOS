/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

void vApplicationMallocFailedHook( void )
{
    /* Force an assert. */
    configASSERT( ( volatile void * ) NULL );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
    /* Force an assert. */
    configASSERT( ( volatile void * ) NULL );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
    __low_power_mode_3();
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{

}
/*-----------------------------------------------------------*/

void vApplicationSetupTimerInterrupt( void )
{
    WDTCTL = WDTPW | WDTSSEL__ACLK | WDTIS_7 | WDTTMSEL;
    SFRIE1 |= WDTIE;

}
/*-----------------------------------------------------------*/

int _system_pre_init( void )
{
    /* Stop Watchdog timer. */
    WDTCTL = WDTPW | WDTHOLD;

    /* Return 1 for segments to be initialised. */
    return 1;
}


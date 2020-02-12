/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

static void blink( void *pvParameters )
{
    while(1)
    {
        P1OUT ^= BIT0;
        vTaskDelay(250);
    }
}

int main( void )
{

    /* Configure system. */
    WDTCTL = WDTPW | WDTHOLD;
    PM5CTL0 &= ~LOCKLPM5;
    P1DIR |= BIT0;

    /* Create the Task */
    xTaskCreate( blink,                             /* The function that implements the task. */
                "Blink",                            /* The text name assigned to the task - for debug only as it is not used by the kernel. */
                configMINIMAL_STACK_SIZE,           /* The size of the stack to allocate to the task. */
                NULL,                               /* The parameter passed to the task - not used in this case. */
                2,                                  /* The priority assigned to the task. */
                NULL );                             /* The task handle is not required, so NULL is passed. */

    /* Start RTOS */
    vTaskStartScheduler();

}


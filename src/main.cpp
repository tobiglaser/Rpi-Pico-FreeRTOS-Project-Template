#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"



void vTaskCode( void * pvParameters )
{
    /* The parameter value is expected to be 1 as 1 is passed in the
    pvParameters value in the call to xTaskCreate() below. 
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
    */
    stdio_init_all();
    const int LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    for( ;; )
    {
        printf("ON\n");
        gpio_put(LED_PIN, 1);
        vTaskDelay(500);
        printf("OFF\n");
        gpio_put(LED_PIN, 0);
        vTaskDelay(500);
    }
}

int main() {


BaseType_t xReturned;
TaskHandle_t xHandle = NULL;
/* Create the task, storing the handle. */
    xReturned = xTaskCreate(
                    vTaskCode,       /* Function that implements the task. */
                    "Blinky task",   /* Text name for the task. */
                    512,             /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    tskIDLE_PRIORITY,/* Priority at which the task is created. */
                    &xHandle );   

    vTaskStartScheduler();
    while(1)
    {
        configASSERT(0);    /* We should never get here */
    }

}
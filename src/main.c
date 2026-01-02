#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

void led_task(void *pvParameters)
{
    while (1)
    {
        printf("LED Task running\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void logger_task(void *pvParameters)
{
    while (1)
    {
        printf("Logger Task alive\n");
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

int main(void)
{
    xTaskCreate(
        led_task,
        "LED",
        256,
        NULL,
        1,
        NULL);

    xTaskCreate(
        logger_task,
        "LOGGER",
        256,
        NULL,
        2,
        NULL);

    vTaskStartScheduler();

    for (;;)
        ;
}

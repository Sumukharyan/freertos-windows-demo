#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
QueueHandle_t sensorQueue;

void sensor_task(void *pvParameters)
{
    int sensor_value = 0;

    while (1)
    {
        sensor_value++;

        xQueueSend(
            sensorQueue,   // queue handle
            &sensor_value, // address of data
            portMAX_DELAY  // wait until space available
        );

        vTaskDelay(pdMS_TO_TICKS(1000)); // 1 second
    }
}
void logger_task(void *pvParameters)
{
    int received_value;

    while (1)
    {
        if (xQueueReceive(
                sensorQueue,     // queue handle
                &received_value, // where to store data
                portMAX_DELAY    // wait until data arrives
                ) == pdPASS)
        {
            printf("Sensor value received: %d\n", received_value);
        }
    }
}

int main(void)
{
    sensorQueue = xQueueCreate(5, sizeof(int));

    xTaskCreate(sensor_task, "SENSOR", 256, NULL, 2, NULL);
    xTaskCreate(logger_task, "LOGGER", 256, NULL, 1, NULL);

    vTaskStartScheduler();

    while (1)
        ;
}

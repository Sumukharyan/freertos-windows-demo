#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

QueueHandle_t sensorQueue;
SemaphoreHandle_t eventSemaphore;

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
void producer_task(void *pvParameters)
{
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(2000)); // simulate event

        printf("Event occurred! Giving semaphore\n");
        xSemaphoreGive(eventSemaphore);
    }
}
void consumer_task(void *pvParameters)
{
    while (1)
    {
        xSemaphoreTake(
            eventSemaphore,
            portMAX_DELAY);

        printf("Semaphore taken! Handling event\n");
    }
}

int main(void)
{
    sensorQueue = xQueueCreate(5, sizeof(int));
    eventSemaphore = xSemaphoreCreateBinary();

    xTaskCreate(sensor_task, "SENSOR", 256, NULL, 2, NULL);
    xTaskCreate(logger_task, "LOGGER", 256, NULL, 1, NULL);
    xTaskCreate(producer_task, "PRODUCER", 256, NULL, 2, NULL);
    xTaskCreate(consumer_task, "CONSUMER", 256, NULL, 1, NULL);

    vTaskStartScheduler();

    while (1)
        ;
}

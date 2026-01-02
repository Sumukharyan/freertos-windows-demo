#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"

QueueHandle_t sensorQueue;
SemaphoreHandle_t eventSemaphore;
SemaphoreHandle_t uartMutex;
SemaphoreHandle_t isrSemaphore;
TimerHandle_t heartbeatTimer;

void safe_print(const char *msg)
{
    xSemaphoreTake(uartMutex, portMAX_DELAY);
    printf("%s\n", msg);
    xSemaphoreGive(uartMutex);
}
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

void simulated_timer_isr(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    xSemaphoreGiveFromISR(
        isrSemaphore,
        &xHigherPriorityTaskWoken);

    /* Request context switch if needed */
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
void isr_handler_task(void *pvParameters)
{
    while (1)
    {
        xSemaphoreTake(isrSemaphore, portMAX_DELAY);
        printf("ISR event handled in task context\n");
    }
}
void heartbeat_timer_callback(TimerHandle_t xTimer)
{
    /* Do NOT block here */
    safe_print("Heartbeat: system alive");
}

int main(void)
{
    sensorQueue = xQueueCreate(5, sizeof(int));
    eventSemaphore = xSemaphoreCreateBinary();
    uartMutex = xSemaphoreCreateMutex();

    xTaskCreate(sensor_task, "SENSOR", 256, NULL, 2, NULL);
    xTaskCreate(logger_task, "LOGGER", 256, NULL, 1, NULL);
    xTaskCreate(producer_task, "PRODUCER", 256, NULL, 2, NULL);
    xTaskCreate(consumer_task, "CONSUMER", 256, NULL, 1, NULL);
    xTaskCreate(simulated_timer_isr, "ISR_SIM", 256, NULL, 1, NULL);
    xTaskCreate(isr_handler_task, "ISR_HANDLER", 512, NULL, 3, NULL);
    heartbeatTimer = xTimerCreate("HEARTBEAT", pdMS_TO_TICKS(2000), pdTRUE, NULL, heartbeat_timer_callback);

    xTimerStart(heartbeatTimer, 0);
    vTaskStartScheduler();

    while (1)
        ;
}

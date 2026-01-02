#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#define configUSE_PREEMPTION            1
#define configUSE_TIME_SLICING          1
#define configCPU_CLOCK_HZ              ( ( unsigned long ) 1000000 )
#define configTICK_RATE_HZ              ( ( TickType_t ) 1000 )
#define configMAX_PRIORITIES            5
#define configMINIMAL_STACK_SIZE        128
#define configTOTAL_HEAP_SIZE           ( 10240 )

#define configUSE_16_BIT_TICKS          0
#define configUSE_MUTEXES               1
#define configUSE_COUNTING_SEMAPHORES   1

#define INCLUDE_vTaskDelay              1
#define INCLUDE_vTaskDelete             1

#endif

## Day 6

- Implemented multitasking application using FreeRTOS kernel
- Created concurrent tasks with different priorities
- Used FreeRTOS delay and scheduler APIs

## Day 7

- Implemented inter-task communication using FreeRTOS queues
- Designed producer–consumer architecture
- Ensured thread-safe data transfer between tasks

## Day 8: Semaphores & Mutexes (RTOS Synchronization)

- Implemented task synchronization using FreeRTOS binary semaphores
- Designed event-driven signaling between producer and consumer tasks
- Used blocking synchronization (`xSemaphoreTake`) to avoid CPU busy-waiting
- Implemented mutex-based protection for shared resources
- Understood and applied priority inheritance to prevent priority inversion

## Day 9: ISR to Task Communication

- Implemented interrupt-to-task signaling using FreeRTOS ISR-safe APIs
- Used binary semaphore for deferred interrupt processing
- Applied `xSemaphoreGiveFromISR` and context switching from ISR
- Designed ISR logic to be minimal and non-blocking

## Day 10: FreeRTOS Software Timers

- Implemented periodic operations using FreeRTOS software timers
- Used auto-reload timers for heartbeat functionality
- Designed non-blocking timer callbacks executed in Timer Service Task
- Replaced delay-based periodic tasks with event-driven timing

## Day 11: RTOS + MQTT Architecture Design

- Designed RTOS-based MQTT communication architecture
- Separated sensor, networking, and application logic into dedicated tasks
- Used queues for data transfer between real-time tasks and MQTT networking
- Prepared design scalable to embedded targets such as ESP32 and STM32

# HoRTOS
 Custom RTOS on STM32

## Features

Round robin scheduler:
- Priority based scheduling
- Tasks can block
- Tasks can sleep
- Tasks can be stopped or resumed

Semaphores for exclusive access

Sleep task that monitors all sleeping tasks and decrements their sleep timer

Idle task with lowest priority that runs when no other task is active, calculating CPU usage

New Tasks can be easily added to the tasklist.c task table that should be run

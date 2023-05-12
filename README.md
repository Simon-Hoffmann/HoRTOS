# HoRTOS
 Custom RTOS on STM32

## Features

1. Round robin scheduler:
  - Priority based scheduling
  - Tasks can block
  - Tasks can sleep
  - Tasks can be stopped or resumed

2. Semaphores for exclusive access

3. Sleep task that monitors all sleeping tasks and decrements their sleep timer

4. Idle task with lowest priority that runs when no other task is active, calculating CPU usage

5. New Tasks can be easily added to the tasklist.c task table that should be run

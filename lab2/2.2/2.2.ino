#include <Arduino.h>
#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "task4.h"
#include "taskIdle.h"
#include <Arduino_FreeRTOS.h>

#define STACK_SIZE 128
#define TASK1_PRIORITY 2
#define TASK2_PRIORITY 1
#define TASK3_PRIORITY 2
#define TASK4_PRIORITY 1
#define TASK_IDLE_PRIORITY 0

#define REC1 2
#define REC2 1
#define REC3 4
#define REC4 3
#define REC_IDLE 1

#define OFFSET1 2
#define OFFSET2 2
#define OFFSET3 4
#define OFFSET4 6
#define OFFSET_IDLE 1

int recCounter1 = OFFSET1;
int recCounter2 = OFFSET2;
int recCounter3 = OFFSET3;
int recCounter4 = OFFSET4;
int recCounterIdle = OFFSET_IDLE;

void setup() {
  task1Setup(recCounter1, REC1);
  task2Setup(recCounter2, REC2);
  task3Setup(recCounter3, REC3);
  task4Setup(recCounter3, REC4);
  taskIdleSetup(recCounterIdle, REC_IDLE);

  xTaskCreate(
    task1Loop
    ,  "ToggleLED"
    ,  STACK_SIZE 
    ,  NULL
    ,  TASK1_PRIORITY 
    ,  NULL );

    xTaskCreate(
    task2Loop
    ,  "BlinkLED"
    ,  STACK_SIZE
    ,  NULL
    ,  TASK2_PRIORITY
    ,  NULL );

    xTaskCreate(
    task3Loop
    ,  "ButtonBlink"
    ,  STACK_SIZE  
    ,  NULL
    ,  TASK3_PRIORITY
    ,  NULL );

    xTaskCreate(
    task4Loop
    ,  "WarningButton"
    ,  STACK_SIZE  
    ,  NULL
    ,  TASK4_PRIORITY
    ,  NULL );

    xTaskCreate(
    taskIdleLoop
    ,  "Idle"   
    ,  STACK_SIZE
    ,  NULL
    ,  TASK_IDLE_PRIORITY
    ,  NULL );
  
}

void loop() {
    vTaskStartScheduler();
}
#include <Arduino.h>
#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "taskIdle.h"
#include <Arduino_FreeRTOS.h>

#define REC1 2
#define REC2 1
#define REC3 4
#define REC_IDLE 1

#define OFFSET1 2
#define OFFSET2 2
#define OFFSET3 4
#define OFFSET_IDLE 1

int recCounter1 = OFFSET1;
int recCounter2 = OFFSET2;
int recCounter3 = OFFSET3;
int recCounterIdle = OFFSET_IDLE;

void setup() {
  task1Setup(recCounter1, REC1);
  task2Setup(recCounter2, REC2);
  task3Setup(recCounter3, REC3);
  taskIdleSetup(recCounterIdle, REC_IDLE);

  xTaskCreate(
    task1Loop
    ,  "ToggleLED"
    ,  128
    ,  NULL
    ,  2
    ,  NULL );

    xTaskCreate(
    task2Loop
    ,  "BlinkLED"
    ,  128
    ,  NULL
    ,  1
    ,  NULL );

    xTaskCreate(
    task3Loop
    ,  "BlinkFrequency"
    ,  128  
    ,  NULL
    ,  2
    ,  NULL );

    xTaskCreate(
    taskIdleLoop
    ,  "Idle"   
    ,  128
    ,  NULL
    ,  0
    ,  NULL );
}

void loop() {
    vTaskStartScheduler();
}
#include <Arduino.h>
#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "taskIdle.h"

void setup() {
    task1Setup();
    task2Setup();
    task3Setup();
    taskIdleSetup();
}

void loop() {
    task1Loop();
    task2Loop();
    task3Loop();
    taskIdleLoop();
}
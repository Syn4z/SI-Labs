#include <Arduino.h>
#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "taskIdle.h"
#include <timer-api.h>

#define REC1 2
#define REC2 1
#define REC3 4

#define OFFSET1 2
#define OFFSET2 0
#define OFFSET3 4

int recCounter1 = OFFSET1;
int recCounter2 = OFFSET2;
int recCounter3 = OFFSET3;

void setup() {
    task1Setup();
    task2Setup();
    task3Setup();
    taskIdleSetup();

    timer_init_ISR_1KHz(TIMER_DEFAULT);
}

void loop() {
    taskIdleLoop();
}

void timer_handle_interrupts(int timer) {
    if (--recCounter1 <= 0) {
        task1Loop();
        recCounter1 = REC1;
    }

    if (--recCounter2 <= 0) {
        task2Loop();
        recCounter2 = REC2;
    }

    if (--recCounter3 <= 0) {
        task3Loop();
        recCounter3 = REC3;
    }
}
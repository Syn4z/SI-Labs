#include "task4.h"
#include <Arduino.h>

int task4Offset;
int task4Rec;

void task4Setup(int offset, int rec) {
    task4Offset = offset;
    task4Rec = rec;
    pinMode(LED_WARNING_PORT, OUTPUT);
}

void task4Loop(void *pvParameters) {
    (void) pvParameters;

    vTaskDelay(task4Offset);
    for (;;) {
      if (blinkInterval == 200) {
          ledWarningState = !ledWarningState;
          delay(DELAY_PERIOD);
      }

      digitalWrite(LED_WARNING_PORT, ledWarningState);
      vTaskDelay(task4Rec);
    }
}
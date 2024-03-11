#include "task2.h"
#include <Arduino.h>

int task2Offset;
int task2Rec;

void task2Setup(int offset, int rec) {
    task2Offset = offset;
    task2Rec = rec;
    pinMode(LED2_PORT, OUTPUT);
}

void task2Loop(void *pvParameters) {
    (void) pvParameters;

    vTaskDelay(task2Offset);
    for (;;) {
      int currentMillis = millis();

      if (!ledState) {
          if (currentMillis - previousMillis >= blinkInterval) {
              previousMillis = currentMillis;

              digitalWrite(LED2_PORT, !digitalRead(LED2_PORT));
          }
      } else {
          digitalWrite(LED2_PORT, LOW);
      }
      vTaskDelay(task2Rec);
    }
}
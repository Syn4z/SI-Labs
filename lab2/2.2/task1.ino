#include "task1.h"
#include <Arduino.h>

bool previousButtonState = LOW;
int task1Offset;
int task1Rec;

void task1Setup(int offset, int rec) {
    task1Offset = offset;
    task1Rec = rec;
    pinMode(LED1_PORT, OUTPUT);
    pinMode(BUTTON1_PORT, INPUT);
}

void task1Loop(void *pvParameters) {
    (void) pvParameters;

    vTaskDelay(task1Offset);
    for (;;) {
      buttonState = digitalRead(BUTTON1_PORT);    

      if (buttonState == HIGH && previousButtonState == LOW) {
          ledState = !ledState;
          delay(DELAY_PERIOD);
      }

      digitalWrite(LED1_PORT, ledState);
      previousButtonState = buttonState;
      vTaskDelay(task1Rec);
    }
}
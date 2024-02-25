#include "task1.h"
#include <Arduino.h>

bool previousButtonState = LOW;

void task1Setup() {
    pinMode(LED1_PORT, OUTPUT);
    pinMode(BUTTON1_PORT, INPUT);
}

void task1Loop() {
    buttonState = digitalRead(BUTTON1_PORT);

    if (buttonState == HIGH && previousButtonState == LOW) {
        ledState = !ledState;
        delay(200);
    }

    digitalWrite(LED1_PORT, ledState);
    previousButtonState = buttonState;
}
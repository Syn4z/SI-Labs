#include "task2.h"
#include <Arduino.h>

void task2Setup() {
    pinMode(LED2_PORT, OUTPUT);
}

void task2Loop() {
    int currentMillis = millis();

    if (!ledState) {
        if (currentMillis - previousMillis >= blinkInterval) {
            previousMillis = currentMillis;

            digitalWrite(LED2_PORT, !digitalRead(LED2_PORT));
        }
    } else {
        digitalWrite(LED2_PORT, LOW);
    }
}
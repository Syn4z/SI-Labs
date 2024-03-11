#include "taskIdle.h"
#include <Arduino.h>

void taskIdleSetup() {
    Serial.begin(BAUD_RATE);
}

void taskIdleLoop() {
    if (previousLedState != ledState) {
        Serial.print("LED State changed to: ");
        Serial.println(ledState);
        previousLedState = ledState;
    }

    if (previousButton2StateIdle != button2State) {
        if (button2State == HIGH) {
            Serial.println("Button 2 pressed!");
        }
        previousButton2StateIdle = button2State;
    }

    if (previousButton3StateIdle != button3State) {
        if (button3State == HIGH) {
            Serial.println("Button 3 pressed!");
        }
        previousButton3StateIdle = button3State;
    }

    if (previousBlinkInterval != blinkInterval) {
        Serial.print("Blink recurency changed to: ");
        Serial.println(blinkInterval);
        previousBlinkInterval = blinkInterval;
    }

}
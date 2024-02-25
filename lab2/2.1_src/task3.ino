#include "task3.h"
#include <Arduino.h>

void task3Setup(){
    pinMode(BUTTON2_PORT, INPUT);
    pinMode(BUTTON3_PORT, INPUT);
}

void task3Loop(){
        button2State = digitalRead(BUTTON2_PORT);
        button3State = digitalRead(BUTTON3_PORT);

        if (button2State == HIGH && previousButton2State == LOW){
            incrementBlinkValue();
            delay(200);
        }

        previousButton2State = button2State;

        if (button3State == HIGH && previousButton3State == LOW){
            decrementBlinkValue();
            delay(200);
        }

        previousButton3State = button3State;

}

void incrementBlinkValue(){
    if (blinkInterval < maxBlinkValue){
      blinkInterval += 100;
    }
}

void decrementBlinkValue(){
    if (blinkInterval > minBlinkValue){ 
      blinkInterval -= 100;
    }
}
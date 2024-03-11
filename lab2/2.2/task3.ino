#include "task3.h"
#include <Arduino.h>

int task3Offset;
int task3Rec;

void task3Setup(int offset, int rec){
    task3Offset = offset;
    task3Rec = rec;
    pinMode(BUTTON2_PORT, INPUT);
    pinMode(BUTTON3_PORT, INPUT);
}

void task3Loop(void *pvParameters){
    (void) pvParameters;

    vTaskDelay(task3Offset);
    for (;;) {
          button2State = digitalRead(BUTTON2_PORT);
          button3State = digitalRead(BUTTON3_PORT);

      if (button2State == HIGH && previousButton2State == LOW){
          incrementBlinkValue();
          delay(DELAY_PERIOD);
      }

      previousButton2State = button2State;

      if (button3State == HIGH && previousButton3State == LOW){
          decrementBlinkValue();
          delay(DELAY_PERIOD);
      }

      previousButton3State = button3State;
      vTaskDelay(task3Rec);
    }
}

void incrementBlinkValue(){
    if (blinkInterval < maxBlinkValue){
      blinkInterval += blinkIntervalStep;
    }
}

void decrementBlinkValue(){
    if (blinkInterval > minBlinkValue){ 
      blinkInterval -= blinkIntervalStep;
    }
}
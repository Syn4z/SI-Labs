#ifndef task3_h
#define task3_h

#define BUTTON2_PORT 3
#define BUTTON3_PORT 4
#define DELAY_PERIOD 0

int previousButton2State = LOW; 
int previousButton3State = LOW;
int button2State = LOW;
int button3State = LOW;
int maxBlinkValue = 3000;
int minBlinkValue = 200;
int blinkIntervalStep = 100;

void task3Setup(int offset, int rec);
void task3Loop(void *pvParameters);
void incrementBlinkValue();
void decrementBlinkValue();

#endif
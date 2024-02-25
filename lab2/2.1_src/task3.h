#ifndef task3_h
#define task3_h

#define BUTTON2_PORT 3
#define BUTTON3_PORT 4

int previousButton2State = LOW; 
int previousButton3State = LOW;
int button2State = LOW;
int button3State = LOW;
int maxBlinkValue = 5000;
int minBlinkValue = 200;

void task3Setup();
void task3Loop();
void incrementBlinkValue();
void decrementBlinkValue();

#endif
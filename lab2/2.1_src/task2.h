#ifndef task2_h
#define task2_h

#define LED2_PORT 8

int previousMillis = 0;
extern int blinkInterval = 1000;

void task2Setup();
void task2Loop();

#endif
#ifndef task1_h
#define task1_h

#define LED1_PORT 9
#define BUTTON1_PORT 2

int buttonState = 0;
extern int ledState = LOW;

void task1Setup();
void task1Loop();

#endif
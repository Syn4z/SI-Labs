#ifndef taskIdle_h
#define taskIdle_h

#define BAUD_RATE 9600

int previousBlinkInterval = blinkInterval;
int previousLedState = ledState;
int previousButton2StateIdle = button2State;
int previousButton3StateIdle = button3State;

void taskIdleSetup();
void taskIdleLoop();

#endif
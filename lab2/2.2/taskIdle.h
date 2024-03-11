#ifndef taskIdle_h
#define taskIdle_h

#define BAUD_RATE 9600

int previousBlinkInterval = blinkInterval;
int previousLedState = ledState;
int previousButton2StateIdle = button2State;
int previousButton3StateIdle = button3State;

void taskIdleSetup(int offset, int rec);
void taskIdleLoop(void *pvParameters);

#endif
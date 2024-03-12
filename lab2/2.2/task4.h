#ifndef task4_h
#define task4_h

#define LED_WARNING_PORT 10
#define DELAY_PERIOD 0

int ledWarningState = LOW;

void task4Setup(int offset, int rec);
void task4Loop(void *pvParameters);

#endif
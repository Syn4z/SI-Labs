#include <stdio.h>
#include <Arduino.h>

#define LED_PIN 12

int serial_putchar(char c, FILE *stream) {
    Serial.write(c);
    return 0;
}

FILE serial_stdout;

void setup() {
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);

    while (Serial.available() > 0) {
        Serial.read();
    }
    
    fdev_setup_stream(&serial_stdout, serial_putchar, NULL, _FDEV_SETUP_WRITE);
    stdout = &serial_stdout;

    printf("Arduino LED Control\n");
    printf("Type 'led on' to turn the LED on\n");
    printf("Type 'led off' to turn the LED off\n");
}

void loop() {
    if (Serial.available() > 0) {
        String command = Serial.readStringUntil('\n');

        if (command.startsWith("led on")) {
            digitalWrite(LED_PIN, HIGH); 
            printf("LED turned on\n"); 
        } else if (command.startsWith("led off")) {
            digitalWrite(LED_PIN, LOW);
            printf("LED turned off\n");
        } else {
            printf("Invalid command\n");
        }
    }
}

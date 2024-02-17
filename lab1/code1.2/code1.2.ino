#include <Wire.h>
#include "LCD.h"
#include "MyKeypad.h"

#define MAX_CODE_LENGTH 4

const char* desiredCode = "1234"; 
const int greenLedPin = 11;
const int redLedPin = 12;

char enteredCode[MAX_CODE_LENGTH + 1]; 
int codeIndex = 0;   
bool checkCode = false; 

void displayInitialMessage() {
  lcd.setCursor(0, 0);
  lcd.print("Enter code:");
  lcd.setCursor(0, 1);
  lcd.print("Push # to submit");
  lcd.setCursor(12, 0);
}

void setup() {
  lcd.init();
  lcd.backlight();
  displayInitialMessage();

  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();

  if (key != NO_KEY) {
    if (key == '#') {
      checkCode = true;
      lcd.clear();
      lcd.print("Checking code...");
      delay(1500);
    } else {
      if (codeIndex < MAX_CODE_LENGTH) {
        enteredCode[codeIndex++] = key;
        lcd.print(key);
      }
    }

    if (checkCode) {
      enteredCode[codeIndex] = '\0';

      if (strcmp(enteredCode, desiredCode) == 0) {
        lcd.clear();
        lcd.print("Valid!");
        digitalWrite(greenLedPin, HIGH); 
        digitalWrite(redLedPin, LOW);    
        delay(3000); 
        digitalWrite(greenLedPin, LOW); 
      } else {
        lcd.clear();
        lcd.print("Wrong!");
        digitalWrite(greenLedPin, LOW); 
        digitalWrite(redLedPin, HIGH);   
        delay(3000); 
        digitalWrite(redLedPin, LOW);  
      }

      codeIndex = 0;
      checkCode = false;
      lcd.clear();
      displayInitialMessage();
    }
  }
}

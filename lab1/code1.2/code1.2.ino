#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
const char* desiredCode = "1234"; 
const int greenLedPin = 11;
const int redLedPin = 12;

#define I2C_ADDR 0x27
#define LCD_WIDTH 12
#define LCD_HEIGHT 6
#define MAX_CODE_LENGTH 4

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_WIDTH, LCD_HEIGHT);

char enteredCode[MAX_CODE_LENGTH + 1]; 
int codeIndex = 0;   
bool checkCode = false; 

void setup() {
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Enter code:");

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
      lcd.setCursor(0, 0);
      lcd.print("Enter code:");
    }
  }
}

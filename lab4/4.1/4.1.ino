#include <LiquidCrystal_I2C.h>
#include <stdio.h>

const int lcdAddress = 0x27; 
LiquidCrystal_I2C lcd(lcdAddress, 16, 2);
const int relayPin = 2;
const String turnOn = "ON";
const String turnOff = "OFF";

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight(); 
  redirectLCDOutput();
  printf("LED: OFF");
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  redirectSerialOutput();
  printf("Commands:\nON    Turn on the relay\nOFF    Turn off the relay");
}

void loop() {
  redirectLCDOutput();
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    if (command == turnOn) {
      digitalWrite(relayPin, HIGH); 
      printf("LED: ON ");
    } else if (command == turnOff) {   
      digitalWrite(relayPin, LOW);
      printf("LED: OFF");
    }
  }
}

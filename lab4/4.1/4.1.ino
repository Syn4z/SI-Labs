#include <LiquidCrystal_I2C.h>
#include <stdio.h>
#include "relay.h"

const int lcdAddress = 0x27; 
LiquidCrystal_I2C lcd(lcdAddress, 16, 2);
const String turnOn = "ON";
const String turnOff = "OFF";

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight(); 
  redirectLCDOutput();
  printf("LED: OFF");
  RelayInit();
  RelayOff();
  redirectSerialOutput();
  printf("Commands:\nON    Turn on the relay\nOFF    Turn off the relay");
}

void loop() {
  redirectLCDOutput();
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    if (command == turnOn) {
      RelayOn(); 
      printf("LED: ON ");
    } else if (command == turnOff) {   
      RelayOff();
      printf("LED: OFF");
    }
  }
}

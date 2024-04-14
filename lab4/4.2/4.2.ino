#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define enA 10
#define in1 7
#define in2 6
#define lcdAddress 32
const int defaultSpeed = 255;
const int minSpeed = -100;
const int linkSpeed = 0;
const int maxSpeed = 100;
const float percentTransform = 0.01;
const int timeDelay = 3000;

LiquidCrystal_I2C lcd(lcdAddress, 16, 2);

class L293DController {
public:
  
  void init() {
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
  }
  
  void setCounterClockwiseSpeed(int speed) {
    analogWrite(enA, (speed * percentTransform) * defaultSpeed);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }

  void setClockwiseSpeed(int speed) {
    analogWrite(enA, (abs(speed) * percentTransform) * defaultSpeed);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  
};

class MotorController {
public:

  L293DController driverController;
  
  void init() {
    driverController.init();
  }
  
  void changeSpeed(int speed) {
    if (speed >= 0){
      driverController.setCounterClockwiseSpeed(speed);
    } else if (speed < 0){
      driverController.setClockwiseSpeed(speed);
    }
  }
};

MotorController motorController;

void displayInitialMessage() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter speed in %:");
}

void setup() {
  motorController.init();
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  displayInitialMessage();
}

void loop() {
  if (Serial.available() > 0) {
    int speed = Serial.parseInt();
    if (speed >= linkSpeed && speed <= maxSpeed) {
      motorController.changeSpeed(speed);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Speed set to: ");
      lcd.setCursor(0, 1);
      lcd.print(speed);
      lcd.print("%");
      delay(timeDelay);
      displayInitialMessage();
    } else if (speed >= minSpeed && speed <= linkSpeed) {
      motorController.changeSpeed(speed);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Speed set to: ");
      lcd.setCursor(0, 1);
      lcd.print(speed);
      lcd.print("%");
      delay(timeDelay);
      displayInitialMessage();
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Invalid speed!");
      lcd.setCursor(0, 1);
      lcd.print("Range:-100...100");
      delay(timeDelay);
      displayInitialMessage();
    }
  }
}

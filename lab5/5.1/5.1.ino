#include <LiquidCrystal_I2C.h>

#define BAUD_RATE 9600

#define LED_SETPOINT_PIN A0
#define LED_OUT_PIN 5

#define LED_SETPOINT_MIN 0
#define LED_SETPOINT_MAX 100

#define ADC_MIN 0
#define ADC_MAX 1023

#define LED_OUT_MIN 3000
#define LED_OUT_MAX 5000

#define PWM_MIN 0
#define PWM_MAX 255

#define TEMP_SETPOINT_PIN A1
#define TEMP_SETPOINT_MAX 80
#define TEMP_SETPOINT_MIN -24

#define TEMP_DELTA 1

#define RELAY_OUT_PIN 4
int TEMP_SetPoint = 24;
const float BETA_COEFFICIENT = 3950;

#define LCD_ADDRESS 0x27

const int lcdDimensions[2] = {16, 2};
LiquidCrystal_I2C lcd(LCD_ADDRESS, lcdDimensions[0], lcdDimensions[1]); 

void lcdInit() {
  lcd.clear();
  lcd.print("LED SetPoint:");
  lcd.setCursor(0, 1);
  lcd.print("LED 2 State:");
}

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(LED_OUT_PIN, OUTPUT);
  lcd.begin(lcdDimensions[0], lcdDimensions[1]);
  lcdInit();
}

void loop() {
  int LED_SetPointRaw = analogRead(LED_SETPOINT_PIN);
  int LED_SetPoint = map(LED_SetPointRaw, ADC_MIN, ADC_MAX, LED_SETPOINT_MIN, LED_SETPOINT_MAX);
  int LED_OutPWM = map(LED_SetPoint, LED_SETPOINT_MIN, LED_SETPOINT_MAX, PWM_MIN, PWM_MAX);
  analogWrite(LED_OUT_PIN, LED_OutPWM);

  if (Serial.available() > 0) {
    int parsedInt = Serial.parseInt();
    if (parsedInt != 0 && parsedInt <= TEMP_SETPOINT_MAX && parsedInt >= TEMP_SETPOINT_MIN) {
      TEMP_SetPoint = parsedInt;
    } else {
      Serial.println("Invalid range!");
    }
  }
  int NTC_TempRaw = analogRead(TEMP_SETPOINT_PIN);
  int NTC_Temp = 1 / (log(1 / (1023. / NTC_TempRaw - 1)) / BETA_COEFFICIENT + 1.0 / 298.15) - 273.15;
  Serial.print("Actual value: ");
  Serial.print(NTC_Temp);
  Serial.println("°C");
  Serial.print("Expected value: < ");
  Serial.print(TEMP_SetPoint);
  Serial.println("°C");
  if (NTC_Temp < TEMP_SetPoint - TEMP_DELTA){
    pinMode(RELAY_OUT_PIN, OUTPUT);
    digitalWrite(RELAY_OUT_PIN, HIGH);
  } else if (NTC_Temp > TEMP_SetPoint + TEMP_DELTA){
    pinMode(RELAY_OUT_PIN, OUTPUT);
    digitalWrite(RELAY_OUT_PIN, LOW);
  }

  lcdInit();
  lcd.setCursor(12, 1);
  if (digitalRead(RELAY_OUT_PIN) == HIGH){
    lcd.print("ON");
  } else {
    lcd.print("OFF");
  }

  lcd.setCursor(13, 0);
  lcd.print(LED_SetPoint);
  delay(1000);
}

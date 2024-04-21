#include <LiquidCrystal_I2C.h>

#define BAUD_RATE 9600
#define INPUT_PIN 7
#define MAX_INPUT_LENGTH 10
#define LCD_ADDRESS 32

// L293N Driver
#define enA 10
#define in1 7
#define in2 6

// Encoder
#define ENCODER_PIN_A 8
#define ENCODER_PIN_B 9

// Motor
#define MOTOR_SETPOINT_PIN A1

#define MOTOR_SETPOINT_MIN -100
#define MOTOR_SETPOINT_MAX 100
#define MOTOR_SPEED_MIN -255
#define MOTOR_SPEED_MAX 255

#define ADC_MIN 0
#define ADC_MAX 1023

// PWM
#define PWM_MIN 0
#define PWM_MAX 255
#define PWM_VOLTAGE_MIN 0
#define PWM_VOLTAGE_MAx 5000

// Temp sensor
#define TEMP_STARTING_FACTOR 20
#define TEMP_SETPOINT_PIN A1
#define NTC_TEMP_PIN A2
#define TEMP_OUT_PIN 5

#define TEMP_DELTA 1
#define TEMP_MAX 125
#define TEMP_MIN -40
#define TEMP_COEF 3.04

#define TEMP_SETPOINT_MIN -40
#define TEMP_SETPOINT_MAX 125

#define TEMP_VOLTAGE_MAX 500
#define TEMP_VOLTAGE_MIN 2000

#define ADC_VOLTAGE_MIN 0
#define ADC_VOLTAGE_MAX 5000
int TEMP_SetPoint = 0;

const int ENCODER_PPR = 416;
static int totalCounts = 0;
int currentPosition = 0;

// PID variables
long previousTimeMicros = 0;
int previousPosition = 0;
double lastError = 0, rateError = 0;
volatile int position = 0; // This variable is changed within the interrupt service routine

// PID constants
const float kp = 0.5;  // Proportional gain
const float ki = 0.11; // Integral gain
const float kd = 0;    // Derivative gain

const int lcdDimensions[2] = {16, 2};
LiquidCrystal_I2C lcd(LCD_ADDRESS, lcdDimensions[0], lcdDimensions[1]); 

void lcdInit() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp Control:");
}

int getTemp(int analogValue) {
  int celsius = map(((analogValue - TEMP_STARTING_FACTOR) * TEMP_COEF), ADC_MIN, ADC_MAX, TEMP_MIN, TEMP_MAX);
  return celsius;
}

void setCounterClockwiseSpeed(int speed) {
  analogWrite(enA, speed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

void setClockwiseSpeed(int speed) {
  analogWrite(enA, abs(speed));
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

void changeMotorSpeed(int speed, int direction) {
  if (direction == 1){
    setCounterClockwiseSpeed(speed);
  } else {
    setClockwiseSpeed(speed);
  }
}

void readEncoder() {
    int b = digitalRead(ENCODER_PIN_B);
    int positionChange = position - previousPosition;
    if (b > 0) {
        positionChange = abs(positionChange);
    } else {
        positionChange = -abs(positionChange);
    }

    // Check if a full revolution has been completed
    if (abs(totalCounts) >= ENCODER_PPR) {
        // Reset total counts and consider only the remaining change for velocity calculation
        totalCounts = positionChange % ENCODER_PPR;
        positionChange = totalCounts;
    } else {
        // Accumulate counts for the next calculation
        totalCounts += positionChange;
    }
}

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(TEMP_OUT_PIN, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  pinMode(ENCODER_PIN_A, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A), readEncoder, RISING);
  pinMode(ENCODER_PIN_B, INPUT);
  
  lcd.begin(lcdDimensions[0], lcdDimensions[1]);
  lcd.init();
  lcd.backlight();
  lcdInit();

}

void loop() {  
  currentPosition = position;
  long currentTimeMicros = micros();
  float deltaTimeSec = (currentTimeMicros - previousTimeMicros) / 1000000.0;
  previousTimeMicros = currentTimeMicros;
  int positionChange = currentPosition - previousPosition;
  previousPosition = currentPosition;
  float velocityCountsPerSec = positionChange / deltaTimeSec;
  float currentRPM = velocityCountsPerSec * 60.0 / ENCODER_PPR;
  
  int SetPointRPMRaw = analogRead(MOTOR_SETPOINT_PIN);
  int SetPointRPM = map(SetPointRPMRaw, ADC_MIN, ADC_MAX, MOTOR_SETPOINT_MIN, MOTOR_SETPOINT_MAX);
  
  // PID calculation
  float error = SetPointRPM - currentRPM;
  static float integralError = 0;
  integralError += error * deltaTimeSec;
  rateError = (error - lastError) / deltaTimeSec;
  float pidOutput = kp * error + ki * integralError + kd * rateError;
  lastError = error;
  
  float controlSignal = constrain(pidOutput, MOTOR_SPEED_MIN, MOTOR_SPEED_MAX);
  int motorDirection = controlSignal >= 0 ? 1 : -1;
  
  //int Motor_OutPWM = map(Motor_SetPoint, ADC_MIN, ADC_MAX, PWM_MIN, PWM_MAX);
  changeMotorSpeed(controlSignal, motorDirection);
  
  // Convert voltage to temp
  int NTC_Raw = analogRead(NTC_TEMP_PIN);
  int NTC_Temp = getTemp(NTC_Raw); 
  
  if (Serial.available() > 0) {
    int parsedInt = Serial.parseInt();
    if (parsedInt != 0 && parsedInt <= TEMP_SETPOINT_MAX && parsedInt >= TEMP_SETPOINT_MIN) {
      TEMP_SetPoint = parsedInt;
    } else {
      Serial.println("Invalid range!");
    }
  }
  int TempOut = 0;
  if (TEMP_SetPoint < NTC_Temp - TEMP_DELTA) {
    TempOut = HIGH;
  } else if (TEMP_SetPoint > NTC_Temp + TEMP_DELTA) {
    TempOut = LOW;
  }

  Serial.print("Temperature setpoint: ");
  Serial.print(TEMP_SetPoint);
  Serial.println();
  Serial.print("Actual temperature: ");
  Serial.print(NTC_Temp);
  Serial.println();
  digitalWrite(TEMP_OUT_PIN, TempOut);

  // LCD
  lcdInit();
  if (TempOut == HIGH) {
    lcd.print("On");
  } else {
    lcd.print("Off");
  }

  Serial.println();  
  
  delay(100);

}
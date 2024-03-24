#include <OneWire.h>
#include <DallasTemperature.h>
#include <stdio.h>
#include "filters.h"
#include "utils.h"

#define LIGHT_SENSOR_PIN A0
#define TEMPERATURE_SENSOR_PIN 2
#define DELAY_INTERVAL 100

char stringResult[20];
int count = 0;
int analogValues[WINDOW_SIZE];
float weights[WINDOW_SIZE];

OneWire oneWire(TEMPERATURE_SENSOR_PIN);
DallasTemperature temperatureSensor(&oneWire);

void setup() {
  Serial.begin(9600);
  redirectOutput();
  updateWeights();
  temperatureSensor.begin();
}

void loop() {
  int analogValue = analogRead(LIGHT_SENSOR_PIN);
  if (count < WINDOW_SIZE) {
    analogValues[count] = analogValue;
    count++;
    delay(DELAY_INTERVAL);
  }
  int analogValueSalt = saltAndPepperFilter(analogValue);
  int analogValueWeighted = weightedAverageFilter(analogValues, weights);
  float voltage = analogValue / 1024. * 5;
  float lux = voltageToLux(voltage); 
  temperatureSensor.requestTemperatures(); 
  float tempC = temperatureSensor.getTempCByIndex(0);

  floatToString(analogValue, stringResult);
  printf("Analog Value: %s V\n", stringResult);
  floatToString(analogValueSalt, stringResult);
  printf("Analog Value after Salt and Pepper: %s V\n", stringResult);
  floatToString(voltage, stringResult);
  printf("LDR Voltage: %s V\n", stringResult);
  floatToString(lux, stringResult);
  printf("Luminosity: %s Lux\n", stringResult);
  printf("Temperature: ");
  if(tempC != DEVICE_DISCONNECTED_C) {
    floatToString(tempC, stringResult);
    printf("%s °C\n", stringResult);
  } else {
    printf("Error: Unable to read temperature data\n");
  }
  delay(DELAY_INTERVAL*10);
}

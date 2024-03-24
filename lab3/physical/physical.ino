#include <OneWire.h>
#include <DallasTemperature.h>

#define LIGHT_SENSOR_PORT = 3;
#define TEMPERATURE_SENSOR_PORT 2

OneWire oneWire(TEMPERATURE_SENSOR_PORT);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  pinMode(LIGHT_SENSOR_PORT, INPUT);
  sensors.begin();
}

void loop() {
  int lightValue = digitalRead(LIGHT_SENSOR_PORT);
  sensors.requestTemperatures(); 
  float tempC = sensors.getTempCByIndex(0);
  
  Serial.print("LDR Digital Value: ");
  Serial.println(lightValue);
  Serial.print("Temperature: ");
  if(tempC != DEVICE_DISCONNECTED_C) {
    Serial.print(tempC);
    Serial.println("°C");
  } else {
    Serial.println("Error: Unable to read temperature data");
  }
  delay(1000);
}

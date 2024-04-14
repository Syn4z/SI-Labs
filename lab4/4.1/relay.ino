#include "relay.h"

void RelayInit() {
  pinMode(INPUT_PIN, OUTPUT);
}

void RelayOn() {
  digitalWrite(INPUT_PIN, HIGH);
}

void RelayOff() {
  digitalWrite(INPUT_PIN, LOW);
}
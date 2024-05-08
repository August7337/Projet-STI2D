#include "hasher.h"
#include <Arduino.h>

unsigned long previousMillis = 0;
bool isHigh;

void Hasher(int pin, int pourcentage) {
  int timeHigh = pourcentage;
  int timeLow = 100 - pourcentage;

  if (millis() - previousMillis >= timeLow && isHigh) {
    previousMillis = millis();
    isHigh = false;
    digitalWrite(pin, HIGH);
  } else if (millis() - previousMillis >= timeHigh && !isHigh) {
    previousMillis = millis();
    isHigh = true;
    digitalWrite(pin, LOW);
  }
}
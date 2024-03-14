#include <Arduino.h>
#include "hasher.h"

const int hasherPin = 9;

void setup() {
  Serial.begin(9600);
  pinMode(hasherPin, OUTPUT);
}

void loop() {
  function(hasherPin, 100);
}
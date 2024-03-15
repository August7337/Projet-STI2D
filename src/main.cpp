#include <Arduino.h>
#include "hasher.h"
#include "potentiometer.h"

const int hasherPin = 9;

int pinA = 3; // Connected to CLK on KY-040
int pinB = 4; // Connected to DT on KY-040
int pinALast;


void setup() {
  Serial.begin(9600);
  pinMode(hasherPin, OUTPUT);

  pinMode (pinA,INPUT);
 pinMode (pinB,INPUT);
 /* Read Pin A
 Whatever state it's in will reflect the last position
 */
 pinALast = digitalRead(pinA); 
}

void loop() {
    Hasher(hasherPin, Potentiometer(pinA, pinB, pinALast, 0, 100));
}   
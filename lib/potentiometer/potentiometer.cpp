#include "potentiometer.h"
#include <Arduino.h>

 int encoderPosCount = 0;
 int aVal;
 boolean bCW;


int Potentiometer(int pinA, int pinB, int pinALast, int minValue, int maxValue) {
    aVal = digitalRead(pinA);
    if (aVal != pinALast){ // Means the knob is rotating
        // if the knob is rotating, we need to determine direction
        // We do that by reading pin B.
        if (digitalRead(pinB) != aVal) { // Means pin A Changed first - We're Rotating Clockwise
            if (encoderPosCount <= maxValue)
            {
                encoderPosCount ++;
            }
        bCW = true;

        } else {// Otherwise B changed first and we're moving CCW
            bCW = false;
            if (encoderPosCount >= minValue)
            {
                encoderPosCount--;
            }
        }

        Serial.print ("Rotated: ");
        if (bCW){
            Serial.println ("clockwise");
        }else{
            Serial.println("counterclockwise");
        }
        Serial.print("Encoder Position: ");
        Serial.println(encoderPosCount);

    }
    pinALast = aVal;
    return  encoderPosCount;
}
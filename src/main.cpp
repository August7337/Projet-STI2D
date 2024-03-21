#include <Arduino.h>
#include "hasher.h"
#include "potentiometer.h"

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


const int hasherPin = 9;

int pinA = 3; // Connected to CLK on KY-040
int pinB = 4; // Connected to DT on KY-040
int pinALast;

#define LCD_ADDR 0x27 

// Nombre de colonnes et de lignes de l'écran LCD
#define LCD_COLS 16
#define LCD_ROWS 2

// Création d'une instance de l'écran LCD
LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);  

void setup() {
    Serial.begin(9600);
    pinMode(hasherPin, OUTPUT);

    pinMode (pinA,INPUT);
    pinMode (pinB,INPUT);
    pinALast = digitalRead(pinA); 

    lcd.init();   
    lcd.backlight();
    lcd.setCursor(0,0);
}

void loop() {
    
    int pot = Potentiometer(pinA, pinB, pinALast, 0, 100);
    Hasher(hasherPin, pot);

    // Screen
    lcd.print(String(pot));
    lcd.clear();   
}   
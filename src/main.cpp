#include <Arduino.h>
#include "hasher.h"
#include "potentiometer.h"

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const int hasherPin = 9;

int pinA = 3; // Connected to CLK on KY-040
int pinB = 4; // Connected to DT on KY-040
int pinC = 5;
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
    pinMode (pinC,INPUT);
    pinALast = digitalRead(pinA); 

    lcd.init();   
    lcd.backlight();
    lcd.setCursor(0,0);
}

int lastPot=0;
int pot;

int menuPos = 1;

void fanMenu();
void fanMenu(){
    pot = Potentiometer(pinA, pinB, pinALast, 0, 100);
    Hasher(hasherPin, pot);

    if (lastPot == pot)
    {
        lcd.setCursor(0,0);
        lcd.print("Ventilateur 1");
        lcd.setCursor(0,1);
        lcd.print(String(pot));
        lcd.print(" %");
        lcd.clear();
    }
    lastPot = pot;
}

void loop() {

    if (menuPos == 1)
    {
        lcd.setCursor(0,0);
        lcd.print("Menu principal");

        lcd.clear();
        pot = Potentiometer(pinA, pinB, pinALast, 0, 100);
        Serial.println(digitalRead(pinC));
        //Serial.println(pot);
        if (digitalRead(pinC) == 0)
        {
            menuPos = 11;
        }
        Hasher(hasherPin, pot);
    }
    else if (menuPos == 11){
        fanMenu();
    }
}
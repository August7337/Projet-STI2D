#include <Arduino.h>
#include "hasher.h"
#include "RotaryEncoder.h"

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const int hasherPin = 10;

#define LCD_ADDR 0x27 

// Nombre de colonnes et de lignes de l'écran LCD
#define LCD_COLS 16
#define LCD_ROWS 2

// Création d'une instance de l'écran LCD
LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);  


int Counter = 0, LastCount = 0; //uneeded just for test
void RotaryChanged(); //we need to declare the func above so Rotary goes to the one below

RotaryEncoder Rotary(&RotaryChanged, 2, 3, 4); // Pins 2 (DT), 3 (CLK), 4 (SW)


void RotaryChanged()
{
  const unsigned int state = Rotary.GetState();
  
  if (state & DIR_CW) 
    Counter++;
    
  if (state & DIR_CCW)  
    Counter--;    
}



void setup() {
    Rotary.setup();  
    Serial.begin(9600);
    pinMode(hasherPin, OUTPUT);

    lcd.init();   
    lcd.backlight();
    lcd.setCursor(0,0);
}

int lastPot=0;
int pot;
int potMenu;

int menuPos = 1;

void fanMenu();
void fanMenu(){
    Hasher(hasherPin, Counter);

    if (LastCount != Counter)  
    {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Ventilateur 1");
        lcd.setCursor(0,1);
        lcd.print(String(Counter));
        lcd.print(" %");  
    }
}

void loop() {
    if (menuPos == 1)
    {
        lcd.setCursor(0,0);
        lcd.print("Menu principal");
        
        if (Rotary.GetButtonDown())
        {
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Ventilateur 1");
            lcd.setCursor(0,1);
            lcd.print(String(Counter));
            lcd.print(" %");  
            menuPos = 11;
        }
    }
    else if (menuPos == 11){
        fanMenu();
    }
}
#include <Arduino.h>
#include "hasher.h"
#include "RotaryEncoder.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


const int fan1HasherPin = 9;
const int tempHasherPin = 10;
const int motorHasherPin = 11;

#define LCD_ADDR 0x27 

// Nombre de colonnes et de lignes de l'écran LCD
#define LCD_COLS 16
#define LCD_ROWS 4

// Création d'une instance de l'écran LCD
LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);  

int lastPot=0;
int pot;
int potMenu;
int menuPos = 1;

bool needRefresh = false;

int settingsCounter = 0, lastSettingsCount = 0;
int fan1Count = 0, lastFan1Count = 0;
int lastTempCount = 0, tempCount = 0;
int lastMotorCount = 0, motorCount = 0;

void RotaryChanged();
RotaryEncoder Rotary(&RotaryChanged, 2, 3, 4); // Pins 2 (DT), 3 (CLK), 4 (SW)

void RotaryChanged()
{
  const unsigned int state = Rotary.GetState();
  
  if (state & DIR_CW){
    if (menuPos == 11)
    {
        settingsCounter--;
    }
     if (menuPos == 111)
    {
        tempCount--;
    }
     if (menuPos == 1131)
    {
        fan1Count--;
    }
     if (menuPos == 112)
    {
        motorCount--;
    }
  }
    
    
  if (state & DIR_CCW){
    if (menuPos == 11)
    {
        settingsCounter++;
    }
     if (menuPos == 111)
    {
        tempCount++;
    }
     if (menuPos == 1131)
    {
        fan1Count++;
    }
     if (menuPos == 112)
    {
        motorCount++;
    }
  }
}

void mainMenu();
void mainMenu(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Menu principal");
    
    if (Rotary.GetButtonDown())
    {
        needRefresh = true;
        menuPos = 11;
    }
}

void setup() {
    Rotary.setup();  
    Serial.begin(9600);
    pinMode(fan1HasherPin, OUTPUT);
    digitalWrite(fan1HasherPin, LOW);

    pinMode(tempHasherPin, OUTPUT);
    digitalWrite(tempHasherPin, LOW);

    pinMode(motorHasherPin, OUTPUT);
    digitalWrite(motorHasherPin, LOW);
    
    lcd.init();   
    lcd.backlight();
    lcd.setCursor(0,0);

    mainMenu();
}

void settingsMenu();
void settingsMenu(){

    if (lastSettingsCount != settingsCounter || needRefresh )  
    {
        needRefresh = false;

        lcd.clear();

        lcd.setCursor(0,0);
        if (settingsCounter == 0)
        {
            lcd.print("*PARAMETRE");
        } else {
            lcd.print(" PARAMETRE");
        }
        
        
        lcd.setCursor(0,1);
        if (settingsCounter == 1)
        {
            lcd.print("* temperature"); 
        } else {
            lcd.print("  temperature"); 
        }

        lcd.setCursor(0,2);
        if (settingsCounter == 2)
        {
            lcd.print("* moteur"); 
        } else {
            lcd.print("  moteur"); 
        }
        
        lcd.setCursor(0,3);
        if (settingsCounter == 3)
        {
            lcd.print("* ventilateurs");  
        } else {
            lcd.print("  ventilateurs");  
        }

        lastSettingsCount = settingsCounter;
    }

    if (Rotary.GetButtonDown())
    {
        if (settingsCounter == 0)
        {
            needRefresh = true;
            menuPos = 1;
        } else if (settingsCounter == 1) {
            needRefresh = true;
            menuPos = 111;
        } else if (settingsCounter == 2) {
            needRefresh = true;
            menuPos = 112;
        } else if (settingsCounter == 3) {
            needRefresh = true;
            menuPos = 1131;
        }
    }
}


void fanMenu();
void fanMenu(){

    if (lastFan1Count != fan1Count || needRefresh)  
    {
        needRefresh = false;

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Ventilateur 1 ");
        lcd.setCursor(0,1);
        lcd.print(String(fan1Count));
        lcd.print(" %");  

        lastFan1Count = fan1Count;
    }

    if (Rotary.GetButtonDown())
    {
        needRefresh = true;
        menuPos = 11;
        
    }
}

void tempMenu();
void tempMenu(){

    if (lastTempCount != tempCount || needRefresh)  
    {
        needRefresh = false;

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Temperature ");
        lcd.setCursor(0,1);
        lcd.print(String(tempCount));
        lcd.print(" %");  

        lastTempCount = tempCount;
    }

    if (Rotary.GetButtonDown())
    {
        needRefresh = true;
        menuPos = 11;
        
    }
}

void motorMenu();
void motorMenu(){

    if (lastMotorCount != motorCount || needRefresh)  
    {
        needRefresh = false;

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Moteur ");
        lcd.setCursor(0,1);
        lcd.print(String(motorCount));
        lcd.print(" %");  

        lastMotorCount = motorCount;
    }

    if (Rotary.GetButtonDown())
    {
        needRefresh = true;
        menuPos = 11;
        
    }
    Hasher(motorHasherPin, motorCount);
}


void loop() {
    if (menuPos == 1)
    {
        mainMenu();
    }
    else if (menuPos == 11){
        settingsMenu();
    }
    else if (menuPos == 111){
        tempMenu();
    }
    else if (menuPos == 112){
        motorMenu();
    }
    else if (menuPos == 1131){
        fanMenu();
    }

    // Hasher section
    Hasher(fan1HasherPin, fan1Count);
    Hasher(tempHasherPin, tempCount);
    

}
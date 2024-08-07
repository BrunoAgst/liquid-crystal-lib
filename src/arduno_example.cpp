#include "Arduino.h"
#include "../lib/arduino/liquid_crystal_lib.h"

void setup(){
    LiquidCrystal liquidCrystal(6, 5, 4, 3, 2);
    liquidCrystal.initLCD();
    liquidCrystal.write("Hello World");
    delay(500);
    liquidCrystal.clear();
}

void loop(){}
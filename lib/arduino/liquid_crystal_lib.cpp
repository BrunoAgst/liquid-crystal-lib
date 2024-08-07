//
// Created by Bruno Augusto on 06/08/24.
//

#include "liquid_crystal_lib.h"
#include "Arduino.h"

LiquidCrystal::LiquidCrystal(int en, int rs, int data, int st, int sh)
: pinEN(en), pinRS(rs), pinDATA(data), pinST(st), pinSH(sh){
    pinMode(pinRS, OUTPUT);
    pinMode(pinEN, OUTPUT);
    pinMode(pinDATA, OUTPUT);
    pinMode(pinST, OUTPUT);
    pinMode(pinSH, OUTPUT);
}

void LiquidCrystal::write(const char *str){
    int i = 1;
    while (*str){
        sendData(*str++);
        if(i == 16){
            sendCommand(0xC0);
            i = 1;
        } else {
            i++;
        }
    }
}

void LiquidCrystal::setData74HC595(uint8_t data){
    digitalWrite(pinST, LOW);
    for(int i = 11; i >= 0; i--){
        digitalWrite(pinDATA, data & (1 << i) ? HIGH : LOW);
        digitalWrite(pinSH, HIGH);
        delay(1);
        digitalWrite(pinSH, LOW);
    }
    digitalWrite(pinST, HIGH);
    pulseEN();
}

void LiquidCrystal::sendData(uint8_t data){
    digitalWrite(pinRS, HIGH);
    setData74HC595(data);
}

void LiquidCrystal::initLCD(){
    digitalWrite(pinEN, LOW);
    delay(50);

    sendCommand(0x30);
    delay(5);

    sendCommand(0x30);
    delayMicroseconds(100);

    sendCommand(0x30);
    sendCommand(0x38);
    sendCommand(0xC);
    sendCommand(0x6);
    sendCommand(0x1);
    delay(5);
}

void LiquidCrystal::sendCommand(uint8_t cmd){
    digitalWrite(pinRS, LOW);
    setData74HC595(cmd);
}

void LiquidCrystal::pulseEN(){
    digitalWrite(pinEN, LOW);
    delayMicroseconds(1);
    digitalWrite(pinEN, HIGH);
    delayMicroseconds(1);
    digitalWrite(pinEN, LOW);
    delayMicroseconds(100);
}

void LiquidCrystal::clear(){
    sendCommand(0x1);
}



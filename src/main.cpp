#include <Arduino.h>

#define EN 6
#define RS 5
#define DATA 4
#define ST 3
#define SH 2

void write(const char *str);
void clear();
void setData74HC595(uint8_t data);
void sendData(uint8_t data);
void configurePinMode();
void initLCD();
void pulseEN();
void sendCommand(uint8_t cmd);

void setup() {
    configurePinMode();
    initLCD();
    write("Coroca quer vir para o Sao Joao");
    delay(500);
    clear();

}

void loop() {}

void write(const char *str){
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

void configurePinMode(){
    pinMode(RS, OUTPUT);
    pinMode(EN, OUTPUT);
    pinMode(DATA, OUTPUT);
    pinMode(ST, OUTPUT);
    pinMode(SH, OUTPUT);
}

void setData74HC595(uint8_t data){
    digitalWrite(ST, LOW);
    for(int i = 11; i >= 0; i--){
        digitalWrite(DATA, data & (1 << i) ? HIGH : LOW);
        digitalWrite(SH, HIGH);
        delay(1);
        digitalWrite(SH, LOW);
    }
    digitalWrite(ST, HIGH);
    pulseEN();
}

void sendData(uint8_t data){
    digitalWrite(RS, HIGH);
    setData74HC595(data);
}

void initLCD(){
    digitalWrite(EN, LOW);
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

void sendCommand(uint8_t cmd){
    digitalWrite(RS, LOW);
    setData74HC595(cmd);
}

void pulseEN(){
    digitalWrite(EN, LOW);
    delayMicroseconds(1);
    digitalWrite(EN, HIGH);
    delayMicroseconds(1);
    digitalWrite(EN, LOW);
    delayMicroseconds(100);
}

void clear(){
    sendCommand(0x1);
}



//
// Created by Bruno Augusto on 06/08/24.
//

#ifndef LIQUID_CRYSTAL_LIB_H
#define LIQUID_CRYSTAL_LIB_H


class LiquidCrystal {
    private:
        int pinEN;
        int pinRS;
        int pinDATA;
        int pinST;
        int pinSH;
        void setData74HC595(unsigned char data);
        void sendData(unsigned char data);
        void pulseEN();
        void sendCommand(unsigned char cmd);
    public:
        LiquidCrystal(int en, int rs, int data, int st, int sh);
        void write(const char *str);
        void clear();
        void initLCD();
};


#endif

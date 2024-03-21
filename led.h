#ifndef LED_H
#define LED_H
#include<Arduino.h>
class Led
{
    public: 
        Led(int ledPin);
        void on();
        void off();
        void init();
    
    private: 
        int pin;
};

#endif
#ifndef LED_H
#define LED_H

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
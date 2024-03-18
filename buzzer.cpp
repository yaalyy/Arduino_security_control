#include "buzzer.h"
#include<Arduino.h>

Buzzer::Buzzer(int buzzerPin)
{
    this->pin = buzzerPin;
}

void Buzzer::buzzerBeeping(int freq, int time)    //Not possible to generate tones lower than 31Hz
{
    tone(pin, freq, time);
    
}

void Buzzer::initBuzzer()
{
    pinMode(this->pin, OUTPUT);
}


void Buzzer::entryBeeping()   // passcode is correct
{
    tone(pin, 262, 300);
    delay(300);
    tone(pin, 294, 300);
    delay(300);
    tone(pin, 330, 300);
    delay(300);
    
}

void Buzzer::buttonPressed()   // general sound when button pressed
{
    tone(pin, 400, 100);
}

void Buzzer::alarm()    // Enter incorrect passcode three times in a row
{
    int i=0;
    for(i;i<60;i=i+1)
    {
        tone(pin,1000,500);
        delay(500);
        tone(pin,500,500);
        delay(500);
    }
}


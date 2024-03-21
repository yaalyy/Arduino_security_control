#include "led.h"

Led::Led(int ledPin)
{
    this->pin = ledPin;
}

void Led::on()
{
    digitalWrite(pin, HIGH);
}

void Led::off()
{
    digitalWrite(pin, LOW);
}

void Led::init()
{
    pinMode(pin, OUTPUT);
}
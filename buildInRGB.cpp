#include "buildInRGB.h"

void initBuildInRGB()
{
    WiFiDrv::pinMode(25, OUTPUT);    // configure red pin 
    WiFiDrv::pinMode(26, OUTPUT);    // configure green pin
    WiFiDrv::pinMode(27, OUTPUT);    // configure blue pin
}

void setBuildInRGB(int red, int green, int blue)
{
    WiFiDrv::analogWrite(25, red);
    WiFiDrv::analogWrite(26, green);
    WiFiDrv::analogWrite(27, blue);
}

void turnOffBuildInRGB()
{
    WiFiDrv::analogWrite(25, 0);
    WiFiDrv::analogWrite(26, 0);
    WiFiDrv::analogWrite(27, 0);
}
#ifndef BUILDINRGB_H
#define BUILDINRGB_H
#include <WiFiNINA.h>
#include <utility/wifi_drv.h>

void initBuildInRGB();
void setBuildInRGB(int red, int green, int blue);
void turnOffBuildInRGB();
#endif
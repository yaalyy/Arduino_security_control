#include "ntp.h"

NTPHandler::NTPHandler()
{
    WiFiUDP ntpUDP;
    NTPClient timeClient(ntpUDP);
    timeClient.begin();
    if(timeClient.update())
    {
        this->epochTime = timeClient.getEpochTime();
    }
    else
    {
        this->epochTime = 0;
    }
    this->timeOffset = 0;
    

}

NTPHandler::NTPHandler(long timeOffset)
{
    WiFiUDP ntpUDP;
    NTPClient timeClient(ntpUDP, timeOffset);
    timeClient.begin();
    if(timeClient.update())
    {
        this->epochTime = timeClient.getEpochTime();
    }
    else
    {
        this->epochTime = 0;
    }
    
    this->timeOffset = timeOffset;
}

void NTPHandler::updateTimeInfo()
{
    time_t raw_time = static_cast<time_t>(epochTime+timeOffset);
    gmtime_r(&raw_time, &timeInfo);
}
unsigned long NTPHandler::getEpochTime()
{
    return this->epochTime;
}

long NTPHandler::getTimeOffset()
{
    return this->timeOffset;
}   

int NTPHandler::getHour()
{
    updateTimeInfo();
    return timeInfo.tm_hour;
}

int NTPHandler::getMinute()
{
    updateTimeInfo();
    return timeInfo.tm_min;
}   

int NTPHandler::getSecond()
{
    updateTimeInfo();
    return timeInfo.tm_sec;
}

int NTPHandler::getYear()
{
    updateTimeInfo();
    return timeInfo.tm_year+1900;
}

int NTPHandler::getMonth()
{
    updateTimeInfo();
    return timeInfo.tm_mon+1;
}

int NTPHandler::getDay()
{
    updateTimeInfo();
    return timeInfo.tm_mday;
}   






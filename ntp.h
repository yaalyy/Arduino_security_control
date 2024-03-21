#ifndef NTP_H
#define NTP_H
#include<ctime>
#include<NTPClient.h>
#include<WiFiUdp.h>


class NTPHandler
{
    public:
        NTPHandler();
        NTPHandler(long timeOffset);
        unsigned long getEpochTime();  // return the epoch time
        int getHour();
        int getMinute(); 
        int getSecond();
        int getYear();
        int getMonth();
        int getDay();
        long getTimeOffset();
    private:
        unsigned long epochTime;
        long timeOffset;
        struct tm timeInfo;
        void updateTimeInfo();
       
};


#endif
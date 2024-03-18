#ifndef BUZZER_H
#define BUZZER_H


class Buzzer
{
    public:
        Buzzer(int buzzerPin);
        void buzzerBeeping(int freq, int time);
        void initBuzzer();
        void entryBeeping();
        void buttonPressed();
        void alarm();
    private:
        int pin;
};

#endif
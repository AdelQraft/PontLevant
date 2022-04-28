#ifndef _VILLE_CONNECTEE_CAR_COUNTING_H
#define _VILLE_CONNECTEE_CAR_COUNTING_H
#include <Arduino.h>
#include "debugging.hpp"

class CarCounting
{
private:
    uint8_t pressureCount;
    uint8_t buttonState;      // current state of the switch
    uint8_t lastButtonStateE; // previous state of the switch
    uint8_t lastButtonStateS;
    void add(int state);
    void substract(int state);
    uint8_t pinE;
    uint8_t pinS;

public:
    CarCounting(int pin1, int pin2);
    void change(int stateE, int stateS);
    bool isEmpty();
    uint8_t getPinE();
    uint8_t getPinS();
    uint8_t getCarNumber();
};

#endif

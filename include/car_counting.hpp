#ifndef _VILLE_CONNECTEE_CAR_COUNTING_H
#define _VILLE_CONNECTEE_CAR_COUNTING_H
#include <Arduino.h>

class CarCounting{
    private : 
        int carNumber;
        int buttonState;         // current state of the switch
        int lastButtonStateE;     // previous state of the switch
         int lastButtonStateS;
        void add(int state);
        void substract(int state);
        int pinE;
        int pinS;
    public : 
        CarCounting(int pin1, int pin2);
        void change(int stateE, int stateS);
        bool isEmpty();
        int getPinE();
        int getPinS();

};


#endif



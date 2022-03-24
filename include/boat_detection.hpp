#ifndef _VILLE_CONNECTEE_BOAT_DETECRTION
#define _VILLE_CONNECTEE_BOAT_DETECRTION
#include <Arduino.h>
class BoatDectection{
    private : 
        int trigPin;
        int echoPin;
    public : 
        BoatDectection(int trigPin, int echoPin);
        int getTrigPin();
        int getEchoPin();
        bool detection(double distance);

};
#endif
#include "boat_detection.hpp"

BoatDectection:: BoatDectection(int trigPin, int echoPin){
    this->echoPin = echoPin;
    this->trigPin = trigPin;
}

int BoatDectection:: getTrigPin(){
    return this->trigPin;
}
int BoatDectection:: getEchoPin(){
    return this->echoPin;
}
bool BoatDectection:: detection(double distance){
    return distance<40 && distance>0;
}


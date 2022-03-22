#include "car_counting.hpp"


CarCounting :: CarCounting(int pin1, int pin2){
    this->carNumber = 0;
    this->buttonState = 0;
    this->lastButtonState = 0;
    this->pinE = pin1;
    this->pinS = pin2;

}
void CarCounting :: add(int state){
    if (this->lastButtonState == HIGH && this->lastButtonState != state){
        this->carNumber++;
    }
    
}
void CarCounting :: substract(int state){
    if (this->lastButtonState == HIGH && this->lastButtonState != state){
        this->carNumber--;
    }
}
bool CarCounting :: isEmpty(){
    return carNumber==0;
}

int CarCounting :: getPinE(){
    return this->pinE;
}
int CarCounting :: getPinS(){
    return this->pinS;
}

void CarCounting:: change(int stateE, int stateS){
    this->add(stateE);
    this->substract(stateE);
}


#include "car_counting.hpp"


CarCounting :: CarCounting(int pin1, int pin2){
    this->carNumber = 0;
    this->buttonState = 0;
    this->lastButtonStateE = 0;
    this->lastButtonStateS = 0;
    this->pinE = pin1;
    this->pinS = pin2;
}

void CarCounting :: add(int state){
  //  Serial.println(this->lastButtonStateE != state);
    //Serial.println(state);
    if(this->lastButtonStateE == HIGH && this->lastButtonStateE != state){
        this->carNumber = this->carNumber+1; 
        Serial.println(this->carNumber);
       // Serial.println(lastButtonStateE);
    }
    this->lastButtonStateE = state;
    
}
void CarCounting :: substract(int state){
    if (this->lastButtonStateS == HIGH && this->lastButtonStateS != state){
        this->carNumber--;
        Serial.println(this->carNumber);

    }
    this->lastButtonStateS = state;
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
    this->substract(stateS);
}


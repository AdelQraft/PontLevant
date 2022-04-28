#include "car_counting.hpp"

CarCounting ::CarCounting(int pin1, int pin2)
{
    this->pressureCount = 0;
    this->buttonState = 0;
    this->lastButtonStateE = 0;
    this->lastButtonStateS = 0;
    this->pinE = pin1;
    this->pinS = pin2;
}

void CarCounting ::add(int state)
{
    //  Serial.println(this->lastButtonStateE != state);
    // Serial.println(state);
    if (this->lastButtonStateE == HIGH && this->lastButtonStateE != state)
    {
        this->pressureCount = this->pressureCount + 1;
        debugPrintln(this->pressureCount);
        // Serial.println(this->carNumber);
        // Serial.println(lastButtonStateE);
    }
    this->lastButtonStateE = state;
}
void CarCounting ::substract(int state)
{
    if (this->lastButtonStateS == HIGH && this->lastButtonStateS != state && this->pressureCount > 0)
    {
        this->pressureCount--;
        // Serial.println(this->carNumber);
        debugPrintln(this->pressureCount);
    }
    this->lastButtonStateS = state;
}
bool CarCounting ::isEmpty()
{
    return pressureCount == 0;
}

uint8_t CarCounting ::getPinE()
{
    return this->pinE;
}
uint8_t CarCounting ::getPinS()
{
    return this->pinS;
}

uint8_t CarCounting ::getCarNumber()
{
    return this->pressureCount / 2;
}

void CarCounting::change(int stateE, int stateS)
{
    this->add(stateE);
    this->substract(stateS);
}

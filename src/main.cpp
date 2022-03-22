#include <Arduino.h>
//#include "movable_bridge.hpp"
#include <AccelStepper.h>
#include "car_counting.hpp" //???


constexpr long ROTATION_STEPS = 2 << 9;

AccelStepper stepper(AccelStepper::FULL4WIRE, 5, 3, 4, 2);

const int PIN_ENTER_A,PIN_ENTER_B, PIN_EXIT_A, PIN_EXIT_B;
int stateEnterA, stateEnterB, stateExitA, stateExitB;

CarCounting sensA(PIN_ENTER_A,PIN_EXIT_A), sensB(PIN_ENTER_B,PIN_EXIT_B);


#define start setup
void start() {
	Serial.begin(9600);
	while (!Serial);

	stepper.setMaxSpeed(1000.0); // set the maximum speed
	//stepper.setAcceleration(0); // set acceleration
	stepper.setCurrentPosition(0); // set position
	stepper.moveTo(ROTATION_STEPS);
	stepper.setSpeed(500); // set initial speed

	// MovableBridge bridge(2048, 8, 10, 9, 11, 512, 512, 100);
	// bridge.open();

	while (stepper.distanceToGo() > 0) stepper.runSpeedToPosition();

	// initialize the switch pin as an input:
 	pinMode(sensA.getPinE(), INPUT);
	pinMode(sensA.getPinS(), INPUT);
	pinMode(sensB.getPinE(), INPUT);
	pinMode(sensB.getPinS(), INPUT);
	 
	Serial.println("done");
}

void loop() {

	//Add or substract a car to the bridge
	sensA.change(digitalRead(sensA.getPinE()),digitalRead(sensA.getPinS()));
	sensB.change(digitalRead(sensB.getPinE()),digitalRead(sensB.getPinS()));
	
}	// Not used.

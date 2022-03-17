#include <Arduino.h>
//#include "movable_bridge.hpp"
#include <AccelStepper.h>

constexpr long ROTATION_STEPS = 2 << 9;

AccelStepper stepper(AccelStepper::FULL4WIRE, 5, 3, 4, 2);

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
	Serial.println("done");
}

void loop() {}	// Not used.

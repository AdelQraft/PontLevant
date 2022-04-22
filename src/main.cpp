#include <Arduino.h>

#include "movable_bridge.hpp"
#include "stepper_driver/a4988.hpp"

constexpr uint8_t STEP_PIN = 12;
constexpr uint8_t DIR_PIN = 14;

constexpr int_fast32_t REVOLUTION_STEPS = 200;

void setup() {
	// Temporary.
	Serial.begin(9600);
	/*
	while (!Serial);

/*
	pinMode(STEP_PIN, OUTPUT);
	pinMode(DIR_PIN, OUTPUT);

	digitalWrite(DIR_PIN, HIGH);

	for (int x = 0; x < REVOLUTION_STEPS; x++) {
		digitalWrite(STEP_PIN, HIGH);
		delayMicroseconds(2000);
		digitalWrite(STEP_PIN, LOW);
		delayMicroseconds(2000);
	}*/


	StepperDriver::A4988 stepper(StepperDriver::A4988::PinoutDescriptor(12, 14));
	stepper.setTargetAngle(8 * REVOLUTION_STEPS);
	stepper.move();

/*
	// More generic

	MovableBridge<StepperDriver::A4988> bridge = decltype(bridge) (
		decltype(bridge)::PinoutDescriptor(23, 22),
		decltype(bridge)::PinoutDescriptor(21, 19)
	);
*/
/*
	MovableBridge<StepperDriver::A4988> bridge (
		StepperDriver::A4988::PinoutDescriptor(12, 14),
		StepperDriver::A4988::PinoutDescriptor(21, 19),
		REVOLUTION_STEPS
	);

	bridge.open();
	delay(5000);
	bridge.close();
*/
}

void loop() {}

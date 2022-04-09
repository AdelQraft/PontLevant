#include "stepper_driver/a4988.hpp"

#include <Arduino.h>

#ifdef _ESP
#include <cassert>
#else
#include <assert.h>
#endif

#include "debugging.hpp"

namespace StepperDriver {
	void A4988::updateDirection() {
		if (targetAngle > currentAngle) {
			digitalWrite(dirPin, HIGH);
			increment = 1;
		} else {
			digitalWrite(dirPin, LOW);
			increment = -1;
		}
	}

	A4988::A4988(const A4988::PinoutDescriptor &pinoutDescriptor, uint32_t speed, int_fast32_t currentAngle) {
		stepPin = pinoutDescriptor.stepPin;
		dirPin = pinoutDescriptor.dirPin;

		pinMode(stepPin, OUTPUT);
		pinMode(dirPin, OUTPUT);

		this->currentAngle = currentAngle;
		setSpeed(speed);
	}

	void A4988::setCurrentAngle(int_fast32_t angle) {
		currentAngle = angle;
		updateDirection();
	}

	void A4988::setTargetAngle(int_fast32_t angle) {
		targetAngle = angle;
		updateDirection();
	}

	uint32_t A4988::getHalfSpeedDelay() const {
		return halfSpeedDelay;
	}

	void A4988::setHalfSpeedDelay(uint32_t halfSpeedDelay) {
		this->halfSpeedDelay = halfSpeedDelay;
	}

	uint_fast32_t A4988::getSpeed() const {
		return (uint32_t)10e6 / halfSpeedDelay / 2;
	}

	void A4988::setSpeed(uint32_t speed) {
		assert(speed != 0);
		halfSpeedDelay = (uint32_t)1e6 / speed / 2;
	}

	void A4988::step() {
		//debugPrintf("currentAngle: %d, targetAngle: %d\n", currentAngle, targetAngle);

		digitalWrite(stepPin, HIGH);
		delayMicroseconds(halfSpeedDelay);
		digitalWrite(stepPin, LOW);
		delayMicroseconds(halfSpeedDelay);

		currentAngle += increment;
	}

	A4988::PinoutDescriptor::PinoutDescriptor(uint8_t stepPin, uint8_t dirPin)
		: stepPin(stepPin), dirPin(dirPin) /*, sleepPin(sleepPin)*/ {}
}
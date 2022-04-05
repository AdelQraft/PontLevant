#include "stepper_driver/a4988.hpp"

#include <Arduino.h>

#include <cassert>

namespace StepperDriver {
	A4988::A4988(const A4988::PinoutDescriptor &pinoutDescriptor, uint32_t speed, int_fast32_t currentAngle) {
		stepPin = pinoutDescriptor.stepPin;
		dirPin = pinoutDescriptor.dirPin;

		pinMode(stepPin, OUTPUT);
		pinMode(dirPin, OUTPUT);

		setCurrentAngle(currentAngle);
		setSpeed(speed);
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
		halfSpeedDelay = (uint32_t)10e6 / speed / 2;
	}

	void A4988::move() {
		int_fast8_t increment = targetAngle >= currentAngle ? 1 : -1;

		while (currentAngle != targetAngle) {
			digitalWrite(stepPin, HIGH);
			delayMicroseconds(halfSpeedDelay);
			digitalWrite(stepPin, LOW);
			delayMicroseconds(halfSpeedDelay);

			currentAngle += increment;
		}
	}

	A4988::PinoutDescriptor::PinoutDescriptor(uint8_t stepPin, uint8_t dirPin)
		: stepPin(stepPin), dirPin(dirPin) /*, sleepPin(sleepPin)*/ {}
}
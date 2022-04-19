#include "stepper_driver/a4988.hpp"

#include <Arduino.h>

#include <cassert>

#include "debugging.hpp"

namespace StepperDriver {
	void A4988::updateDirection() {
		if (targetStep > currentStep) {
			digitalWrite(dirPin, HIGH);
			increment = 1;
		} else {
			digitalWrite(dirPin, LOW);
			increment = -1;
		}
	}

	A4988::A4988(const A4988::PinoutDescriptor &pinoutDescriptor, uint32_t speed, int_fast32_t currentStep) {
		stepPin = pinoutDescriptor.stepPin;
		dirPin = pinoutDescriptor.dirPin;

		pinMode(stepPin, OUTPUT);
		pinMode(dirPin, OUTPUT);

		this->currentStep = currentStep;
		setSpeed(speed);
	}

	void A4988::setCurrentStep(int_fast32_t step) {
		currentStep = step;
		updateDirection();
	}

	void A4988::setTargetStep(int_fast32_t step) {
		targetStep = step;
		updateDirection();
	}

	uint32_t A4988::getHalfSpeedDelay() const {
		return halfSpeedDelay;
	}

	void A4988::setHalfSpeedDelay(delay_t halfSpeedDelay) {
		this->halfSpeedDelay = halfSpeedDelay;
	}

	uint_fast32_t A4988::getSpeed() const {
		return (uint32_t)10e6 / halfSpeedDelay / 2;
	}

	void A4988::setSpeed(delay_t speed) {
		assert(speed != 0);
		halfSpeedDelay = (uint32_t)1e6 / speed / 2;
	}

	void A4988::move() {
		debugPrintf(
			"currentStep: %d, targetStep: %d, stepPin: %hhu, dirPin: %hhu, halfSpeedDelay: %u, increment: %hhu\n",
			currentStep, targetStep, stepPin, dirPin, halfSpeedDelay, increment
		);

		while (currentStep != targetStep) {
			digitalWrite(stepPin, HIGH);
			delayMicroseconds(halfSpeedDelay);
			digitalWrite(stepPin, LOW);
			delayMicroseconds(halfSpeedDelay);

			currentStep += increment;
		}
	}

	A4988::PinoutDescriptor::PinoutDescriptor(uint8_t stepPin, uint8_t dirPin)
		: stepPin(stepPin), dirPin(dirPin) /*, sleepPin(sleepPin)*/ {}
}
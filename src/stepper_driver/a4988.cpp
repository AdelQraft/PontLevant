#include "stepper_driver/a4988.hpp"

#include <Arduino.h>

#ifdef _ESP
#include <cassert>
#else
#include <assert.h>
#endif

#include <cstdlib>

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

	A4988::A4988(const A4988::PinoutDescriptor &pinoutDescriptor, uint_fast32_t revolutionSteps, uint32_t speed) {
		stepPin = pinoutDescriptor.stepPin;
		dirPin = pinoutDescriptor.dirPin;

		pinMode(stepPin, OUTPUT);
		pinMode(dirPin, OUTPUT);

		setRevolutionSteps(revolutionSteps);
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

	uint_fast32_t A4988::getSpeed() const {
		return speed;
	}

	void A4988::setSpeed(delay_t speed) {
		assert(speed != 0);
		this->speed = speed;
	}

	void A4988::run() {
		delay_t delta = abs(200 - currentStep);
		if (delta == 0) return;
		delay_t halfSpeedDelay = static_cast<delay_t>(1e6) * delta / speed / 2;
		debugPrintf("targetStep: %d, currentStep: %d, halfSpeedDelay: %d, stepPin: %d, dirPin: %d, speed: %d\n", targetStep, currentStep, halfSpeedDelay, stepPin, dirPin, speed);

		do {
			digitalWrite(stepPin, HIGH);
			delayMicroseconds(halfSpeedDelay);
			digitalWrite(stepPin, LOW);
			delayMicroseconds(halfSpeedDelay);

			currentStep += increment;
		} while (currentStep != targetStep);
	}

	A4988::PinoutDescriptor::PinoutDescriptor(uint8_t stepPin, uint8_t dirPin)
		: stepPin(stepPin), dirPin(dirPin) /*, sleepPin(sleepPin)*/ {}
}
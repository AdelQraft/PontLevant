#include "stepper_driver/interface.hpp"

#include <Arduino.h>
#include <cmath>

constexpr float REVOLUTION_ANGLE_RAD = 2 * PI;

namespace StepperDriver {
	// Base interface IStepperDriver

	int_fast32_t IStepperDriver::getCurrentStep() const {
		return currentStep;
	}

	void IStepperDriver::setCurrentStep(int_fast32_t step) {
		currentStep = step;
	}

	int_fast32_t IStepperDriver::getTargetStep() const {
		return targetStep;
	}

	void IStepperDriver::setTargetStep(int_fast32_t step) {
		targetStep = step;
	}

	int_fast32_t IStepperDriver::getCurrentAngle() const {
		return stepToAngle(currentStep);
	}

	void IStepperDriver::setCurrentAngle(int_fast32_t angle) {
		setCurrentStep(angleToStep(angle));
	}

	int_fast32_t IStepperDriver::getTargetAngle() const {
		return stepToAngle(targetStep);
	}

	void IStepperDriver::setTargetAngle(int_fast32_t angle) {
		setTargetStep(angleToStep(angle));
	}

	uint_fast32_t IStepperDriver::getRevolutionSteps() const {
		return angleScale * REVOLUTION_ANGLE_RAD;
	}

	void IStepperDriver::setRevolutionSteps(uint_fast32_t steps) {
		angleScale = roundf(steps / REVOLUTION_ANGLE_RAD);
	};

	int_fast32_t IStepperDriver::angleToStep(int_fast32_t angle) const {
		return angleScale * angle;
	}

	int_fast32_t IStepperDriver::stepToAngle(int_fast32_t step) const {
		return step / angleScale;
	}

	void IStepperDriver::run() {
		while (currentAngle != targetAngle) {
			step();
		}
	}
}
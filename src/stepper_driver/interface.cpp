#include "stepper_driver/interface.hpp"

#include <Arduino.h>

#include "debugging.hpp"

constexpr float REVOLUTION_ANGLE_RAD = 2*PI;

namespace StepperDriver {
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

	float IStepperDriver::getCurrentAngle() const {
		return stepToAngle(currentStep);
	}

	void IStepperDriver::setCurrentAngle(float angle) {
		setCurrentStep(angleToStep(angle));
	}

	float IStepperDriver::getTargetAngle() const {
		return stepToAngle(targetStep);
	}

	void IStepperDriver::setTargetAngle(float angle) {
		setTargetStep(angleToStep(angle));
	}

	uint_fast32_t IStepperDriver::getRevolutionSteps() const {
		return angleScale * REVOLUTION_ANGLE_RAD;
	}

	void IStepperDriver::setRevolutionSteps(uint_fast32_t revolutionSteps) {
		angleScale = revolutionSteps / REVOLUTION_ANGLE_RAD;
	};

	int_fast32_t IStepperDriver::angleToStep(float angle) const {
		return angleScale * angle;
	}

	float IStepperDriver::stepToAngle(int_fast32_t step) const {
		return step / angleScale;
	}

	float IStepperDriver::getSpeedAngle() const {
		return angleScale * getSpeedStep();
	}

	void IStepperDriver::setSpeedAngle(float speed) {
		setSpeedStep(angleToStep(speed));
	}
}
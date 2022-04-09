#include "stepper_driver/interface.hpp"

#include <Arduino.h>

namespace StepperDriver {
	// Base interface IStepperDriver

	int_fast32_t IStepperDriver::getCurrentAngle() const {
		return currentAngle;
	}

	void IStepperDriver::setCurrentAngle(int_fast32_t angle) {
		this->currentAngle = angle;
	}

	int_fast32_t IStepperDriver::getTargetAngle() const {
		return targetAngle;
	}

	void IStepperDriver::setTargetAngle(int_fast32_t angle) {
		this->targetAngle = angle;
	}

	void IStepperDriver::run() {
		while (currentAngle != targetAngle) {
			step();
		}
	}
}
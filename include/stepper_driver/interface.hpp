#ifndef _STEPPER_DRIVER_H
#define _STEPPER_DRIVER_H

#include <Arduino.h>

// Base abstract class IStepperDriver

namespace StepperDriver {
	class IStepperDriver {
	protected:
		int_fast32_t currentAngle, targetAngle;
	public:
		int_fast32_t getCurrentAngle() const;
		virtual void setCurrentAngle(int_fast32_t angle);
		int_fast32_t getTargetAngle() const;
		virtual void setTargetAngle(int_fast32_t angle);
		virtual void setSpeed(uint32_t speed) = 0;
		virtual void move() = 0;
	};
}

#endif

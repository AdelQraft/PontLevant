#ifndef _STEPPER_DRIVER_H
#define _STEPPER_DRIVER_H

#include <Arduino.h>

// Base abstract class IStepperDriver

namespace StepperDriver {
class IStepperDriver {
protected:
	int_fast32_t currentStep = 0, targetStep = 0;
	float angleScale;
public:
	int_fast32_t getCurrentStep() const;
	virtual void setCurrentStep(int_fast32_t);
	int_fast32_t getTargetStep() const;
	virtual void setTargetStep(int_fast32_t);

	float getCurrentAngle() const;
	void setCurrentAngle(float);
	float getTargetAngle() const;
	void setTargetAngle(float);

	uint_fast32_t getRevolutionSteps() const;
	virtual void setRevolutionSteps(uint_fast32_t);

	int_fast32_t angleToStep(float) const;
	virtual float stepToAngle(int_fast32_t) const;

	virtual uint_fast32_t getSpeedStep() const = 0;
	virtual void setSpeedStep(uint_fast32_t) = 0;

	float getSpeedAngle() const;
	void setSpeedAngle(float);

	virtual void run() = 0;
	virtual void nextStep() = 0;

	bool isOpen() const;
};
} // namespace StepperDriver

#endif

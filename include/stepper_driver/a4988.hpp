#ifndef _STEPPER_DRIVER_A4988_H
#define _STEPPER_DRIVER_A4988_H

#include "stepper_driver/interface.hpp"

namespace StepperDriver {
class A4988 : public IStepperDriver {
private:
	uint8_t stepPin, dirPin;
	uint_fast32_t speed;
	int_fast8_t increment;

	void updateDirection();
public:
	struct PinoutDescriptor {
	public:
		// TO DO: Implement sleepPin.
		uint8_t stepPin, dirPin;
		PinoutDescriptor(uint8_t stepPin, uint8_t dirPin);
	};

	static constexpr uint32_t DEFAULT_SPEED = 100;
	static constexpr uint_fast32_t REVOLUTION_STEPS = 200;

	A4988(const PinoutDescriptor&, uint_fast32_t revolutionSteps, uint32_t speed = DEFAULT_SPEED);
	void setCurrentStep(int_fast32_t) override;
	void setTargetStep(int_fast32_t) override;

	void setRevolutionSteps(uint_fast32_t) override;
	
	uint_fast32_t getSpeedStep() const override;
	void setSpeedStep(uint_fast32_t) override;

	void run();
};
} // namespace StepperDriver

#endif

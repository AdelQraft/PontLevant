#ifndef _STEPPER_DRIVER_A4988_H
#define _STEPPER_DRIVER_A4988_H

#include "stepper_driver/interface.hpp"

namespace StepperDriver {
	class A4988 : public IStepperDriver {
	private:
		uint8_t stepPin, dirPin;
		uint32_t halfSpeedDelay;
	public:
		struct PinoutDescriptor {
		public:
			// TO DO: Implement sleepPin.
			uint8_t stepPin, dirPin;
			PinoutDescriptor(uint8_t stepPin, uint8_t dirPin);
		};

		A4988(const PinoutDescriptor&, uint32_t speed = 10, int_fast32_t currentAngle = 0);
		uint32_t getHalfSpeedDelay() const;
		void setHalfSpeedDelay(uint32_t halfSpeedDelay);
		uint32_t getSpeed() const;
		void setSpeed(uint32_t speed);
		void move();
	};
}

#endif

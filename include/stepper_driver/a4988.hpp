#ifndef _STEPPER_DRIVER_A4988_H
#define _STEPPER_DRIVER_A4988_H

#include "stepper_driver/interface.hpp"

namespace StepperDriver {
	class A4988 : public IStepperDriver {
	private:
		uint8_t stepPin, dirPin;
		uint32_t halfSpeedDelay;
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

		A4988(const PinoutDescriptor&, uint32_t speed = DEFAULT_SPEED, int_fast32_t currentAngle = 0);
		void setCurrentAngle(int_fast32_t) override;
		void setTargetAngle(int_fast32_t) override;
		uint32_t getHalfSpeedDelay() const;
		void setHalfSpeedDelay(uint32_t);
		uint32_t getSpeed() const;
		void setSpeed(uint32_t);
		void step();
	};
}

#endif

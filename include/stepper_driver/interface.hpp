#ifndef _STEPPER_DRIVER_H
#define _STEPPER_DRIVER_H

#include <Arduino.h>

// Base abstract class IStepperDriver

namespace StepperDriver {
	class IStepperDriver {
	private:
		template <typename>
		struct argType;

		template <typename R, typename A>
		struct argType<R(A)> { using type = A; };

protected:
		int_fast32_t currentStep, targetStep;
		float angleScale;
	public:
		using delay_t = typename argType<decltype(delay)>::type;

		int_fast32_t getCurrentStep() const;
		virtual void setCurrentStep(int_fast32_t);
		int_fast32_t getTargetStep() const;
		virtual void setTargetStep(int_fast32_t);

		int_fast32_t getCurrentAngle() const;
		void setCurrentAngle(int_fast32_t);
		int_fast32_t getTargetAngle() const;
		void setTargetAngle(int_fast32_t);

		uint_fast32_t getRevolutionSteps() const;
		void setRevolutionSteps(uint_fast32_t);

		int_fast32_t angleToStep(int_fast32_t) const;
		int_fast32_t stepToAngle(int_fast32_t) const;

		virtual void setSpeed(delay_t speed) = 0;
		virtual void move() = 0;
	};
}

#endif

#ifndef _VILLE_CONNECTEE_MOVABLE_BRIDGE_H
#define _VILLE_CONNECTEE_MOVABLE_BRIDGE_H

#include <Arduino.h>
#include "stepper_driver/interface.hpp"

#ifdef _ESP
#include <type_traits>
#endif

template<typename StepperDriverT1, typename StepperDriverT2>
class MovableBridge {
#ifdef _ESP
	static_assert(std::is_base_of<StepperDriver::IStepperDriver, StepperDriverT1>::value, "StepperDriverT1 must inherit from StepperDriver::IStepperDriver");
	static_assert(std::is_base_of<StepperDriver::IStepperDriver, StepperDriverT2>::value, "StepperDriverT2 must inherit from StepperDriver::IStepperDriver"); 
#endif
private:
#	define callSteppersMethod(method, ...) { s1.method(__VA_ARGS__); s2.method(__VA_ARGS__); }	// Warning! Unsafe macro! Doesn't prevent expansion!

	StepperDriverT1 s1;
	StepperDriverT2 s2;

	int_fast32_t openAngle;

	void run() {
		debugPrintf("Run -- currentAngle: %d, targetAngle: %d\n", s1.getCurrentAngle(), openAngle);

		const int_fast32_t targetAngle = s1.getTargetAngle();
		while (s1.getCurrentAngle() != targetAngle) {
			s1.step();
			s2.step();
		}
	}
public:
	using PinoutDescriptor1 = typename StepperDriverT1::PinoutDescriptor;
	using PinoutDescriptor2 = typename StepperDriverT2::PinoutDescriptor;

	int_fast32_t getOpenAngle() const { return openAngle; };
	void setOpenAngle(int_fast32_t angle) { openAngle = angle; }
	uint32_t getSpeed() const { return s1.getSpeed(); };
	void setSpeed(int_fast32_t speed) { callSteppersMethod(setSpeed, speed); }

	MovableBridge(const PinoutDescriptor1& pd1, const PinoutDescriptor2& pd2, uint_fast32_t speed = StepperDriverT1::DEFAULT_SPEED)
		: s1(pd1, speed), s2(pd2, speed) {}

	void open() { callSteppersMethod(setTargetAngle, openAngle); run(); }

	void close() { callSteppersMethod(setTargetAngle, 0); run(); }

private:
#	undef callSteppersMethod
};

#endif

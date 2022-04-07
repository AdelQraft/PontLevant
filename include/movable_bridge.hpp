#ifndef _VILLE_CONNECTEE_MOVABLE_BRIDGE_H
#define _VILLE_CONNECTEE_MOVABLE_BRIDGE_H

#include <Arduino.h>
#include "stepper_driver/interface.hpp"

#include <type_traits>

template<typename StepperDriverT>
class MovableBridge {
	static_assert(std::is_base_of<StepperDriver::IStepperDriver, StepperDriverT>::value, "StepperDriverT must inherit from StepperDriver::IStepperDriver");
private:
#	define callSteppersMethod(method, ...) { s1.method(__VA_ARGS__); s2.method(__VA_ARGS__); }	// Warning! Unsafe macro!

	StepperDriverT s1, s2;
public:
	using PinoutDescriptor = typename StepperDriverT::PinoutDescriptor;

	int_fast32_t getOpenAngle() const { return s1.getTargetAngle(); };
	void setOpenAngle(int_fast32_t angle) { callSteppersMethod(setTargetAngle, angle); }
	void setSpeed(int_fast32_t speed) { callSteppersMethod(setSpeed, speed); }

	MovableBridge(const PinoutDescriptor& pd1, const PinoutDescriptor& pd2, uint_fast32_t speed = StepperDriverT::DEFAULT_SPEED)
		: s1(pd1, speed), s2(pd2, speed) {}

	void open() { callSteppersMethod(move); }
	void close() { callSteppersMethod(setTargetAngle, 0); callSteppersMethod(move); }

private:
#	undef callSteppersMethod
};

#endif

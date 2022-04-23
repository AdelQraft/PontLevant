#ifndef _VILLE_CONNECTEE_MOVABLE_BRIDGE_H
#define _VILLE_CONNECTEE_MOVABLE_BRIDGE_H

#include <Arduino.h>
#include "stepper_driver/interface.hpp"

#include <type_traits>
#include <thread>

template<typename StepperDriverT1, typename StepperDriverT2>
class MovableBridge {
	static_assert(std::is_base_of<StepperDriver::IStepperDriver, StepperDriverT1>::value, "StepperDriverT1 must inherit from StepperDriver::IStepperDriver");
	static_assert(std::is_base_of<StepperDriver::IStepperDriver, StepperDriverT2>::value, "StepperDriverT2 must inherit from StepperDriver::IStepperDriver"); 
private:
#	define callSteppersMethod(method, ...) { s1.method(__VA_ARGS__); s2.method(__VA_ARGS__); }	// Warning! Unsafe macro! Doesn't prevent expansion!

	StepperDriverT1 s1;
	StepperDriverT2 s2;

	float openAngle;

	void run() {
		s1.run();
		std::thread t1(&StepperDriverT1::run, &s1);
		std::thread t2(&StepperDriverT2::run, &s2);
		t1.join();
		t2.join();
	}
public:
	using PinoutDescriptor1 = typename StepperDriverT1::PinoutDescriptor;
	using PinoutDescriptor2 = typename StepperDriverT2::PinoutDescriptor;

	float getOpenAngle() const { return openAngle; }
	void setOpenAngle(float angle) { openAngle = angle; }
	uint_fast32_t getSpeedAngle() const { return s1.getSpeedAngle(); } // Remember, s1.getSpeed() == s2.getSpeed().
	void setSpeedAngle(uint_fast32_t speed) { callSteppersMethod(setSpeedAngle, speed); }

	MovableBridge(const typename StepperDriverT1::PinoutDescriptor& pd1, uint_fast32_t stepper1RevolutionSteps, const typename StepperDriverT2::PinoutDescriptor& pd2, uint_fast32_t stepper2RevolutionSteps, float speed = 4*PI)
		: s1(pd1, stepper1RevolutionSteps, speed), s2(pd2, stepper2RevolutionSteps, speed) {}

	void open() { callSteppersMethod(setTargetAngle, openAngle); run(); }

	void close() { callSteppersMethod(setTargetAngle, 0); run(); }

private:
#	undef callSteppersMethod
};

#endif

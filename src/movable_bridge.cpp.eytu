#include "movable_bridge.hpp"

// Warning! Unsafe macro! Use it with care!
#define callSteppersMethod(method, ...) { leftStepper.method(__VA_ARGS__); /*rightStepper.method(__VA_ARGS__);*/ }

MovableBridge::MovableBridge(int steps, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, long openAbsPos, long speed)
: leftStepper(steps, pin1, pin2, pin3, pin4)/*, rightStepper(steps, pin1, pin2, pin3, pin4)*/ {
	this->speed = speed;
	this->openAbsPos = openAbsPos;
	callSteppersMethod(setCurrentPosition, 0);
}

void MovableBridge::constSpeedMove(long absPos) {
	callSteppersMethod(moveTo, absPos);
	callSteppersMethod(setSpeed, speed);
	while (leftStepper.distanceToGo() > 0) callSteppersMethod(runSpeedToPosition);
}

void MovableBridge::accelMove(long absPos) {
	callSteppersMethod(runToPosition)
}

uint32_t MovableBridge::getOpenAbsPos() const {
	return openAbsPos;
}

void MovableBridge::setOpenAbsPos(uint32_t steps) {
	callSteppersMethod(move, steps);
}

void MovableBridge::setSpeed(float speed) {
	callSteppersMethod(setSpeed, speed);
}

void MovableBridge::setMaxSpeed(float speed) {
	callSteppersMethod(setMaxSpeed, speed);
}

void MovableBridge::setAcceleration(float accel = 0) {
	moveHandler = accel == 0 ? &constSpeedMove : &accelMove;
}

void MovableBridge::move(long absPos) {
	(this->*moveHandler)(absPos);
}

void MovableBridge::open() {
	move(openAbsPos);
}

void MovableBridge::close() {
	move(0);
}

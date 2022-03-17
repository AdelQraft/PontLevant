#ifndef _VILLE_CONNECTEE_MOVABLE_BRIDGE_H
#define _VILLE_CONNECTEE_MOVABLE_BRIDGE_H

#include <Arduino.h>
#include <AccelStepper.h>

class MovableBridge {
private:
	using move_handler_t = void (MovableBridge::*)(long);

	AccelStepper leftStepper/*, rightStepper*/;
	long speed, openAbsPos;
	move_handler_t moveHandler;
	void constSpeedMove(long absPos);
	void accelMove(long absPos);
public:
	MovableBridge(int steps, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, long openAbsPos, long speed = 500);
	uint32_t getOpenAbsPos() const;
	void setOpenAbsPos(uint32_t steps);
	void setSpeed(float speed);
	void setMaxSpeed(float speed);
	void setAcceleration(float accel = 0);
	void move(long absPos);
	void open();
	void close();
};

#endif

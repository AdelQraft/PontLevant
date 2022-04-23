#include <Arduino.h>

#include "movable_bridge.hpp"
#include "stepper_driver/a4988.hpp"

#include "debugging.hpp"

/*
constexpr uint8_t PIN_ENTER_A = 15,PIN_ENTER_B = 2, PIN_EXIT_A=13, PIN_EXIT_B=2;
constexpr uint8_t TRIG_PIN_A=18, ECHO_PIN_A=19,TRIG_PIN_B=2, ECHO_PIN_B=2;
int durationA, durationB;

CarCounting sensA(PIN_ENTER_A,PIN_EXIT_A), sensB(PIN_ENTER_B,PIN_EXIT_B);
BoatDectection detectionA(TRIG_PIN_A,ECHO_PIN_A), detectionB(TRIG_PIN_B,ECHO_PIN_B);
*/
//constexpr uint8_t PIN_ENTER_A = 26, PIN_EXIT_A = 27;
//CarCounting sensA(PIN_ENTER_A,PIN_EXIT_A);

// bridge.setOpenAngle sert à configurer l'angle d'ouverture. Augmenter si n'ouvre pas assez et diminuer si ouvre trop. Modifier le coefficient devant REVOLUTION_ANGLE dans la définition de REVOLUTION_ANGLE;
MovableBridge<StepperDriver::A4988, StepperDriver::A4988> bridge (
	StepperDriver::A4988::PinoutDescriptor(12, 14),
	200,
	StepperDriver::A4988::PinoutDescriptor(34, 35),
	200
);

void setup() {
	debugInit();
	// Objet pont levant

	bridge.setOpenAngle(15*2*PI);

	// initialize the switch pin as an input:
	//pinMode(sensA.getPinE(), INPUT);
	//pinMode(sensA.getPinS(), INPUT);
	// pinMode(sensB.getPinE(), INPUT);
	// pinMode(sensB.getPinS(), INPUT);
	//Serial.println("done");
}

void loop() {
	bridge.open();	// À configurer avec ALIVEcode.
	delay(5000);
	bridge.close(); // À configurer avec ALIVEcode.

	// --- Switch ---
	//Add or substract a car to the bridge
	//sensA.change(digitalRead(sensA.getPinE()),digitalRead(sensA.getPinS()));
	//sensB.change(digitalRead(sensB.getPinE()),digitalRead(sensB.getPinS()));
	//Serial.println(digitalRead(15));
    //debugPrintln(digitalRead(sensA.getPinE())); 

	//delay(100);
}

#include <Arduino.h>
//#include <ESP8266WiFi.h>
//#include <BlynkSimpleEsp8266.h>

#include "car_counting.hpp"
#include "boat_detection.hpp"

#include "movable_bridge.hpp"
#include "stepper_driver/a4988.hpp"

#include "debugging.hpp"

constexpr int_fast32_t REVOLUTION_ANGLE = 200;
constexpr int_fast32_t OPEN_ANGLE = 3 * REVOLUTION_ANGLE;

/*
const int PIN_ENTER_A = 15,PIN_ENTER_B = 2, PIN_EXIT_A=13, PIN_EXIT_B=2;
const int TRIG_PIN_A=18, ECHO_PIN_A=19,TRIG_PIN_B=2, ECHO_PIN_B=2;
int durationA,durationB;

CarCounting sensA(PIN_ENTER_A,PIN_EXIT_A), sensB(PIN_ENTER_B,PIN_EXIT_B);
BoatDectection detectionA(TRIG_PIN_A,ECHO_PIN_A), detectionB(TRIG_PIN_B,ECHO_PIN_B);
*/
const uint8_t PIN_ENTER_A = 27, PIN_EXIT_A=26;
CarCounting sensA(PIN_ENTER_A,PIN_EXIT_A);


void setup() {
	debugInit();
/*	
	StepperDriver::A4988 s(StepperDriver::A4988::PinoutDescriptor(14, 12), 250);
	s.setTargetAngle(1000 * OPEN_ANGLE);
	s.run();
*/

	// Objet pont levant
	MovableBridge<StepperDriver::A4988, StepperDriver::A4988> bridge (
		StepperDriver::A4988::PinoutDescriptor(14, 12),
		StepperDriver::A4988::PinoutDescriptor(2, 15),
		250	// Vitesse en steps/seconde.
	);
/*
	// bridge.setOpenAngle sert à configurer l'angle d'ouverture. Augmenter si n'ouvre pas assez et diminuer si ouvre trop. Modifier le coefficient devant REVOLUTION_ANGLE dans la définition de REVOLUTION_ANGLE;
	bridge.setOpenAngle(OPEN_ANGLE);
	bridge.open();
	delay(5000);
	bridge.close();
*/
	// initialize the switch pin as an input:
	pinMode(sensA.getPinE(), INPUT);
	pinMode(sensA.getPinS(), INPUT);
   // pinMode(sensB.getPinE(), INPUT);
   // pinMode(sensB.getPinS(), INPUT);
   Serial.println("done");
}

void loop() {
	// --- Switch ---
	//Add or substract a car to the bridge
	sensA.change(digitalRead(sensA.getPinE()),digitalRead(sensA.getPinS()));
	//sensB.change(digitalRead(sensB.getPinE()),digitalRead(sensB.getPinS()));
	//Serial.println(digitalRead(15));
    //debugPrintln(digitalRead(sensA.getPinE())); 





	delay(100);
}

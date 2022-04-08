#include <Arduino.h>
//#include <ESP8266WiFi.h>
//#include <BlynkSimpleEsp8266.h>

#include "car_counting.hpp"
#include "boat_detection.hpp"

#include "movable_bridge.hpp"
#include "stepper_driver/a4988.hpp"

#include "debugging.hpp"

constexpr size_t REVOLUTION_ANGLE = 200;
constexpr size_t OPEN_ANGLE = 3 * REVOLUTION_ANGLE;

/*
const int PIN_ENTER_A = 15,PIN_ENTER_B = 2, PIN_EXIT_A=13, PIN_EXIT_B=2;
const int TRIG_PIN_A=18, ECHO_PIN_A=19,TRIG_PIN_B=2, ECHO_PIN_B=2;
int durationA,durationB;

CarCounting sensA(PIN_ENTER_A,PIN_EXIT_A), sensB(PIN_ENTER_B,PIN_EXIT_B);
BoatDectection detectionA(TRIG_PIN_A,ECHO_PIN_A), detectionB(TRIG_PIN_B,ECHO_PIN_B);
*/
const int PIN_ENTER_A = 15,PIN_ENTER_B = 2, PIN_EXIT_A=13, PIN_EXIT_B=2;
CarCounting sensA(PIN_ENTER_A,PIN_EXIT_A), sensB(PIN_ENTER_B,PIN_EXIT_B);


void setup() {
	//debugInit();
	
	// Objet pont levant
	MovableBridge<StepperDriver::A4988> bridge = decltype(bridge) (
		decltype(bridge)::PinoutDescriptor(14, 12),
		decltype(bridge)::PinoutDescriptor(32, 33),	// Pas utilisé car l'un des drivers est brisé.
		250	// Vitesse en steps/seconde.
	);

	// bridge.setOpenAngle sert à configurer l'angle d'ouverture. Augmenter si n'ouvre pas assez et diminuer si ouvre trop. Modifier le coefficient devant REVOLUTION_ANGLE dans la définition de REVOLUTION_ANGLE;
	bridge.setOpenAngle(OPEN_ANGLE);
	bridge.open();
	delay(5000);
	bridge.close();
	

	// initialize the switch pin as an input:
   // pinMode(sensA.getPinE(), INPUT);
   // pinMode(sensA.getPinS(), INPUT);
   // pinMode(sensB.getPinE(), INPUT);
   // pinMode(sensB.getPinS(), INPUT);
	uint8_t c = 27;
   pinMode(c, INPUT);

}

void loop() {
	// --- Switch ---
	//Add or substract a car to the bridge
	sensA.change(digitalRead(sensA.getPinE()),digitalRead(sensA.getPinS()));
	//sensB.change(digitalRead(sensB.getPinE()),digitalRead(sensB.getPinS()));
	//Serial.println(digitalRead(15));

	uint8_t c = 27;
	pinMode(c, INPUT);
	//digitalWrite(c, HIGH);




	delay(100);

}

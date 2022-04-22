#include <Arduino.h>

#include "movable_bridge.hpp"
#include "stepper_driver/a4988.hpp"

constexpr uint8_t STEP_PIN = 12;
constexpr uint8_t DIR_PIN = 14;

constexpr int_fast32_t REVOLUTION_STEPS = 200;

/*
constexpr uint8_t PIN_ENTER_A = 15,PIN_ENTER_B = 2, PIN_EXIT_A=13, PIN_EXIT_B=2;
constexpr uint8_t TRIG_PIN_A=18, ECHO_PIN_A=19,TRIG_PIN_B=2, ECHO_PIN_B=2;
int durationA, durationB;

CarCounting sensA(PIN_ENTER_A,PIN_EXIT_A), sensB(PIN_ENTER_B,PIN_EXIT_B);
BoatDectection detectionA(TRIG_PIN_A,ECHO_PIN_A), detectionB(TRIG_PIN_B,ECHO_PIN_B);
*/
constexpr uint8_t PIN_ENTER_A = 26, PIN_EXIT_A = 27;
//CarCounting sensA(PIN_ENTER_A,PIN_EXIT_A);

void setup() {
	debugInit();

//	StepperDriver::A4988 s(StepperDriver::A4988::PinoutDescriptor(14, 12), 200, 20);
//	s.setTargetAngle(2 * PI);
//	s.run();

	// Objet pont levant
	MovableBridge<StepperDriver::A4988, StepperDriver::A4988> bridge (
		StepperDriver::A4988::PinoutDescriptor(14, 12),
		StepperDriver::A4988::PinoutDescriptor(2, 15),
		500	// Vitesse en steps/seconde.
	);

	// bridge.setOpenAngle sert à configurer l'angle d'ouverture. Augmenter si n'ouvre pas assez et diminuer si ouvre trop. Modifier le coefficient devant REVOLUTION_ANGLE dans la définition de REVOLUTION_ANGLE;
	bridge.setOpenAngle(20*2*PI);
	bridge.open();
	delay(5000);
	bridge.close();
	bridge.open();
	delay(5000);
	bridge.close();
*/
>>>>>>> f35a0966dde310a6d17a0f7098e5e739b10ca747

	// initialize the switch pin as an input:
	//pinMode(sensA.getPinE(), INPUT);
	//pinMode(sensA.getPinS(), INPUT);
	// pinMode(sensB.getPinE(), INPUT);
	// pinMode(sensB.getPinS(), INPUT);
	//Serial.println("done");
}

void loop() {
	// --- Switch ---
	//Add or substract a car to the bridge
	//sensA.change(digitalRead(sensA.getPinE()),digitalRead(sensA.getPinS()));
	//sensB.change(digitalRead(sensB.getPinE()),digitalRead(sensB.getPinS()));
	//Serial.println(digitalRead(15));
    //debugPrintln(digitalRead(sensA.getPinE())); 

	//delay(100);
}

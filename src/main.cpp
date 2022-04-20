#include <Arduino.h>
//#include <ESP8266WiFi.h>
//#include <BlynkSimpleEsp8266.h>

#include "car_counting.hpp"
#include "boat_detection.hpp"

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
//constexpr uint8_t PIN_ENTER_A = 33, PIN_EXIT_A = 32;
//CarCounting sensA(PIN_ENTER_A,PIN_EXIT_A);
const int dirPin = 12;
const int stepPin = 14;
const int dirPin2 = 15;
const int stepPin2 = 2;
const int stepsPerRevolution = 3200;

void setup() {
	debugInit();

	pinMode(stepPin, OUTPUT);
	pinMode(dirPin, OUTPUT);

	pinMode(stepPin2, OUTPUT);
	pinMode(dirPin2, OUTPUT);

/*
	pinMode(2, OUTPUT);
	digitalWrite(2, HIGH);
	
	StepperDriver::A4988 s(StepperDriver::A4988::PinoutDescriptor(14, 12), 200, 20);
	s.setTargetAngle(2 * PI);
	s.run();
*/
	// Objet pont levant
/*	MovableBridge<StepperDriver::A4988, StepperDriver::A4988> bridge (
		StepperDriver::A4988::PinoutDescriptor(14, 12),
		StepperDriver::A4988::PinoutDescriptor(2, 15),
		500	// Vitesse en steps/seconde.
	);

	// bridge.setOpenAngle sert à configurer l'angle d'ouverture. Augmenter si n'ouvre pas assez et diminuer si ouvre trop. Modifier le coefficient devant REVOLUTION_ANGLE dans la définition de REVOLUTION_ANGLE;
	bridge.setOpenAngle(PI);
	bridge.open();
	delay(5000);
	bridge.close();
*/
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

	  // Set motor direction clockwise

  // Spin motor slowly
	digitalWrite(dirPin, HIGH);
	digitalWrite(dirPin2, HIGH);

  for(int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin, HIGH);
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(1000);
  }
  delay(1000); // Wait a second
  
  // Set motor direction counterclockwise
  digitalWrite(dirPin, LOW);
  digitalWrite(dirPin2, LOW);

  // Spin motor quickly
  for(int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin, HIGH);
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(1000);
  }
  delay(1000); // Wait a 
}

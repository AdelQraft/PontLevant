#include <Arduino.h>
//#include <ESP8266WiFi.h>
//#include <BlynkSimpleEsp8266.h>

#include "car_counting.hpp"
#include "boat_detection.hpp"
#include "stepper_driver/a4988.hpp"

constexpr uint8_t STEP_PIN = 12;
constexpr uint8_t DIR_PIN = 14;

constexpr int_fast32_t REVOLUTION_STEPS = 200;

const int PIN_ENTER_A = 15,PIN_ENTER_B = 2, PIN_EXIT_A=13, PIN_EXIT_B=2;
const int TRIG_PIN_A=18, ECHO_PIN_A=19,TRIG_PIN_B=2, ECHO_PIN_B=2;
//int durationA,durationB;

CarCounting sensA(PIN_ENTER_A,PIN_EXIT_A), sensB(PIN_ENTER_B,PIN_EXIT_B);
//BoatDectection detectionA(TRIG_PIN_A,ECHO_PIN_A), detectionB(TRIG_PIN_B,ECHO_PIN_B);


void setup() {
	// Temporary.
	Serial.begin(9600);
	
	while (!Serial);

/*
	pinMode(STEP_PIN, OUTPUT);
	pinMode(DIR_PIN, OUTPUT);

	digitalWrite(DIR_PIN, HIGH);

	for (int x = 0; x < REVOLUTION_STEPS; x++) {
		digitalWrite(STEP_PIN, HIGH);
		delayMicroseconds(2000);
		digitalWrite(STEP_PIN, LOW);
		delayMicroseconds(2000);
	}*/

	 // initialize the switch pin as an input:
   	pinMode(sensA.getPinE(), INPUT);
	pinMode(sensA.getPinS(), INPUT);
   // pinMode(sensB.getPinE(), INPUT);
   // pinMode(sensB.getPinS(), INPUT);

	// initialize the captor pin :
	//pinMode(TRIG_PIN_A, OUTPUT); 
    //pinMode(ECHO_PIN_A, INPUT); 
	//pinMode(detectionB.getTrigPin(), OUTPUT);
    //pinMode(detectionB.getEchoPin(), INPUT); 


	//StepperDriver::A4988 stepper(StepperDriver::A4988::PinoutDescriptor(12, 14));
	//stepper.setTargetAngle(8 * REVOLUTION_STEPS);
	//stepper.move();

	uint8_t c = 15;
	pinMode(c, INPUT);
	//digitalWrite(c, HIGH);




	Serial.println("done");
}

void loop(){
	int interDelay = 0;

	// --- Switch ---
	//Add or substract a car to the bridge
	sensA.change(digitalRead(sensA.getPinE()),digitalRead(sensA.getPinS()));
	//sensB.change(digitalRead(sensB.getPinE()),digitalRead(sensB.getPinS()));
	//Serial.println(digitalRead(15));

	// --- Ultrasonic Captor ---

/*
	// More generic

	MovableBridge<StepperDriver::A4988> bridge = decltype(bridge) (
		decltype(bridge)::PinoutDescriptor(23, 22),
		decltype(bridge)::PinoutDescriptor(21, 19)
	);
*/
/*
	MovableBridge<StepperDriver::A4988> bridge (
		StepperDriver::A4988::PinoutDescriptor(12, 14),
		StepperDriver::A4988::PinoutDescriptor(21, 19),
		REVOLUTION_STEPS
	);

	bridge.open();
	delay(5000);
	bridge.close();
*/



	delay(100-interDelay);
}	// Not used.

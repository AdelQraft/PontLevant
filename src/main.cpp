#include <Arduino.h>
//#include "movable_bridge.hpp"
#include <AccelStepper.h>
#include "car_counting.hpp" 
#include "boat_detection.hpp"


constexpr long ROTATION_STEPS = 2 << 9;

AccelStepper stepper(AccelStepper::FULL4WIRE, 5, 3, 4, 2);

const int PIN_ENTER_A,PIN_ENTER_B, PIN_EXIT_A, PIN_EXIT_B;
int stateEnterA, stateEnterB, stateExitA, stateExitB;
const int TRIG_PIN_A, ECHO_PIN_A,TRIG_PIN_B, ECHO_PIN_B;
int trigPin, echoPin;
int durationA,durationB;

CarCounting sensA(PIN_ENTER_A,PIN_EXIT_A), sensB(PIN_ENTER_B,PIN_EXIT_B);
BoatDectection detectionA(TRIG_PIN_A,ECHO_PIN_A), detectionB(TRIG_PIN_B,ECHO_PIN_B);

#define start setup
void start() {
	Serial.begin(9600);
	while (!Serial);

	stepper.setMaxSpeed(1000.0); // set the maximum speed
	//stepper.setAcceleration(0); // set acceleration
	stepper.setCurrentPosition(0); // set position
	stepper.moveTo(ROTATION_STEPS);
	stepper.setSpeed(500); // set initial speed

	// MovableBridge bridge(2048, 8, 10, 9, 11, 512, 512, 100);
	// bridge.open();

	while (stepper.distanceToGo() > 0) stepper.runSpeedToPosition();

	// initialize the switch pin as an input:
 	pinMode(sensA.getPinE(), INPUT);
	pinMode(sensA.getPinS(), INPUT);
	pinMode(sensB.getPinE(), INPUT);
	pinMode(sensB.getPinS(), INPUT);

	// initialize the captor pin :
	pinMode(detectionA.getTrigPin(), OUTPUT); 
    pinMode(detectionA.getEchoPin(), INPUT); 
	pinMode(detectionB.getTrigPin(), OUTPUT);
    pinMode(detectionB.getEchoPin(), INPUT); 
	 
	Serial.println("done");
}

void loop() {

	//Add or substract a car to the bridge
	sensA.change(digitalRead(sensA.getPinE()),digitalRead(sensA.getPinS()));
	sensB.change(digitalRead(sensB.getPinE()),digitalRead(sensB.getPinS()));

	// Clears the trigPin condition
	digitalWrite(trigPin, LOW);
  	delayMicroseconds(2);
  	// Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  	digitalWrite(trigPin, HIGH);
  	delayMicroseconds(10);
  	digitalWrite(trigPin, LOW);
	
  	durationA = pulseIn(sensA.getPinE(), HIGH);
	durationB = pulseIn(sensB.getPinE(), HIGH);
	//Boat detection	
  	if (detectionA.detection(durationA * 0.034 / 2)||detectionB.detection(durationB * 0.034 / 2)){
		  if (sensA.isEmpty()&&sensB.isEmpty()){
			  //Ouvrir le pont
		  };
	}; 

	


}	// Not used.

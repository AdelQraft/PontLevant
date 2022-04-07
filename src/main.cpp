#include <Arduino.h>

#include "movable_bridge.hpp"
#include "stepper_driver/a4988.hpp"

#include "debugging.hpp"

constexpr size_t REVOLUTION_ANGLE = 200;
constexpr size_t OPEN_ANGLE = 2 * REVOLUTION_ANGLE;

void setup() {
	debugInit();

	// Objet pont levant
	MovableBridge<StepperDriver::A4988> bridge = decltype(bridge) (
		decltype(bridge)::PinoutDescriptor(14, 12),
		decltype(bridge)::PinoutDescriptor(32, 33),	// Pas utilisé car l'un des drivers est brisé.
		250
	);

	// bridge.setOpenAngle sert à configurer l'angle d'ouverture. Augmenter si n'ouvre pas assez et diminuer si ouvre trop. Modifier le coefficient devant REVOLUTION_ANGLE dans la définition de REVOLUTION_ANGLE;
	bridge.setOpenAngle(OPEN_ANGLE);
	bridge.open();
	delay(5000);
	bridge.close();
}

void loop() {}

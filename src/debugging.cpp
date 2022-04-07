#include "debugging.hpp"

#include <Arduino.h>

void _debugInit() {
	static bool inited = false;
	if (!inited) {
		Serial.begin(115200);
		while (!Serial);
	}
	debugPrintf("\n\nSerial debugging output:\n\n");
}
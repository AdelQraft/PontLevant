#ifndef _DEBUGGING_H
#define _DEBUGGING_H

#include <Arduino.h>

#ifdef _DEBUG
	void _debugInit();
#	define debugInit _debugInit
#	define debugPrint Serial.print
#	define debugPrintln Serial.println
#ifdef _ESP
#	define debugPrintf Serial.printf
#else
#	define debugPrintf(...)
#endif
#else
#	define debuggingInit()
#	define debugPrint(...)
#	define debugPrintln(...)
#	define debugPrintf(...)
#endif

#endif

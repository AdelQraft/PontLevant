#include <Arduino.h>
//#include <WebSocketsClient.h>
#include <ArduinoJson.h>
//#include <ESP8266WiFi.h>
//#include <BlynkSimpleEsp8266.h>

#include "car_counting.hpp"
#include "boat_detection.hpp"

#include "movable_bridge.hpp"
#include "stepper_driver/a4988.hpp"

#include "debugging.hpp"
#include "../lib/arduinoWebSockets-master/src/WebSocketsClient.h"
#include "../lib/ArduinoJson/src/ArduinoJson.h"

const char *ssid = "robot03";
const char *password = "alive160";

// const char *ssid = "LRIMA_2.4";
// const char *password = "LRIMA_SWAG_24";

constexpr uint8_t PIN_ENTER_A = 15, PIN_EXIT_A = 2;
// constexpr uint8_t TRIG_PIN_A = 18, ECHO_PIN_A = 19, TRIG_PIN_B = 2, ECHO_PIN_B = 2;
int durationA, durationB;

CarCounting sensA(PIN_ENTER_A, PIN_EXIT_A);
// BoatDectection detectionA(TRIG_PIN_A, ECHO_PIN_A), detectionB(TRIG_PIN_B, ECHO_PIN_B);

// constexpr uint8_t PIN_ENTER_A = 33, PIN_EXIT_A = 32;
const int dirPin = 12;
const int stepPin = 14;
const int dirPin2 = 15;
const int stepPin2 = 2;
const int stepsPerRevolution = 3200;

// constexpr uint8_t PIN_ENTER_A = 26, PIN_EXIT_A = 27;
// CarCounting sensA(PIN_ENTER_A,PIN_EXIT_A);

// bridge.setOpenAngle sert à configurer l'angle d'ouverture. Augmenter si n'ouvre pas assez et diminuer si ouvre trop. Modifier le coefficient devant REVOLUTION_ANGLE dans la définition de REVOLUTION_ANGLE;
MovableBridge<StepperDriver::A4988, StepperDriver::A4988> bridge(
		StepperDriver::A4988::PinoutDescriptor(12, 14),
		200,
		StepperDriver::A4988::PinoutDescriptor(33, 32),
		200);

WebSocketsClient webSocket;
// WiFiClient client;

const char *path = "/";
char host[] = "24.202.54.51";
int port = 8881;

#define Serial Serial
// events
#define EVT_CONNECT_OBJ "connect_object"
#define EVT_CONNECT_SUCCESS "connect_success"
#define EVT_ERROR "error"
#define EVT_UPDATE "update_doc"
#define EVT_ON_RECV "receive_action"
#define EVT_ACTION_DONE "action_done"
#define EVT_PONG "pong"
#define EVT_PING "ping"

bool readyToGo = false;

/**
 * @brief This function should NOT be called manually
 *
 * @param eventName
 */
void _sendEvent(const char *eventName, const StaticJsonDocument<256> &responseData)
{
	StaticJsonDocument<256> doc;
	doc["event"] = eventName;
	doc["data"] = responseData;
	String eventSerialized;
	serializeJson(doc, eventSerialized);
	doc.clear();
	webSocket.sendTXT(eventSerialized);
}

void wait(uint16_t waitTime)
{
	uint16_t maxTimeBetweenUpdates = 2000;

	if (waitTime <= maxTimeBetweenUpdates)
	{
		Serial.println("Minimum treshold not reached");
		Serial.println(waitTime);
		delay(waitTime);
	}
	else
	{
		uint8_t nbUpdates = waitTime / maxTimeBetweenUpdates + 1;
		Serial.println("Number of iterations");
		Serial.println(nbUpdates);
		for (uint8_t i = 0; i < nbUpdates; i++)
		{
			if (i + 1 == nbUpdates)
			{
				Serial.println(waitTime - (uint16_t)(nbUpdates - 1) * maxTimeBetweenUpdates);
				delay(waitTime - (uint16_t)(nbUpdates - 1) * maxTimeBetweenUpdates);
			}
			else
			{
				Serial.println(maxTimeBetweenUpdates);
				delay(maxTimeBetweenUpdates);
			}
			webSocket.loop();
		}
	}
}

void webSocketEvent(WStype_t type, uint8_t *payload, size_t length)
{
	switch (type)
	{
	case WStype_DISCONNECTED:
		Serial.printf("[WSc] Disconnected!\n");
		break;
	case WStype_CONNECTED:
	{
		Serial.printf("[WSc] Connected to url: %s\n", payload);
		webSocket.sendTXT(
				R"({"event": "connect_object", "data": { "id": "27d8ec40-4504-459b-98d7-d32a36d92d5f"}})");
		break;
	}
	case WStype_TEXT:
	{
		StaticJsonDocument<256> doc;
		Serial.printf("[WSc] get text: %s\n", payload);
		doc.clear();
		deserializeJson(doc, (char *)payload);
		String event = String(doc["event"].as<const char *>());

		// ping
		if (event == EVT_PING || event == "")
		{
			webSocket.sendTXT(R"({"event": "pong"})");
			break;
		}

		if (event == EVT_CONNECT_SUCCESS && !readyToGo)
		{
			readyToGo = true;
			// TODO register listeners
			Serial.println("Connected to ALIVEcode");
			// voiture.forward(100);
			break;
		}
		else if (event == EVT_ERROR)
		{
			// TODO handle errors
			Serial.println("Error received '");
			Serial.print(event);
			Serial.print("': ");
			Serial.print(doc["data"].as<const char *>());
			break;
		}

		if (!readyToGo)
		{
			break;
		}

		Serial.println(event);
		// TODO handle callbacks
		if (event == EVT_ON_RECV)
		{
			byte actionId = doc["data"]["id"];
			switch (actionId)
			{
			case 0:
				bridge.close();
				webSocket.sendTXT(
						R"({"event": "update_doc","data": {"fields": {"/document/pont/ouvert": false}}})");
				break;
			case 1:
				webSocket.sendTXT(
						R"({"event": "update_doc","data": {"fields": {"/document/pont/ouvert": true}}})");
				bridge.open();
				break;
			default:
				break;
			}
			Serial.println("DONE");
			StaticJsonDocument<256> responseData;
			responseData["actionId"] = actionId;
			responseData["value"] = NULL;
			_sendEvent(EVT_ACTION_DONE, responseData);
			responseData.clear();
			doc.clear();

			webSocket.loop();
		}
		break;
	}
	case WStype_BIN:
		Serial.printf("[WSc] get binary length: %zu\n", length);
		// hexdump(payload, length);

		// send data to server
		// webSocketTXT.sendBIN(payload, length);
		break;
	case WStype_ERROR:
	case WStype_FRAGMENT_TEXT_START:
	case WStype_FRAGMENT_BIN_START:
	case WStype_FRAGMENT:
	case WStype_FRAGMENT_FIN:
		break;
	case WStype_PING:
		break;
	case WStype_PONG:
		break;
	}
}

void setup()
{
	debugInit();

	/*WiFi.begin(ssid, password);

	uint32_t notConnectedCounter = 0;
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(1000);
		Serial.print(".");
		notConnectedCounter++;
		if (notConnectedCounter > 10)
		{ // Reset board if not connected after 10s
			Serial.println("Resetting due to Wifi not connecting...");
			ESP.restart();
		}
	}
	Serial.println("Connection au reseau reussie!");*/

	pinMode(stepPin, OUTPUT);
	pinMode(dirPin, OUTPUT);

	pinMode(stepPin2, OUTPUT);
	pinMode(dirPin2, OUTPUT);

	// initialize the switch pin as an input:
	pinMode(sensA.getPinE(), INPUT);
	pinMode(sensA.getPinS(), INPUT);
	// event handler
	// webSocket.onEvent(webSocketEvent);

	// server address, port and URL
	// webSocket.begin(host, port, path);

	// try every 7000 again if connection has failed
	// webSocket.setReconnectInterval(7000);

	// Objet pont levant
	bridge.setOpenAngle(10 * 2 * PI);
}

uint8_t nbCarsOnTheBridge = 0;
uint8_t newNbCarsOnTheBridge = 0;

void loop()
{
	// --- Switch ---
	// Add or substract a car to the bridge
	sensA.change(digitalRead(sensA.getPinE()), digitalRead(sensA.getPinS()));
	Serial.print("Cars nb: ");
	Serial.println(sensA.getCarNumber());

	newNbCarsOnTheBridge = sensA.getCarNumber();
	if (newNbCarsOnTheBridge != nbCarsOnTheBridge)
	{
		nbCarsOnTheBridge = newNbCarsOnTheBridge;

		StaticJsonDocument<256> doc;
		StaticJsonDocument<256> fields;
		fields["/document/pont/cars"] = nbCarsOnTheBridge;
		doc.clear();
		doc["event"] = "update_doc";
		doc["fields"] = fields;

		String txt;
		serializeJson(doc, txt);
		webSocket.sendTXT(txt);
	}
	// Serial.println(digitalRead(15));
	// debugPrintln(digitalRead(sensA.getPinE()));

	webSocket.loop();
	delay(100);
}
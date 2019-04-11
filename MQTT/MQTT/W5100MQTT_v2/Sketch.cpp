
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include "CAN.h"
#include "account_Buero.h"

#define RELAIS_PIN 8
//#define CAN_SCHIELD_SPI_CS 2 //Arduino Zählweise Pin 2 wird als CS Leitung benutzt
//#define SPI_CAN_SETTINGS CAN_SCHIELD_SPI_CS, SPISettings(4000000, MSBFIRST, SPI_MODE0)

			// Update these with values suitable for your network.
			byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
			IPAddress ip(HUB_IP);
			//const char* server = "messtechnik.w-hs.de";
			IPAddress server(MQTT_SERVERIP);
			//IPAddress server(192, 168, 0, 2);
			char mqtt_user[] = USERNAME;
			char mqtt_password[] = PASSWORD;

void callback(char* topic, byte* payload, unsigned int length) {
	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("] ");
	for (int i=0;i<length;i++) {
		Serial.print((char)payload[i]);
	}
	//Vorsicht ggf. negierte Logik, Status der LED leuchtet nun wenn payload[0] == '1'
	if((char)payload[0] == '1')
	{
		digitalWrite(RELAIS_PIN, LOW);
	}
	else
	{
		digitalWrite(RELAIS_PIN, HIGH);
	}
	Serial.println();
}

EthernetClient ethClient;
PubSubClient mqttClient(ethClient);

void reconnect() {
	// Loop until we're reconnected
	while (!mqttClient.connected()) {
		Serial.print("Attempting MQTT connection...");
		// Attempt to connect
		if (mqttClient.connect("arduinoClient", mqtt_user, mqtt_password)) {
			Serial.println("connected");
			// Once connected, publish an announcement...
			mqttClient.publish("outTopic","hello WHS");
			// ... and resubscribe
			mqttClient.subscribe("inTopic");
			} else {
			Serial.print("failed, rc=");
			Serial.print(mqttClient.state());
			Serial.println(" try again in 5 seconds");
			// Wait 5 seconds before retrying
			delay(5000);
		}
	}
}

void setup()
{
	pinMode(RELAIS_PIN, OUTPUT);
	Serial.begin(9600);
	Serial.println("Arduino started");
	mqttClient.setServer(server, 1883);
	mqttClient.setCallback(callback);
	Serial.println("MQTT initialisiert");
	//Ethernet.begin(mac);
	Ethernet.begin(mac, ip);
	Serial.println("Ethernet.begin()");
	// Allow the hardware to sort itself out
	delay(1500);
	
	    // initialisieren des MCP2515
/*	      if (!CAN.begin(500E3)) {
		      Serial.println("Starting CAN failed!");
		      while (1);
	      }*/
}

void loop()
{
	if (!mqttClient.connected()) {
		reconnect();
	}
	mqttClient.loop();
	mqttClient.publish("outTopic","hello world");
/*
  // send packet: id is 11 bits, packet can contain up to 8 bytes of data
  Serial.print("Sending packet ... ");

  CAN.beginPacket(0x10); //Das ist die Package ID
  CAN.write('G');
  CAN.write('u');
  CAN.write('t');
  CAN.write('e');
  CAN.write('n');
  CAN.endPacket();
  Serial.println("done");
  CAN.beginPacket(0x11); //Das ist die Package ID
  CAN.write('h');
  CAN.write('e');
  CAN.write('l');
  CAN.write('l');
  CAN.write('o');
  CAN.endPacket();
  Serial.println("done");
  delay(1000);
  CAN.beginPacket(0x12); //Das ist die Package ID
  CAN.write('w');
  CAN.write('o');
  CAN.write('r');
  CAN.write('l');
  CAN.write('d');
  CAN.endPacket();
  Serial.println("done");
  delay(1000); 
  CAN.beginPacket(0x13); //Das ist die Package ID
  CAN.write('T');
  CAN.write('a');
  CAN.write('g');
  CAN.endPacket();
  Serial.println("done");
  

  // send extended packet: id is 29 bits, packet can contain up to 8 bytes of data
  Serial.print("Sending extended packet ... ");

  CAN.beginExtendedPacket(0xabcdef);
  CAN.write('w');
  CAN.write('o');
  CAN.write('r');
  CAN.write('l');
  CAN.write('d');
  CAN.endPacket();

  Serial.println("done");
*/
  delay(5000);

}



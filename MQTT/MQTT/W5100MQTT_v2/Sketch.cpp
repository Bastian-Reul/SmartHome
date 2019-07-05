
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "CAN.h"
#include "account_Labor.h"
#include "Hausbus.h"
#include "Pin_ATMEGA328.h"
#include "Aktor.h"


uint32_t CAN_Buffer[20];
uint32_t CAN_UID_List[3] = {
	/*	0	*/					ID_02_Keller_1_Bastelkeller_Lichtschalter_ROT,
	/*	1	*/					ID_02_Keller_1_Bastelkeller_Lichtschalter_Gruen,
	/*	2	*/					ID_02_Keller_1_Bastelkeller_Lichtschalter_BLAU,
	/*	3	*/		//			UID_MASK_ZERO,
	/*	4	*/		//			UID_MASK_ZERO,
	/*	5	*/		//			UID_MASK_ZERO,
	/*	6	*/		//			UID_MASK_ZERO,
	/*	7	*/		//			UID_MASK_ZERO,
	/*	8	*/		//			UID_MASK_ZERO,
	/*  9	*/		//			UID_MASK_ZERO,
	/* 10	*/		//			UID_MASK_ZERO,
	/* 11	*/		//			UID_MASK_ZERO,
	/* 12	*/		//			UID_MASK_ZERO,
	/* 13	*/		//			UID_MASK_ZERO,
	/* 14	*/		//			UID_MASK_ZERO,
	/* 15	*/		//			UID_MASK_ZERO,
	/* 16	*/		//			UID_MASK_ZERO,
	/* 17	*/		//			UID_MASK_ZERO,
	/* 18	*/		//			UID_MASK_ZERO,
	/* 19	*/		//			UID_MASK_ZERO

};

//char input[] = {"_Topic":"Test/objects/Aktor1","_status":false,"_schaltvorgaenge":2,"Adresse":739,"_toggle_trigger":true};
		Aktor Aktor1;




//#define RELAIS_PIN 8
//#define CAN_SCHIELD_SPI_CS 2 //Arduino Zählweise Pin 2 wird als CS Leitung benutzt
//#define SPI_CAN_SETTINGS CAN_SCHIELD_SPI_CS, SPISettings(4000000, MSBFIRST, SPI_MODE0)

			// Update these with values suitable for your network.
			byte mac[]    = {  0xDA, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
			//byte ip[] = {HUB_IP};
			IPAddress ip(HUB_IP);
			IPAddress server(MQTT_SERVERIP);
			IPAddress gateway(GatewayWHS);
			IPAddress subnet(SubnetWHS);
			//IPAddress DNSipServer(DNS_ServerBuero);
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
	/*		StaticJsonDocument<116> doc;
	deserializeJson(doc, payload);
	    Aktor1._Topic = doc["_Topic"];
	    Aktor1._status = doc["_status"];
	    Aktor1._schaltvorgaenge = doc["_schaltvorgaenge"];
	    Aktor1._toggle_trigger = doc["_toggle_trigger"];
	    Aktor1.Adresse = doc["Adresse"];*/
	
	//if((char)payload[0] == '1')
	if(Aktor1._toggle_trigger)
	{
		//wenn in Erdgeschoss/Wohnzimmer/Deckenlicht eine 1 steht, dann per CAN das Kommando für Licht einschalten senden
		Serial.println("Licht wird angeschaltet");
		CAN.beginExtendedPacket(ID_01_Keller_1_Bastelkeller_Licht);
		CAN.write(Kommando_Licht_toggle);
		CAN.endPacket();
	}
	else
	{
		//wenn in Erdgeschoss/Wohnzimmer/Deckenlicht etwas anderes steht, dann per CAN das Kommando für Licht ausschalten senden
		Serial.println("Licht wird ausgeschaltet");
		CAN.beginExtendedPacket(ID_01_Keller_1_Bastelkeller_Licht);
		CAN.write(Kommando_Licht_aus);
		CAN.endPacket();		
	}
	Serial.println();
}

EthernetClient ethClient;
//PubSubClient mqttClient(ethClient);
/*
void reconnect() {
	// Loop until we're reconnected
	while (!mqttClient.connected()) {
		Serial.print("Attempting MQTT connection...");
		// Attempt to connect
		if (mqttClient.connect("arduinoClient", mqtt_user, mqtt_password)) {
			Serial.println("connected");
			// Once connected, publish an announcement...
			mqttClient.publish("outTopic","toggle");
			// ... and resubscribe
			//mqttClient.subscribe("Erdgeschoss/Wohnzimmer/Deckenlicht");
			mqttClient.subscribe("Test/objects/Aktor1");
			} else {
			Serial.print("failed, rc=");
			Serial.print(mqttClient.state());
			Serial.println(" try again in 5 seconds");
			// Wait 5 seconds before retrying
			delay(5000);
		}
	}
}*/

void setup()
{
//	pinMode(RELAIS_PIN, OUTPUT);
	Serial.begin(9600);
	Serial.println("Arduino started");
		

	Ethernet.begin(mac, ip, gateway, subnet);
	//Ethernet.begin(mac); //IP Adresse per DHCP holen klappt bei Philipp
	Serial.println("Ethernet wurde gestartet");

	// Allow the hardware to sort itself out
	delay(5000);
		Serial.print("IP Adresse Arduino: ");
		Serial.println(Ethernet.localIP());
		/*-------------------05.07.2019
		mqttClient.setServer(server, 1883);
		mqttClient.setCallback(callback);
		Serial.println("MQTT initialisiert");
	
	  // start the CAN bus at 500 kbps
	  if (!CAN.begin(500E3)) {
		  Serial.println("Starting CAN failed!");
		  while (1);
	  }
		*///-------------------05.07.2019
}

void loop()
{	/*-------------------05.07.2019
	if (!mqttClient.connected()) {
		reconnect();
	}
	mqttClient.loop();
	*///-------------------05.07.2019



	//mqttClient.publish("outTopic","hello world");
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



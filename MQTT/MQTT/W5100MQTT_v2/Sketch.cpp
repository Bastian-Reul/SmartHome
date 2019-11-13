
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include "CAN.h"
#include "src/account_Labor.h"
#include "Hausbus.h"
#include "Pin_ATMEGA328.h"
#include "Aktor.h"
#include "../ArduinoCore/include/core/Arduino.h"
#include <stdio.h> 
//#include "src/account_Home.h"

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

char testinput[] =	{"\"_Topic\":\"Test/objects/Aktor1\",\"_status\":false,\"_schaltvorgaenge\":2,\"Adresse\":739,\"_toggletrigger\":true"};
	
		Aktor Aktor1;




//#define RELAIS_PIN 8
//#define CAN_SCHIELD_SPI_CS 2 //Arduino Zählweise Pin 2 wird als CS Leitung benutzt
//#define SPI_CAN_SETTINGS CAN_SCHIELD_SPI_CS, SPISettings(4000000, MSBFIRST, SPI_MODE0)

			// Update these with values suitable for your network.
			byte mac[]    = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
			//byte ip[] = {HUB_IP};
			IPAddress ip_WHS(HUB_IP);
			IPAddress google = { 64, 233, 187, 99 }; // Google
			//IPAddress server_WHS(MQTT_SERVERIP);
			const char MQTT_SERVER_Adress[]  = MQTT_SERVER_Adress_Home;
			IPAddress gateway_WHS(Gateway_Labor);
			IPAddress subnet_WHS(Subnet_Labor);
			IPAddress DNS_Server_WHS(DNS_Server_Labor);
			
			//IPAddress DNSipServer(DNS_ServerBuero);
			//IPAddress server(192, 168, 0, 2);
			const char mqtt_user[] = USERNAME;
			const char mqtt_password[] = PASSWORD;
			

void callback(char* topic, byte* payload, unsigned int length) {
	payload[length] = '\0';
	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("] ");
	for (int i=0;i<length;i++) {
		Serial.print((char)payload[i]);
	}
	Serial.println("JSON_2_Aktor wird aufgerufen:");
	if (Aktor1.JSON_2_Aktor((char*)payload))
	{
		Serial.println("ungueltiger JSON Code");
	} 
	else
	{
		if(Aktor1._toggletrigger)
		{
			Serial.println("Licht wird getoggelt");
			//CAN.beginExtendedPacket(ID_01_Keller_1_Bastelkeller_Licht);
			//CAN.write(Kommando_Licht_toggle);
			//CAN.endPacket();
			Aktor1._toggletrigger = false;
		}
		else
		{
			Serial.println("Licht bleibt im alten Status");
		/*	CAN.beginExtendedPacket(ID_01_Keller_1_Bastelkeller_Licht);
			CAN.write(Kommando_Licht_aus);
			CAN.endPacket();*/
		}
	}

	Serial.println("...warte...");

}
EthernetClient ConnectionTestClient;
EthernetClient ethClient;
PubSubClient mqttClient(ethClient);

void reconnect() {
	// Loop until we're reconnected
	while (!mqttClient.connected()) {
		Serial.print("Attempting MQTT connection...");
		// Attempt to connect
		if (mqttClient.connect("Arduino", mqtt_user, mqtt_password)) {
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
}

void setup()
{
//	pinMode(RELAIS_PIN, OUTPUT);
	Serial.begin(57600);
	Serial.println("Arduino started");
		
		
		//  void begin(uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server, IPAddress gateway, IPAddress subnet);
		//Unbedingt diese Reihenfolge beachten, DNS Server und IP Adresse sind vertauscht!!!!!!!
		//Ethernet.begin(mac, DNS_Server_WHS, ip_WHS, gateway_WHS, subnet_WHS);
		Ethernet.begin(mac, ip_WHS, DNS_Server_WHS, gateway_WHS, subnet_WHS);
		//Ethernet.begin(mac); //IP Adresse per DHCP holen klappt bei Philipp
		Serial.println("Ethernet wurde gestartet");
		
		ConnectionTestClient.connect(google, 80);
		delay(1000);
		  if (ConnectionTestClient.connected()) {
			  Serial.println("connected");
			  ConnectionTestClient.println("GET /search?q=arduino HTTP/1.0");
			  ConnectionTestClient.println();
			  } else {
			  Serial.println("connection failed");
		  }
		  ConnectionTestClient.stop();
		
	//mqttClient.setServer(server_WHS, 1883);
	mqttClient.setServer(MQTT_SERVER_Adress, 1883);
	mqttClient.setCallback(callback);
	Serial.println("MQTT initialisiert");
	//Serial.println(MQTT_VERSION);
			


	// Allow the hardware to sort itself out
	delay(5000);
		Serial.print("IP Adresse Arduino: ");
		Serial.println(Ethernet.localIP());
		Serial.print("Gateway: ");
		Serial.println(Ethernet.gatewayIP());
		
	  // start the CAN bus at 500 kbps
	/*  if (!CAN.begin(500E3)) {
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
 // delay(5000);

}



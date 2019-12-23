/*
 * Hub.cpp
 *
 * Created: 13.11.2019 11:41:37
 * Author : Bastian
 */ 

#include <avr/io.h>
#include "src/Ethernet/Ethernet.h"


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


int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
    }
}


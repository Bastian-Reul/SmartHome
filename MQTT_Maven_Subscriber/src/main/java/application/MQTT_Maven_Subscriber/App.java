package application.MQTT_Maven_Subscriber;


import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;

import com.fasterxml.jackson.core.JsonGenerationException;
import com.fasterxml.jackson.databind.JsonMappingException;
import com.fasterxml.jackson.databind.ObjectMapper;

import application.MQTT_Maven_Subscriber.Aktor;
import application.MQTT_Maven_Subscriber.account;

import java.io.*;
import java.io.IOException;
import java.util.Random; 





//Hier weiterschauen
//https://gist.github.com/m2mIO-gister/5275324

public class App implements MqttCallback {


	MqttClient sampleClient;
	account Bueroaccount = new account();

	Aktor LED_Rot = new Aktor();
	Sensor Taster_1 = new Sensor();
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	
	public App()
	{
		
	}
	
	
	public String CreateUID()
	{
		int zufallszahl; 
		zufallszahl = (int)(Math.random() * 1000) + 1; 
		System.out.println(zufallszahl);
		String JavaInitClientUUID = "InitClient" + Integer.toString(zufallszahl);
		return JavaInitClientUUID;
	} 
	
	
    public static void main( String[] args )
    {
    	new App().doDemo();
    }
	
       

    public void doDemo()
    {

    	    	int Programmauswahl = 0;
    			LED_Rot.set_Status(false);
    			LED_Rot.set_Topic("Test/objects/Aktor1");
    			
    			Taster_1.set_Topic("Test/objects/Taster1");
    			
    	    	// Creating Object of ObjectMapper define in Jakson Api 
    	    	ObjectMapper mapper = new ObjectMapper();
    	    	 
    	    	String topic        = "Test/objects";

    	    	int qos             = 0;
    	    	String broker 		= Bueroaccount.Adresse;
    	    	//Die Adresse für meinen MQTT Server will ich nicht online stellen, daher habe ich die User- und Serverdaten in eine separate
    	    	//Klasse geschoben, die nicht per Github synchronisiert wird. Man kann hier aber anstatt der Klassenvariable Bueroaccount.Adresse
    	    	//einfach eines Strin in folgender Form eingeben:
    	    	//String broker       = "tcp://meinMqttServer.de";
    	    	//String broker       = "tcp://192.168.0.2";
    	    	
    	    	String clientId     = CreateUID();
    	    	
    	    	MemoryPersistence persistence = new MemoryPersistence();
    	    	
    			try {
    				sampleClient = new MqttClient(broker, clientId, persistence);
    				
    				// Convert object to JSON string and save into a file directly
    	    	//Object to JSON in file
    	    	//mapper.writeValue(new File("c:\\file.json"), LED_Rot);
    	    	
    	    	//Object to JSON in String
    	    	String jsonInString = mapper.writeValueAsString(LED_Rot);
    	    	System.out.println(jsonInString);
    	    	String content      = jsonInString;

    	            
    	       
    	            MqttConnectOptions connOpts = new MqttConnectOptions();
    	            connOpts.setCleanSession(true);
        	    	//Die Adresse für meinen MQTT Server will ich nicht online stellen, daher habe ich die User- und Serverdaten in eine separate
        	    	//Klasse geschoben, die nicht per Github synchronisiert wird. Man kann hier aber anstatt der Klassenvariable Bueroaccount.Username
    	            //und Bueroaccount.Password einfach einen String in folgender Form eingeben:
    	            //connOpts.setUserName("BeispielNutzerName");
    	            //connOpts.setPassword("Beispielpasswort".toCharArray());
    	            connOpts.setUserName(Bueroaccount.Username);
    	            connOpts.setPassword(Bueroaccount.Password.toCharArray());
    	            connOpts.setAutomaticReconnect(true);
    	            System.out.println("Connecting to broker: "+broker);
    	            


    	            
    	            sampleClient.connect(connOpts);
    	            sampleClient.setCallback(this);
    	            System.out.println("Connected");
    	            //System.out.println("Publishing message: "+content);
        	    	jsonInString = mapper.writeValueAsString(LED_Rot);
        	    	content      = jsonInString;
        	    	MqttMessage message = new MqttMessage(content.getBytes());
        	    	message.setQos(qos);
    	            sampleClient.publish(LED_Rot.get_Topic(), message);
    	            
    	            // sampleClient.unsubscribe("Test/objects");
    	           // MqttMessage message = new MqttMessage(content.getBytes());
    	           // message.setQos(qos);
    	            //sampleClient.publish(topic, message);
    	            //System.out.println("Message published");
    	            sampleClient.subscribe(LED_Rot.get_Topic());
    	            //sampleClient.disconnect();
    	            //System.out.println("Disconnected");
    	            //System.exit(0);
    	            while(true)
    	            {
    	            	System.out.println("Welche MQTT Operation möchten Sie ausführen:");
    	            	System.out.println("1: Initialisiere alle Objekte lokal.");
    	            	System.out.println("2: Lade alle Objekte in die Datenbank hoch.");
    	            	System.out.println("3: Taster tasten und uploaden");
    	            	System.out.println("4: Ausgabe Status Taster.");
    	            	System.out.println("5: Ausgabe Status Aktor.");
    	            	System.out.println("0: Programmende");
    	            	Programmauswahl = Integer.parseInt(br.readLine());
    	            	switch(Programmauswahl)
    	            	{
    	            		case 1 : 
    	            				System.out.println("Initialisiere alle Objekte lokal.");
    	            				LED_Rot.set_Status(false);
    	            				Taster_1.reset_impuls();
    	            				Taster_1.set_Status(false);
    	            				break;
    	            		case 2 :
    	            				System.out.println("Lade alle Objekte in die Datenbank hoch.");
    	            				sampleClient.unsubscribe(LED_Rot.get_Topic());
    	                	    	jsonInString = mapper.writeValueAsString(LED_Rot);
    	                	    	content      = jsonInString;
    	                	    	message = new MqttMessage(content.getBytes());
    	                	    	message.setQos(qos);
    	                	    	
    	            	            sampleClient.publish(LED_Rot.get_Topic(), message);
    	            	            sampleClient.subscribe(LED_Rot.get_Topic());
    	                	    	jsonInString = mapper.writeValueAsString(Taster_1);
    	                	    	content      = jsonInString;
    	                	    	message = new MqttMessage(content.getBytes());
    	                	    	message.setQos(qos);
    	            	            sampleClient.publish(Taster_1.get_Topic(), message);   	            	            
    	            				break;
    	            		case 3: 
    	            				System.out.println("Taster tasten und uploaden");
    	            				Taster_1.impuls_on();
    	                	    	jsonInString = mapper.writeValueAsString(Taster_1);
    	                	    	content      = jsonInString;
    	                	    	message = new MqttMessage(content.getBytes());
    	                	    	message.setQos(qos);
    	            	            sampleClient.publish(Taster_1.get_Topic(), message);   
    	            	         /*   try
    	            	            {
    	            	                Thread.sleep(1000);
    	            	            }
    	            	            catch(InterruptedException ex)
    	            	            {
    	            	                Thread.currentThread().interrupt();
    	            	            }*/
    	            				Taster_1.reset_impuls();
    	                	    	jsonInString = mapper.writeValueAsString(Taster_1);
    	                	    	content      = jsonInString;
    	                	    	message = new MqttMessage(content.getBytes());
    	                	    	message.setQos(qos);
    	            	            sampleClient.publish(Taster_1.get_Topic(), message);      	            	            
    	            				break;
    	            		case 0:
    	        	            	sampleClient.disconnect();
    	        	            	System.out.println("Disconnected");
    	        	            	System.exit(0);
    	        	            	break;
    	        	        default:
    	        	        		System.out.println("Ungueltige Eingabe");
    	        	        		break;
    	            				
    	            			
    	            	}
    	            }

    	        } 
    			catch(MqttException me) 
    			{
    				System.out.println("reason "+me.getReasonCode());
    	            System.out.println("msg "+me.getMessage());
    	            System.out.println("loc "+me.getLocalizedMessage());
    	            System.out.println("cause "+me.getCause());
    	            System.out.println("excep "+me);
    	            me.printStackTrace();
    	        }
    			
    			catch (JsonGenerationException e) 
    			{
    				e.printStackTrace();
    			} 
    			
    			catch (JsonMappingException e) 
    			{
    				e.printStackTrace();
    			} 
    			
    			catch (IOException e) 
    			{
    			e.printStackTrace();
    			}
    	        
    	    }

	public void connectionLost(Throwable arg0)
	{
		// TODO Auto-generated method stub
		
	}

	public void deliveryComplete(IMqttDeliveryToken t)
	{
		// TODO Auto-generated method stub
		
	}

	public void messageArrived(String t, MqttMessage m) throws Exception
	{
		ObjectMapper mapper = new ObjectMapper();
		// TODO Auto-generated method stub
		System.out.println(new String(m.getPayload()));
		System.out.println("Nachricht wurde empfangen");
		System.out.println(m);
		LED_Rot = mapper.readValue(m.getPayload(), Aktor.class);
		//Irgendwo hier scheint es zu klemmen. Außerdem sollte jedesmal eine neue Client ID vergeben werden
		if(LED_Rot.get_Trigger())
		{
			LED_Rot.toggle_status();
		}
		LED_Rot.reset_Trigger();
		if(LED_Rot.get_status()) 
		{
			System.out.println("Led ist eingeschaltet");
		}
		else
		{
			System.out.println("Led ist ausgeschaltet");
		}
		
	}
    
    
    
    
    

	}
	
    
    
    


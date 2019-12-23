/*
selbst erstellte Library
zur Ansteuerung eines Pins an einem ATMEGA328
Version 0.1		04.11.2018		Erstellung der Klasse
Version 1.0		05.11.2018		Fertigstellung der rudimentären Funktionen der Klasse Pin


Notes:
Der Atmega 328 hat keinen Port A, an Port C fehlt Pin 7 bei der DIP (Arduino UNO) Version des ICs!!!
*/
#include "Pin_ATMEGA128.h"
#include <stdint-gcc.h>
#include <avr/io.h>

Pin::Pin()
{
	//Standardkonstruktor
}

Pin::Pin(char PublicPort, uint8_t Public_Nummer_Pin, bool Eingang)
{
	//ctor
	setze_Port(PublicPort);
	setze_PinNummer(Public_Nummer_Pin);
	setze_Richtung(Eingang);
	initialisierePin();  
	merke_status(false);
}

void Pin::merke_status(bool status)
{
	status_intern = status;
}

void Pin::toggle_Pin()
{
	if (lese_status())
	{
		setze_Status(false);
	} 
	else
	{
		setze_Status(true);
	}
}

bool Pin::lese_status()
{
	if(!private_Eingang) //Der Pin ist ein Ausgang, dementsprechend ist der Status derjenige, der als letztes definiert wurde
	{
		
	}
	else
	{
		if (private_Port == 'A')
		{
  			switch(private_Nummer_Pin)
  			{
    			case 0:	if (PINA & (1<<PINA0))
    			{merke_status(true);}
    			else
    			{merke_status(false);}
    			break;
    		
    			case 1:	if (PINA & (1<<PINA1))
    			{merke_status(true);}
    			else
    			{merke_status(false);}
    			break;
    		
    			case 2:	if (PINA & (1<<PINA2))
    			{merke_status(true);}
    			else
    			{merke_status(false);}
    			break;
    		
    			case 3:	if (PINA & (1<<PINA3))
    			{merke_status(true);}
    			else
    			{merke_status(false);}
    			break;
    		
    			case 4:	if (PINA & (1<<PINA4))
    			{merke_status(true);}
    			else
    			{merke_status(false);}
    			break;
    		
    			case 5:	if (PINA & (1<<PINA5))
    			{merke_status(true);}
    			else
    			{merke_status(false);}
    			break;
    		
    			case 6:	if (PINA & (1<<PINA6))
    			{merke_status(true);}
    			else
    			{merke_status(false);}
    			break;
    		
    			case 7:	if (PINA & (1<<PINA7))
    			{merke_status(true);}
    			else
    			{merke_status(false);}
    			break;
    		
    			default: //# warning "The choosen pin number is not valid. Only 0-7 are allowed on Port B"
    			break;
    		
  			}
		}


		if (private_Port == 'B')
		{
			switch(private_Nummer_Pin)
			{
				case 0:	if (PINB & (1<<PINB0))
					{merke_status(true);}
				else
					{merke_status(false);}
				break;
				
				case 1:	if (PINB & (1<<PINB1))
					{merke_status(true);}
				else
					{merke_status(false);}
				break;
				
				case 2:	if (PINB & (1<<PINB2))
					{merke_status(true);}
				else
					{merke_status(false);}
				break;
				
				case 3:	if (PINB & (1<<PINB3))
					{merke_status(true);}
				else
					{merke_status(false);}
				break;
					
				case 4:	if (PINB & (1<<PINB4))
					{merke_status(true);}
				else
					{merke_status(false);}
				break;
				
				case 5:	if (PINB & (1<<PINB5))
					{merke_status(true);}
				else
					{merke_status(false);}
				break;
				
				case 6:	if (PINB & (1<<PINB6))
					{merke_status(true);}
				else
					{merke_status(false);}
				break;
					
				case 7:	if (PINB & (1<<PINB7))
					{merke_status(true);}
				else
					{merke_status(false);}
				break;		
													
				default: //# warning "The choosen pin number is not valid. Only 0-7 are allowed on Port B"
				break;
				
			}
		}

		if (private_Port == 'C')
		{
			switch(private_Nummer_Pin)
			{
				case 0:	if (PINC & (1<<PINC0))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;
				
				case 1:	if (PINC & (1<<PINC1))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;
				
				case 2:	if (PINC & (1<<PINC2))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;
				
				case 3:	if (PINC & (1<<PINC3))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;
				
				case 4:	if (PINC & (1<<PINC4))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;
				
				case 5:	if (PINC & (1<<PINC5))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;
				
				case 6:	if (PINC & (1<<PINC6))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;
				
			}
		}
		
		if (private_Port == 'D')
		{
			switch(private_Nummer_Pin)
			{
				case 0:	if (PIND & (1<<PIND0))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;
				
				case 1:	if (PIND & (1<<PIND1))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;
				
				case 2:	if (PIND & (1<<PIND2))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;
				
				case 3:	if (PIND & (1<<PIND3))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;
				
				case 4:	if (PIND & (1<<PIND4))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;
				
				case 5:	if (PIND & (1<<PIND5))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;
				
				case 6:	if (PIND & (1<<PIND6))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;
				
				case 7:	if (PIND & (1<<PIND7))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;			}
		}
	}
  
  		if (private_Port == 'E')
  		{
    		switch(private_Nummer_Pin)
    		{
      		case 0:	if (PINE & (1<<PINE0))
      		{merke_status(true);}
      		else
      		{merke_status(false);}
      		break;
      		
      		case 1:	if (PINE & (1<<PINE1))
      		{merke_status(true);}
      		else
      		{merke_status(false);}
      		break;
      		
      		case 2:	if (PINE & (1<<PINE2))
      		{merke_status(true);}
      		else
      		{merke_status(false);}
      		break;
      		
      		case 3:	if (PINE & (1<<PINE3))
      		{merke_status(true);}
      		else
      		{merke_status(false);}
      		break;
      		
      		case 4:	if (PINE & (1<<PINE4))
      		{merke_status(true);}
      		else
      		{merke_status(false);}
      		break;
      		
      		case 5:	if (PINE & (1<<PINE5))
      		{merke_status(true);}
      		else
      		{merke_status(false);}
      		break;
      		
      		case 6:	if (PINE & (1<<PINE6))
      		{merke_status(true);}
      		else
      		{merke_status(false);}
      		break;
      		
      		case 7:	if (PINE & (1<<PINE7))
      		{merke_status(true);}
      		else
      		{merke_status(false);}
      		break;
      		
      		default: //# warning "The choosen pin number is not valid. Only 0-7 are allowed on Port E"
      		break;
      		
    		}
  		}
      
		if (private_Port == 'F')
		{
  		switch(private_Nummer_Pin)
  		{
    		case 0:	if (PINF & (1<<PINF0))
    		{merke_status(true);}
    		else
    		{merke_status(false);}
    		break;
    		
    		case 1:	if (PINF & (1<<PINF1))
    		{merke_status(true);}
    		else
    		{merke_status(false);}
    		break;
    		
    		case 2:	if (PINF & (1<<PINF2))
    		{merke_status(true);}
    		else
    		{merke_status(false);}
    		break;
    		
    		case 3:	if (PINF & (1<<PINF3))
    		{merke_status(true);}
    		else
    		{merke_status(false);}
    		break;
    		
    		case 4:	if (PINF & (1<<PINF4))
    		{merke_status(true);}
    		else
    		{merke_status(false);}
    		break;
    		
    		case 5:	if (PINF & (1<<PINF5))
    		{merke_status(true);}
    		else
    		{merke_status(false);}
    		break;
    		
    		case 6:	if (PINF & (1<<PINF6))
    		{merke_status(true);}
    		else
    		{merke_status(false);}
    		break;
    		
    		case 7:	if (PINF & (1<<PINF7))
    		{merke_status(true);}
    		else
    		{merke_status(false);}
    		break;
    		
    		default: //# warning "The choosen pin number is not valid. Only 0-7 are allowed on Port F"
    		break;
  		}
		}
		if (private_Port == 'G')
		{
  		switch(private_Nummer_Pin)
  		{
    		case 0:	if (PING & (1<<PING0))
    		{merke_status(true);}
    		else
    		{merke_status(false);}
    		break;
    		
    		case 1:	if (PING & (1<<PING1))
    		{merke_status(true);}
    		else
    		{merke_status(false);}
    		break;
    		
    		case 2:	if (PING & (1<<PING2))
    		{merke_status(true);}
    		else
    		{merke_status(false);}
    		break;
    		
    		case 3:	if (PING & (1<<PING3))
    		{merke_status(true);}
    		else
    		{merke_status(false);}
    		break;
    		
    		case 4:	if (PING & (1<<PING4))
    		{merke_status(true);}
    		else
    		{merke_status(false);}
    		break;
    		
    		
    		default: //# warning "The choosen pin number is not valid. Only 0-4 are allowed on Port G"
    		break;
    		
  		}
		}



	return status_intern;
}	
	


char Pin::lese_Port()
{
	return private_Port;
}

uint8_t Pin::lese_PinNummer()
{
	return private_Nummer_Pin;
}

void Pin::setze_Port(char PortBuchstabe)
{
	private_Port = PortBuchstabe;
}

void Pin::setze_PinNummer(uint8_t Pin_Nummer)
{
	private_Nummer_Pin = Pin_Nummer;
}

void Pin::setze_Richtung(bool is_Eingang)
{
	private_Eingang = is_Eingang;
}

void Pin::initialisierePin()
{
	if (private_Port == 'A')
	{
		switch(private_Nummer_Pin)
		{
  		case 0:	if (private_Eingang == true)
  		{DDRA &= ~(1 << DDA0);}
  		else
  		{DDRA |= (1 << DDA0);}
  		break;
  		
  		case 1:	if (private_Eingang == true)
  		{DDRA &= ~(1 << DDA1);}
  		else
  		{DDRA |= (1 << DDA1);}
  		break;
  		
  		case 2:	if (private_Eingang == true)
  		{DDRA &= ~(1 << DDA2);}
  		else
  		{DDRA |= (1 << DDA2);}
  		break;
  		
  		case 3:	if (private_Eingang == true)
  		{DDRA &= ~(1 << DDA3);}
  		else
  		{DDRA |= (1 << DDA3);}
  		break;
  		
  		case 4:	if (private_Eingang == true)
  		{DDRA &= ~(1 << DDA4);}
  		else
  		{DDRA |= (1 << DDA4);}
  		break;
  		
  		case 5:	if (private_Eingang == true)
  		{DDRA &= ~(1 << DDA5);}
  		else
  		{DDRA |= (1 << DDA5);}
  		break;
  		
  		case 6:	if (private_Eingang == true)
  		{DDRA &= ~(1 << DDA6);}
  		else
  		{DDRA |= (1 << DDA6);}
  		break;
  		
  		case 7:	if (private_Eingang == true)
  		{DDRA &= ~(1 << DDA7);}
  		else
  		{DDRA |= (1 << DDA7);}
  		break;
  		
  		default: //# warning "The choosen pin number is not valid. Only 0-7 are allowed on Port A"
  		break;
  		
		}
	}

	if (private_Port == 'B')
	{
		switch(private_Nummer_Pin)
		{
			case 0:	if (private_Eingang == true)
			{DDRB &= ~(1 << DDB0);}
			else
			{DDRB |= (1 << DDB0);}
			break;
			
			case 1:	if (private_Eingang == true)
			{DDRB &= ~(1 << DDB1);}
			else
			{DDRB |= (1 << DDB1);}
			break;
			
			case 2:	if (private_Eingang == true)
			{DDRB &= ~(1 << DDB2);}
			else
			{DDRB |= (1 << DDB2);}
			break;
			
			case 3:	if (private_Eingang == true)
			{DDRB &= ~(1 << DDB3);}
			else
			{DDRB |= (1 << DDB3);}
			break;
			
			case 4:	if (private_Eingang == true)
			{DDRB &= ~(1 << DDB4);}
			else
			{DDRB |= (1 << DDB4);}
			break;
			
			case 5:	if (private_Eingang == true)
			{DDRB &= ~(1 << DDB5);}
			else
			{DDRB |= (1 << DDB5);}
			break;
			
			case 6:	if (private_Eingang == true)
			{DDRB &= ~(1 << DDB6);}
			else
			{DDRB |= (1 << DDB6);}
			break;
			
			case 7:	if (private_Eingang == true)
			{DDRB &= ~(1 << DDB7);}
			else
			{DDRB |= (1 << DDB7);}
			break;
			
			default: //# warning "The choosen pin number is not valid. Only 0-7 are allowed on Port B"
			break;
			
		}
	}

	if (private_Port == 'C')
	{
		switch(private_Nummer_Pin)
		{
			case 0:	if (private_Eingang == true)
			{DDRC &= ~(1 << DDC0);}
			else
			{DDRC |= (1 << DDC0);}
			break;
			
			case 1:	if (private_Eingang == true)
			{DDRC &= ~(1 << DDC1);}
			else
			{DDRC |= (1 << DDC1);}
			break;
			
			case 2:	if (private_Eingang == true)
			{DDRC &= ~(1 << DDC2);}
			else
			{DDRC |= (1 << DDC2);}
			break;
			
			case 3:	if (private_Eingang == true)
			{DDRC &= ~(1 << DDC3);}
			else
			{DDRC |= (1 << DDC3);}
			break;
			
			case 4:	if (private_Eingang == true)
			{DDRC &= ~(1 << DDC4);}
			else
			{DDRC |= (1 << DDC4);}
			break;
			
			case 5:	if (private_Eingang == true)
			{DDRC &= ~(1 << DDC5);}
			else
			{DDRC |= (1 << DDC5);}
			break;
			
			case 6:	if (private_Eingang == true)
			{DDRC &= ~(1 << DDC6);}
			else
			{DDRC |= (1 << DDC6);}
			break;
			
			default: //# warning "The choosen pin number is not valid. Only 0-6 are allowed on Port C"
			break;
			
		}
	}
	
	if (private_Port == 'D')
	{
		switch(private_Nummer_Pin)
		{
			case 0:	if (private_Eingang == true)
			{DDRD &= ~(1 << DDD0);}
			else
			{DDRD |= (1 << DDD0);}
			break;
			
			case 1:	if (private_Eingang == true)
			{DDRD &= ~(1 << DDD1);}
			else
			{DDRD |= (1 << DDD1);}
			break;
			
			case 2:	if (private_Eingang == true)
			{DDRD &= ~(1 << DDD2);}
			else
			{DDRD |= (1 << DDD2);}
			break;
			
			case 3:	if (private_Eingang == true)
			{DDRD &= ~(1 << DDD3);}
			else
			{DDRD |= (1 << DDD3);}
			break;
			
			case 4:	if (private_Eingang == true)
			{DDRD &= ~(1 << DDD4);}
			else
			{DDRD |= (1 << DDD4);}
			break;
			
			case 5:	if (private_Eingang == true)
			{DDRD &= ~(1 << DDD5);}
			else
			{DDRD |= (1 << DDD5);}
			break;
			
			case 6:	if (private_Eingang == true)
			{DDRD &= ~(1 << DDD6);}
			else
			{DDRD |= (1 << DDD6);}
			break;
			
			case 7:	if (private_Eingang == true)
			{DDRD &= ~(1 << DDD7);}
			else
			{DDRD |= (1 << DDD7);}
			break;
			
			default: //# warning "The choosen pin number is not valid. Only 0-7 are allowed on Port D"
			break;						
		}
	}
	
	if (private_Port == 'E')
	{
  		switch(private_Nummer_Pin)
  		{
    		case 0:	if (private_Eingang == true)
    		{DDRE &= ~(1 << DDE0);}
    		else
    		{DDRE |= (1 << DDE0);}
    		break;
    	
    		case 1:	if (private_Eingang == true)
    		{DDRE &= ~(1 << DDE1);}
    		else
    		{DDRE |= (1 << DDE1);}
    		break;
    	
    		case 2:	if (private_Eingang == true)
    		{DDRE &= ~(1 << DDE2);}
    		else
    		{DDRE |= (1 << DDE2);}
    		break;
    	
    		case 3:	if (private_Eingang == true)
    		{DDRE &= ~(1 << DDE3);}
    		else
    		{DDRE |= (1 << DDE3);}
    		break;
    	
    		case 4:	if (private_Eingang == true)
    		{DDRE &= ~(1 << DDE4);}
    		else
    		{DDRE |= (1 << DDE4);}
    		break;
    	
    		case 5:	if (private_Eingang == true)
    		{DDRE &= ~(1 << DDE5);}
    		else
    		{DDRE |= (1 << DDE5);}
    		break;
    	
    		case 6:	if (private_Eingang == true)
    		{DDRE &= ~(1 << DDE6);}
    		else
    		{DDRE |= (1 << DDE6);}
    		break;
    	
    		case 7:	if (private_Eingang == true)
    		{DDRE &= ~(1 << DDE7);}
    		else
    		{DDRE |= (1 << DDE7);}
    		break;
    	
    		default: //# warning "The choosen pin number is not valid. Only 0-7 are allowed on Port E"
    		break;
  		}
	}

	if (private_Port == 'F')
	{
  		switch(private_Nummer_Pin)
  		{
    		case 0:	if (private_Eingang == true)
    		{DDRF &= ~(1 << DDF0);}
    		else
    		{DDRF |= (1 << DDF0);}
    		break;
    	
    		case 1:	if (private_Eingang == true)
    		{DDRF &= ~(1 << DDF1);}
    		else
    		{DDRF |= (1 << DDF1);}
    		break;
    	
    		case 2:	if (private_Eingang == true)
    		{DDRF &= ~(1 << DDF2);}
    		else
    		{DDRF |= (1 << DDF2);}
    		break;
    	
    		case 3:	if (private_Eingang == true)
    		{DDRF &= ~(1 << DDF3);}
    		else
    		{DDRF |= (1 << DDF3);}
    		break;
    	
    		case 4:	if (private_Eingang == true)
    		{DDRF &= ~(1 << DDF4);}
    		else
    		{DDRF |= (1 << DDF4);}
    		break;
    	
    		case 5:	if (private_Eingang == true)
    		{DDRF &= ~(1 << DDF5);}
    		else
    		{DDRF |= (1 << DDF5);}
    		break;
    	
    		case 6:	if (private_Eingang == true)
    		{DDRF &= ~(1 << DDF6);}
    		else
    		{DDRF |= (1 << DDF6);}
    		break;
    	
    		case 7:	if (private_Eingang == true)
    		{DDRF &= ~(1 << DDF7);}
    		else
    		{DDRF |= (1 << DDF7);}
    		break;
    	
    		default: //# warning "The choosen pin number is not valid. Only 0-7 are allowed on Port F"
    		break;
  		}
	}
	if (private_Port == 'G')
	{
  		switch(private_Nummer_Pin)
  		{
    		case 0:	if (private_Eingang == true)
    		{DDRG &= ~(1 << DDG0);}
    		else
    		{DDRG |= (1 << DDG0);}
    		break;
    	
    		case 1:	if (private_Eingang == true)
    		{DDRG &= ~(1 << DDG1);}
    		else
    		{DDRG |= (1 << DDG1);}
    		break;
    	
    		case 2:	if (private_Eingang == true)
    		{DDRG &= ~(1 << DDG2);}
    		else
    		{DDRG |= (1 << DDG2);}
    		break;
    	
    		case 3:	if (private_Eingang == true)
    		{DDRG &= ~(1 << DDG3);}
    		else
    		{DDRG |= (1 << DDG3);}
    		break;
    	
    		case 4:	if (private_Eingang == true)
    		{DDRG &= ~(1 << DDG4);}
    		else
    		{DDRG |= (1 << DDG4);}
    		break;
    	
    		default: //# warning "The choosen pin number is not valid. Only 0-4 are allowed on Port G"
    		break;
  		}
	}



}

void Pin::setze_Status(bool Status)
{

		if (private_Port == 'B')
		{
			switch(private_Nummer_Pin)
			{
				case 0:	if (Status == true)
				{ PORTB |= (1<< PINB0);
					merke_status(true);}
				else
				{PORTB &= ~(1<<PINB0);
					merke_status(false);}
				break;
				
				case 1:	if (Status == true)
				{ PORTB |= (1<< PINB1);
					merke_status(true);}
				else
				{PORTB &= ~(1<<PINB1);
					merke_status(false);}
				break;
				
				case 2:	if (Status == true)
				{ PORTB |= (1<< PINB2);
					merke_status(true);}
				else
				{PORTB &= ~(1<<PINB2);
					merke_status(false);}
				break;
				
				case 3:	if (Status == true)
				{ PORTB |= (1<< PINB3);
					merke_status(true);}
				else
				{PORTB &= ~(1<<PINB3);
					merke_status(false);}
				break;
				
				case 4:	if (Status == true)
				{ PORTB |= (1<< PINB4);
					merke_status(true);}
				else
				{PORTB &= ~(1<<PINB4);
					merke_status(false);}
				break;
				
				case 5:	if (Status == true)
				{ PORTB |= (1<< PINB5);
					merke_status(true);}
				else
				{PORTB &= ~(1<<PINB5);
					merke_status(false);}
				break;
				
				case 6:	if (Status == true)
				{ PORTB |= (1<< PINB6);
					merke_status(true);}
				else
				{PORTB &= ~(1<<PINB6);
					merke_status(false);}
				break;
				
				case 7:	if (Status == true)
				{ PORTB |= (1<< PINB7);
					merke_status(true);}
				else
				{PORTB &= ~(1<<PINB7);
					merke_status(false);}
				break;
				
				default: //# warning "The choosen pin number is not valid. Only 0-7 are allowed on Port B"
				break;
				
			}
		}

		if (private_Port == 'C')
		{
			switch(private_Nummer_Pin)
			{
				case 0:	if (Status == true)
				{ PORTC |= (1<< PINC0);
					merke_status(true);}
				else
				{PORTC &= ~(1<<PINC0);
					merke_status(false);}
				break;
				
				case 1:	if (Status == true)
				{ PORTC |= (1<< PINC1);
					merke_status(true);}
				else
				{PORTC &= ~(1<<PINC1);
					merke_status(false);}
				break;
				
				case 2:	if (Status == true)
				{ PORTC |= (1<< PINC2);
					merke_status(true);}
				else
				{PORTC &= ~(1<<PINC2);
					merke_status(false);}
				break;
				
				case 3:	if (Status == true)
				{ PORTC |= (1<< PINC3);
					merke_status(true);}
				else
				{PORTC &= ~(1<<PINC3);
					merke_status(false);}
				break;
				
				case 4:	if (Status == true)
				{ PORTC |= (1<< PINC4);
					merke_status(true);}
				else
				{PORTC &= ~(1<<PINC4);
					merke_status(false);}
				break;
				
				case 5:	if (Status == true)
				{ PORTC |= (1<< PINC5);
					merke_status(true);}
				else
				{PORTC &= ~(1<<PINC5);
					merke_status(false);}
				break;
				
				case 6:	if (Status == true)
				{ PORTC |= (1<< PINC6);
					merke_status(true);}
				else
				{PORTC &= ~(1<<PINC6);
					merke_status(false);}
				break;
				
				default: //# warning "The choosen pin number is not valid. Only 0-6 are allowed on Port C"
				break;
							}
		}
		
		if (private_Port == 'D')
		{
			switch(private_Nummer_Pin)
			{
				case 0:	if (Status == true)
				{ PORTD |= (1<< PIND0);
					merke_status(true);}
				else
				{PORTD &= ~(1<<PIND0);
					merke_status(false);}
				break;
				
				case 1:	if (Status == true)
				{ PORTD |= (1<< PIND1);
					merke_status(true);}
				else
				{PORTD &= ~(1<<PIND1);
					merke_status(false);}
				break;
				
				case 2:	if (Status == true)
				{ PORTD |= (1<< PIND2);
					merke_status(true);}
				else
				{PORTD &= ~(1<<PIND2);
					merke_status(false);}
				break;
				
				case 3:	if (Status == true)
				{ PORTD |= (1<< PIND3);
					merke_status(true);}
				else
				{PORTD &= ~(1<<PIND3);
					merke_status(false);}
				break;
				
				case 4:	if (Status == true)
				{ PORTD |= (1<< PIND4);
					merke_status(true);}
				else
				{PORTD &= ~(1<<PIND4);
					merke_status(false);}
				break;
				
				case 5:	if (Status == true)
				{ PORTD |= (1<< PIND5);
					merke_status(true);}
				else
				{PORTD &= ~(1<<PIND5);
					merke_status(false);}
				break;
				
				case 6:	if (Status == true)
				{ PORTD |= (1<< PIND6);
					merke_status(true);}
				else
				{PORTD &= ~(1<<PIND6);
					merke_status(false);}
				break;
				
				case 7:	if (Status == true)
				{ PORTD |= (1<< PIND7);
					merke_status(true);}
				else
				{PORTD &= ~(1<<PIND7);
					merke_status(false);}
				break;
				
				default: //# warning "The choosen pin number is not valid. Only 0-7 are allowed on Port D"
				break;
			}
		}

}

void Pin::PullUpSchalten(bool anschalten)
{
	setze_Status(anschalten); // Der PullUp Widerstand am µC aktiviert, wenn er als Eingang definiert ist, und dann so auf 1 geschaltet wird, als wäre er ein Ausgang.
}

/*
Pin::~Pin()
{
	//dtor
}
*/
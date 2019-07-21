/* 
* String_Operationen.cpp
*
* Created: 21.07.2019 15:35:12
* Author: Bastian
*/


#include "String_Operationen.h"

// default constructor
String_Operationen::String_Operationen()
{
} //String_Operationen

	int[] String_Operationen::search_for_next_two_quotation_marks(int start_position, char[] String2searchFor)
	{
		int[] quotation_mark_position = { 0 , 0};
		int j=0;
		for(int i=start_position; String2searchFor[i]!='\0'; i++)
		{
			if (j<2)
			{
				if(String2searchFor[i]=='"') //wenn Anf�hrungszeichen erkannt wurden
				{
					quotation_mark_position[j] = i;
					j++;
				}
				
			}
		}
		return quotation_mark_position;
	}
	
	char[] String_Operationen::String_between_quotation_marks(char[] String_with_2quot_marks)
	{
		char[] Param = new char[30];
		int[] quot_marks_pos = search_for_next_two_quotation_marks(0, String_with_2quot_marks);
		for(int i=0; i<(quot_marks_pos[1]-quot_marks_pos[0]-1); i++)
		{
			Param[i] = String_with_2quot_marks[i+quot_marks_pos[0]+1];
			Param[i+1] = '\0';
		}

		return Param;
	}
	
	static int[] String_Operationen::Positionen_von_Elementen_in_String(char[] InputString, char Character_to_search_for)
	{
		int[] Positionen = {999, 999, 999, 999, 999, 999, 999, 999, 999, 999};
		int i=0;
		int j=0;
		while(InputString[i]!='\0')
		{
			if(InputString[i] == Character_to_search_for)
			{
				Positionen[j] = i;
				j++;
			}
			i++;
		}
		
		return Positionen;
	}
	
	//gibt die L�nge eines Strings zur�ck
	int String_Operationen::lenght(char[] InputString)
	{
		int i=0;
		while(InputString[i]!='\0')
		{
			i++;
		}
		return i;
	}
	
	char[] String_Operationen::String_to_Char_Array(String eingabestring)
	{
		char[] AusgabeArray = new char[40];
		AusgabeArray= eingabestring.toCharArray();	
		return AusgabeArray;
	}
	
	int String_Operationen::char_array_to_int(char[] InputString)
	{
		int zahl = 0;
		boolean negativ = false;
		int laufindex = 0;
		int Potenz = 0;
		if(InputString[0] == '-')
		{
			negativ = true;
			laufindex++;
		}
		for(; InputString[laufindex] != '\0'; laufindex++)
		{
			zahl = zahl*10;
		
			Potenz++;
			switch(InputString[laufindex])
			{
			case '0':
				zahl = zahl;
				break;
			case '1':
				zahl = zahl+1;
				break;
			case '2':
				zahl = zahl+2;
				break;
			case '3':
				zahl = zahl+3;
				break;
			case '4':
				zahl = zahl+4;
				break;
			case '5':
				zahl = zahl+5;
				break;
			case '6':
				zahl = zahl+6;
				break;
			case '7':
				zahl = zahl+7;
				break;
			case '8':
				zahl = zahl+8;
				break;
			case '9':
				zahl = zahl+9;
				break;
			default:
				//Fehlerfall sollte irgendwie noch abgehandelt werden
				break;
			}
			if(negativ)
			{
				zahl = zahl *(-1);
			}
			
		}
		
		return zahl;
	}
	
	//Hoffentlich eine Java Spezifische Methode um zwei Char Arrays gleichen Inhalts, aber unterschiedlicher L�nge zu vergleichen
	//Gibt true zur�ck, wenn zwei Char Arrays die gleichen "druckbaren" Zeichen enthalten, aber sich in der L�nge der angeh�ngten freien Stellen unterscheiden
	boolean String_Operationen::Compare_Char_Arrays(char[] String_1, char[] String_2)
	{
		boolean ist_gleich = true;
		for(int i=0; ((ist_gleich && (int)String_1[i]>32) && ((int)String_2[i]>32) && ((int)String_1[i]<127) && ((int)String_2[i]<127)); i++) //Damit liegen die beiden aktuell gepr�ften Zeichen im Bereich der normalen Buchstaben und Zeichen
		{
			if(String_1[i] == String_2[i])
			{
				ist_gleich = true;
			}
			else
			{
				ist_gleich = false;
			}
		}
		
		
		return ist_gleich;
	}



// default destructor
String_Operationen::~String_Operationen()
{
} //~String_Operationen

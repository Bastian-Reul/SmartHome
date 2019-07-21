/* 
* Aktor.cpp
*
* Created: 30.04.2019 12:26:22
* Author: Basti
*/


#include "Aktor.h"
#include "String_Operationen.h"

// default constructor
Aktor::Aktor()
{
} //Aktor



int Aktor::JSON_2_Aktor(char JSON_Input[])
{
		/*Im ersten Teil wird der JSON String an dem Kommata aufgeteilt, so dass die Parameter getrennt voneinander, jedoch mit ihren
		Bezeichner in einem String stehen:
		"_Topic":"Test/objects/Aktor1","_status":true,"_schaltvorgaenge":2,"Adresse":739,"_toggle_trigger":true
		wird zu:
		char Liste[5][40]
		[0]['"','_','T','o','p','i','c','"',':','"','T','e','s','t','/','o','b','j','e','c','t','s','/','A','k','t','o','r','1','"','\0']
		[1]['"','_','s','t','a','t','u','s','"',':','t','r','u','e','\0']
		[2]....
		[3]....
		[4]....
		*/
		int result = 0;

		char Liste[5][40];
		char typ[40];
		char wert[40];
		int Listenplatz = 0;
		
		//Erkennen wieviele Kommata im Text überhaupt sind
		int positionen[] = String_Operationen::Positionen_von_Elementen_in_String(JSON_Input, ',');
		int anzahl_Positionen = 0;
		for(int i=0; i<10; i++)
		{
			if(positionen[i]!=999)
			{
				anzahl_Positionen++;
			}
		}
		

		int j=0; //j bestimmt an welcher Position wir im Ausgangsstring sind
		int h=0; //h bestimmt an welcher Position Position wir in der aktuellen Zeile der Liste sind Liste[0-4][h]
		int laenge_JSON_String = String_Operationen::lenght(JSON_Input);
		for(int i=0; i<=anzahl_Positionen; i++) //i bestimmt in welcher Zeile von Liste[i][0-39] wir sind
		{
			for(h=0; (j<positionen[i])&&(j<laenge_JSON_String); h++)
			{
				Liste[i][h] = JSON_Input[j];
				Liste[i][h+1] = '\0';
				j++;
			}
			j++;
		}
		//Ende erster Teil 
		
		//Anfang zweiter Teil
		/*Im zweiten Teil wird die char Liste[5][40] Zeile für Zeile durchgearbeitet
		 * Um Speicherplatz zu sparen, wird jedoch eine Zeile ausgelesen, am Doppelpunkt in zwei Char Arrays (char Zeile[2][40])
		 * gespeichert, beschnitten (Anführungszeichen heraus, etc) und dann in den entsprechenden Aktor Parameter abgespeichert
		 * Danach wird genauso mit der nächsten Zeile aus char Liste[5][40] verfahren. Dafür kann dann wieder das gleiche char Zeile[2][40]
		 * benutzt werden um Speicherplatz zu sparen
		 * 		char Liste[5][40]
				[0]['"','_','T','o','p','i','c','"',':','"','T','e','s','t','/','o','b','j','e','c','t','s','/','A','k','t','o','r','1','"','\0']
				[1]['"','_','s','t','a','t','u','s','"',':','t','r','u','e','\0']
				 wird zu:
				char Zeile[2][40]
				[0]['_','T','o','p','i','c','\0']
				[1]['T','e','s','t','/','o','b','j','e','c','t','s','/','A','k','t','o','r','1','\0']
				
				und wird dann abgespeichert
				Topic = Zeile[1];
		 */
		
		char[][] Zeile = new char[2][40];
		
		//Topic speichern
		//Herausfinden wo der Doppelpunkt in der Zeile ist:
		positionen = String_Operationen::Positionen_von_Elementen_in_String(Liste[0], ':');
		j=0; //Zaehlervariable im Ausgangsstring, die bestimmt welcher Buchstabe grade eingelesen wird
		h=0; //Bestimmt in welcher Zeile wir von "Zeile" sind (0 oder 1) Zeile[h][0-39]
		int i=0;
		for(j=0; j<positionen[0];) // Der Teil vor dem : wird abgegrast
		{
			if((Liste[Listenplatz][j] != '_') && (Liste[Listenplatz][j] != ':') && (Liste[Listenplatz][j] !=  '"') && (Liste[Listenplatz][j] !=  '\0'))
			{
				Zeile[0][i] = Liste[Listenplatz][j];
				Zeile[0][i+1] = '\0';
				i++;
			}
			j++;
		}
		i=0;
		for(; j<String_Operationen.lenght(Liste[Listenplatz]);) // Der Teil nach dem : wird abgegrast
		{
			if((Liste[Listenplatz][j] != '_') && (Liste[Listenplatz][j] != ':') && (Liste[Listenplatz][j] !=  '"') && (Liste[Listenplatz][j] !=  '\0'))
			{
				Zeile[1][i] = Liste[Listenplatz][j];
				Zeile[1][i+1] = '\0';
				i++;
			}
			j++;
		}
		
		//Java Spezifisch (hoffentlich)
		
		
		
		if(String_Operationen::Compare_Char_Arrays(Zeile[0], ("Topic")))
		{
			Aktor._Topic = Zeile[1];
		}
		else
		{
			result++; //Wenn der Rückgabewert != 0 ist, ist ein Fehler bei der Konvertierung aufgetreten
		}
		
		//status speichern
		Listenplatz++;
		//Herausfinden wo der Doppelpunkt in der Zeile ist:
		positionen = String_Operationen::Positionen_von_Elementen_in_String(Liste[Listenplatz], ':');
		j=0; //Zaehlervariable im Ausgangsstring, die bestimmt welcher Buchstabe grade eingelesen wird
		h=0; //Bestimmt in welcher Zeile wir von "Zeile" sind (0 oder 1) Zeile[h][0-39]
		i=0;
		for(j=0; j<positionen[0];) // Der Teil vor dem : wird abgegrast
		{
			if((Liste[Listenplatz][j] != '_') && (Liste[Listenplatz][j] != ':') && (Liste[Listenplatz][j] !=  '"') && (Liste[Listenplatz][j] !=  '\0'))
			{
				Zeile[0][i] = Liste[Listenplatz][j];
				Zeile[0][i+1] = '\0';
				i++;
			}
			j++;
		}
		i=0;
		for(; j<String_Operationen::lenght(Liste[Listenplatz]);) // Der Teil nach dem : wird abgegrast
		{
			if((Liste[Listenplatz][j] != '_') && (Liste[Listenplatz][j] != ':') && (Liste[Listenplatz][j] !=  '"') && (Liste[Listenplatz][j] !=  '\0'))
			{
				Zeile[1][i] = Liste[Listenplatz][j];
				Zeile[1][i+1] = '\0';
				i++;
			}
			j++;
		}
		

		if(String_Operationen::Compare_Char_Arrays(Zeile[0], ("status")))   //Es muss die String Methode toCharArray() benutzt werden, da ich in Java kein Char Array einfach so Hardgecodet schreiben kann
		{
			if(String_Operationen::Compare_Char_Arrays(Zeile[1], ("true")))
			{
				Aktor._status = true;
			}
			else
			{
				if(String_Operationen::Compare_Char_Arrays(Zeile[1], ("false")))
				{
					Aktor._status = false;
				}
				else
				{
					result++;
				}
			}
		}		
		else
		{
			result++; //Wenn der Rückgabewert != 0 ist, ist ein Fehler bei der Konvertierung aufgetreten
		}
		
		//schaltvorgänge speichern
		Listenplatz++;
		//Herausfinden wo der Doppelpunkt in der Zeile ist:
		positionen = String_Operationen::Positionen_von_Elementen_in_String(Liste[Listenplatz], ':');
		j=0; //Zaehlervariable im Ausgangsstring, die bestimmt welcher Buchstabe grade eingelesen wird
		h=0; //Bestimmt in welcher Zeile wir von "Zeile" sind (0 oder 1) Zeile[h][0-39]
		i=0;
		for(j=0; j<positionen[0];) // Der Teil vor dem : wird abgegrast
		{
			if((Liste[Listenplatz][j] != '_') && (Liste[Listenplatz][j] != ':') && (Liste[Listenplatz][j] !=  '"') && (Liste[Listenplatz][j] !=  '\0'))
			{
				Zeile[0][i] = Liste[Listenplatz][j];
				Zeile[0][i+1] = '\0';
				i++;
			}
			j++;
		}
		i=0;
		for(; j<String_Operationen::lenght(Liste[Listenplatz]);) // Der Teil nach dem : wird abgegrast
		{
			if((Liste[Listenplatz][j] != '_') && (Liste[Listenplatz][j] != ':') && (Liste[Listenplatz][j] !=  '"') && (Liste[Listenplatz][j] !=  '\0'))
			{
				Zeile[1][i] = Liste[Listenplatz][j];
				Zeile[1][i+1] = '\0';
				i++;
			}
			j++;
		}
		

		if(String_Operationen::Compare_Char_Arrays(Zeile[0], ("schaltvorgaenge")))   //Es muss die String Methode toCharArray() benutzt werden, da ich in Java kein Char Array einfach so Hardgecodet schreiben kann
		{
			Aktor._schaltvorgaenge = String_Operationen::char_array_to_int(Zeile[1]);
		}		
		else
		{
			result++; //Wenn der Rückgabewert != 0 ist, ist ein Fehler bei der Konvertierung aufgetreten
		}
		
		//Adresse speichern
		Listenplatz++;
		//Herausfinden wo der Doppelpunkt in der Zeile ist:
		positionen = String_Operationen::Positionen_von_Elementen_in_String(Liste[Listenplatz], ':');
		j=0; //Zaehlervariable im Ausgangsstring, die bestimmt welcher Buchstabe grade eingelesen wird
		h=0; //Bestimmt in welcher Zeile wir von "Zeile" sind (0 oder 1) Zeile[h][0-39]
		i=0;
		for(j=0; j<positionen[0];) // Der Teil vor dem : wird abgegrast
		{
			if((Liste[Listenplatz][j] != '_') && (Liste[Listenplatz][j] != ':') && (Liste[Listenplatz][j] !=  '"') && (Liste[Listenplatz][j] !=  '\0'))
			{
				Zeile[0][i] = Liste[Listenplatz][j];
				Zeile[0][i+1] = '\0';
				i++;
			}
			j++;
		}
		i=0;
		for(; j<String_Operationen::lenght(Liste[Listenplatz]);) // Der Teil nach dem : wird abgegrast
		{
			if((Liste[Listenplatz][j] != '_') && (Liste[Listenplatz][j] != ':') && (Liste[Listenplatz][j] !=  '"') && (Liste[Listenplatz][j] !=  '\0'))
			{
				Zeile[1][i] = Liste[Listenplatz][j];
				Zeile[1][i+1] = '\0';
				i++;
			}
			j++;
		}
		

		if(String_Operationen::Compare_Char_Arrays(Zeile[0], ("Adresse")))   //Es muss die String Methode toCharArray() benutzt werden, da ich in Java kein Char Array einfach so Hardgecodet schreiben kann
		{
			Aktor.Adresse = String_Operationen::char_array_to_int(Zeile[1]);
		}		
		else
		{
			result++; //Wenn der Rückgabewert != 0 ist, ist ein Fehler bei der Konvertierung aufgetreten
		}
		
		
	
		//toggle_trigger speichern
		Listenplatz++;
		//Herausfinden wo der Doppelpunkt in der Zeile ist:
		positionen = String_Operationen::Positionen_von_Elementen_in_String(Liste[Listenplatz], ':');
		j=0; //Zaehlervariable im Ausgangsstring, die bestimmt welcher Buchstabe grade eingelesen wird
		h=0; //Bestimmt in welcher Zeile wir von "Zeile" sind (0 oder 1) Zeile[h][0-39]
		i=0;
		for(j=0; j<positionen[0];) // Der Teil vor dem : wird abgegrast
		{
			if((Liste[Listenplatz][j] != '_') && (Liste[Listenplatz][j] != ':') && (Liste[Listenplatz][j] !=  '"') && (Liste[Listenplatz][j] !=  '\0'))
			{
				Zeile[0][i] = Liste[Listenplatz][j];
				Zeile[0][i+1] = '\0';
				i++;
			}
			j++;
		}
		i=0;
		for(; j<String_Operationen::lenght(Liste[Listenplatz]);) // Der Teil nach dem : wird abgegrast
		{
			if((Liste[Listenplatz][j] != '_') && (Liste[Listenplatz][j] != ':') && (Liste[Listenplatz][j] !=  '"') && (Liste[Listenplatz][j] !=  '\0'))
			{
				Zeile[1][i] = Liste[Listenplatz][j];
				Zeile[1][i+1] = '\0';
				i++;
			}
			j++;
		}
		

		if(String_Operationen::Compare_Char_Arrays(Zeile[0], ("toggletrigger")))   //Es muss die String Methode toCharArray() benutzt werden, da ich in Java kein Char Array einfach so Hardgecodet schreiben kann
		{
			if(String_Operationen::Compare_Char_Arrays(Zeile[1], ("true")))
			{
				Aktor._status = true;
			}
			else
			{
				if(String_Operationen::Compare_Char_Arrays(Zeile[1], ("false")))
				{
					Aktor._status = false;
				}
				else
				{
					result++;
				}
			}
		}		
		else
		{
			result++; //Wenn der Rückgabewert != 0 ist, ist ein Fehler bei der Konvertierung aufgetreten
		}

		//Im gutfall eine Rückmeldung geben, dass die Transformation geklappt hat
		return result;
}

// default destructor
Aktor::~Aktor()
{
} //~Aktor

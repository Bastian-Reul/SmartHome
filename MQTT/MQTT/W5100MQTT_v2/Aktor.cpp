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



int Aktor::JSON_2_Aktor(char* JSON_Input)
{
	/*Im ersten Teil wird der JSON String an dem Kommata aufgeteilt, so dass die Parameter getrennt voneinander, jedoch mit ihren
	Bezeichner in einem String stehen:
	"_Topic":"Test/objects/Aktor1","_status":true,"Adresse":739,"_toggle":true
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
	int positionen[10] = { 999, 999, 999, 999, 999, 999, 999, 999, 999, 999 };
	int *positionen_zeiger = positionen;
	String_Operationen::Positionen_von_Elementen_in_String(JSON_Input, ',', positionen_zeiger);
	int anzahl_Positionen = 0;
	for (int i = 0; i < 10; i++)
	{
		if (positionen[i] != 999)
		{
			anzahl_Positionen++;
		}
	}


	int j = 0; //j bestimmt an welcher Position wir im Ausgangsstring sind
	int h = 0; //h bestimmt an welcher Position Position wir in der aktuellen Zeile der Liste sind Liste[0-4][h]
	int laenge_JSON_String = String_Operationen::lenght(JSON_Input);
	for (int i = 0; i <= anzahl_Positionen; i++) //i bestimmt in welcher Zeile von Liste[i][0-39] wir sind
	{
		for (h = 0; (j < positionen[i]) && (j < laenge_JSON_String); h++)
		{
			Liste[i][h] = JSON_Input[j];
			Liste[i][h + 1] = '\0';
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

	char Zeile[2][40];
	char Hilfsstring[100];
	char* Hilfsstring_Zeiger = Hilfsstring;
	char* String_1_Zeiger;
	char* String_2_Zeiger;

	//Topic speichern
	//Herausfinden wo der Doppelpunkt in der Zeile ist:
	String_Operationen::Positionen_von_Elementen_in_String(Liste[0], ':', positionen_zeiger);
	j = 0; //Zaehlervariable im Ausgangsstring, die bestimmt welcher Buchstabe grade eingelesen wird
	h = 0; //Bestimmt in welcher Zeile wir von "Zeile" sind (0 oder 1) Zeile[h][0-39]
	int i = 0;
	for (j = 0; j < positionen[0];) // Der Teil vor dem : wird abgegrast
	{
		if ((Liste[Listenplatz][j] != '_') && (Liste[Listenplatz][j] != ':') && (Liste[Listenplatz][j] != '"') && (Liste[Listenplatz][j] != '\0'))
		{
			Zeile[0][i] = Liste[Listenplatz][j];
			Zeile[0][i + 1] = '\0';
			i++;
		}
		j++;
	}
	i = 0;
	for (; j < String_Operationen::lenght(Liste[Listenplatz]);) // Der Teil nach dem : wird abgegrast
	{
		if ((Liste[Listenplatz][j] != '_') && (Liste[Listenplatz][j] != ':') && (Liste[Listenplatz][j] != '"') && (Liste[Listenplatz][j] != '\0'))
		{
			Zeile[1][i] = Liste[Listenplatz][j];
			Zeile[1][i + 1] = '\0';
			i++;
		}
		j++;
	}


	//char String_1[] = Zeile[0];


	String_Operationen::write_short_into_long_string(Hilfsstring_Zeiger, (char*)"Topic\0");
	if (String_Operationen::Compare_Char_Arrays((char*)Zeile[0], Hilfsstring_Zeiger))
	{
		_Topic = Zeile[1];
	}
	else
	{
		result++; //Wenn der Rückgabewert != 0 ist, ist ein Fehler bei der Konvertierung aufgetreten
	}

	//status speichern
	Listenplatz++;
	//Herausfinden wo der Doppelpunkt in der Zeile ist:
	String_Operationen::Positionen_von_Elementen_in_String(Liste[Listenplatz], ':', positionen_zeiger);
	j = 0; //Zaehlervariable im Ausgangsstring, die bestimmt welcher Buchstabe grade eingelesen wird
	h = 0; //Bestimmt in welcher Zeile wir von "Zeile" sind (0 oder 1) Zeile[h][0-39]
	i = 0;
	for (j = 0; j < positionen[0];) // Der Teil vor dem : wird abgegrast
	{
		if ((Liste[Listenplatz][j] != '_') && (Liste[Listenplatz][j] != ':') && (Liste[Listenplatz][j] != '"') && (Liste[Listenplatz][j] != '\0'))
		{
			Zeile[0][i] = Liste[Listenplatz][j];
			Zeile[0][i + 1] = '\0';
			i++;
		}
		j++;
	}
	i = 0;
	for (; j < String_Operationen::lenght(Liste[Listenplatz]);) // Der Teil nach dem : wird abgegrast
	{
		if ((Liste[Listenplatz][j] != '_') && (Liste[Listenplatz][j] != ':') && (Liste[Listenplatz][j] != '"') && (Liste[Listenplatz][j] != '\0'))
		{
			Zeile[1][i] = Liste[Listenplatz][j];
			Zeile[1][i + 1] = '\0';
			i++;
		}
		j++;
	}

	String_Operationen::write_short_into_long_string(Hilfsstring_Zeiger, (char*)"status\0");

	if (String_Operationen::Compare_Char_Arrays((char*)Zeile[0], Hilfsstring_Zeiger))   //Es muss die String Methode toCharArray() benutzt werden, da ich in Java kein Char Array einfach so Hardgecodet schreiben kann
	{
		String_Operationen::write_short_into_long_string(Hilfsstring_Zeiger, (char*)"true\0");
		if (String_Operationen::Compare_Char_Arrays(Zeile[1], Hilfsstring_Zeiger))
		{
			_status = true;
		}
		else
		{
			String_Operationen::write_short_into_long_string(Hilfsstring_Zeiger, (char*)"false\0");
			if (String_Operationen::Compare_Char_Arrays((char*)Zeile[1], Hilfsstring_Zeiger))
			{
				_status = false;
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

	//Adresse speichern
	Listenplatz++;
	//Herausfinden wo der Doppelpunkt in der Zeile ist:
	String_1_Zeiger = Liste[Listenplatz];
	String_Operationen::Positionen_von_Elementen_in_String(String_1_Zeiger, ':', positionen_zeiger);
	j = 0; //Zaehlervariable im Ausgangsstring, die bestimmt welcher Buchstabe grade eingelesen wird
	h = 0; //Bestimmt in welcher Zeile wir von "Zeile" sind (0 oder 1) Zeile[h][0-39]
	i = 0;
	for (j = 0; j < positionen[0];) // Der Teil vor dem : wird abgegrast
	{
		if ((Liste[Listenplatz][j] != '_') && (Liste[Listenplatz][j] != ':') && (Liste[Listenplatz][j] != '"') && (Liste[Listenplatz][j] != '\0'))
		{
			Zeile[0][i] = Liste[Listenplatz][j];
			Zeile[0][i + 1] = '\0';
			i++;
		}
		j++;
	}
	i = 0;
	String_1_Zeiger = Liste[Listenplatz];
	for (; j < String_Operationen::lenght(String_1_Zeiger);) // Der Teil nach dem : wird abgegrast
	{
		if ((Liste[Listenplatz][j] != '_') && (Liste[Listenplatz][j] != ':') && (Liste[Listenplatz][j] != '"') && (Liste[Listenplatz][j] != '\0'))
		{
			Zeile[1][i] = Liste[Listenplatz][j];
			Zeile[1][i + 1] = '\0';
			i++;
		}
		j++;
	}


	String_Operationen::write_short_into_long_string(Hilfsstring_Zeiger, (char*)"Adresse\0");
	if (String_Operationen::Compare_Char_Arrays((char*)Zeile[0], Hilfsstring_Zeiger))  //Es muss die String Methode toCharArray() benutzt werden, da ich in Java kein Char Array einfach so Hardgecodet schreiben kann
	{
		String_1_Zeiger = Zeile[1];
		Adresse = String_Operationen::char_array_to_int(String_1_Zeiger);
	}
	else
	{
		result++; //Wenn der Rückgabewert != 0 ist, ist ein Fehler bei der Konvertierung aufgetreten
	}



	//toggle speichern
	Listenplatz++;
	//Herausfinden wo der Doppelpunkt in der Zeile ist:
	String_1_Zeiger = Liste[Listenplatz];
	String_Operationen::Positionen_von_Elementen_in_String(String_1_Zeiger, ':', positionen_zeiger);
	j = 0; //Zaehlervariable im Ausgangsstring, die bestimmt welcher Buchstabe grade eingelesen wird
	h = 0; //Bestimmt in welcher Zeile wir von "Zeile" sind (0 oder 1) Zeile[h][0-39]
	i = 0;
	for (j = 0; j < positionen[0];) // Der Teil vor dem : wird abgegrast
	{
		if ((Liste[Listenplatz][j] != '_') && (Liste[Listenplatz][j] != ':') && (Liste[Listenplatz][j] != '"') && (Liste[Listenplatz][j] != '\0'))
		{
			Zeile[0][i] = Liste[Listenplatz][j];
			Zeile[0][i + 1] = '\0';
			i++;
		}
		j++;
	}
	i = 0;
	String_1_Zeiger = Liste[Listenplatz];
	for (; j < String_Operationen::lenght(String_1_Zeiger);) // Der Teil nach dem : wird abgegrast
	{
		if ((Liste[Listenplatz][j] != '_') && (Liste[Listenplatz][j] != ':') && (Liste[Listenplatz][j] != '"') && (Liste[Listenplatz][j] != '\0'))
		{
			Zeile[1][i] = Liste[Listenplatz][j];
			Zeile[1][i + 1] = '\0';
			i++;
		}
		j++;
	}

	String_Operationen::write_short_into_long_string(Hilfsstring_Zeiger, (char*)"toggle\0");
	if (String_Operationen::Compare_Char_Arrays((char*)Zeile[0], Hilfsstring_Zeiger))		  //Es muss die String Methode toCharArray() benutzt werden, da ich in Java kein Char Array einfach so Hardgecodet schreiben kann
	{
		String_Operationen::write_short_into_long_string(Hilfsstring_Zeiger, (char*)"true\0");
		if (String_Operationen::Compare_Char_Arrays((char*)Zeile[1], Hilfsstring_Zeiger))
		{
			_toggletrigger = true;
		}
		else
		{
			String_Operationen::write_short_into_long_string(Hilfsstring_Zeiger, (char*)"false\0");
			if (String_Operationen::Compare_Char_Arrays((char*)Zeile[1], Hilfsstring_Zeiger))
			{
				_toggletrigger = false;
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

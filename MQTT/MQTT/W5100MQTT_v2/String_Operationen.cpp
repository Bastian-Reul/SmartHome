/* 
* String_Operationen.cpp
*
* Created: 21.07.2019 15:35:12
* Author: Bastian
Version 0.0.1
*/


#include "String_Operationen.h"

String_Operationen::String_Operationen()
{
}


String_Operationen::~String_Operationen()
{
}

void String_Operationen::search_for_next_two_quotation_marks(int start_position, char* String2searchFor, int* quotation_mark_position)
{
	int j = 0;
	for (int i = start_position; String2searchFor[i] != '\0'; i++)
	{
		if (j < 2)
		{
			if (String2searchFor[i] == '"') //wenn Anf�hrungszeichen erkannt wurden
			{
				quotation_mark_position[j] = i;
				j++;
			}

		}
	}
}

void String_Operationen::String_between_quotation_marks(char* Pointer_to_String_with_2quot_marks, char* Pointer_to_String_between_2_quot_marks)
{
	int quot_marks_pos[2];
	int* quot_marks_zeiger = quot_marks_pos;
	search_for_next_two_quotation_marks(0, Pointer_to_String_with_2quot_marks, quot_marks_zeiger);
	for (int i = 0; i < (quot_marks_pos[1] - quot_marks_pos[0] - 1); i++)
	{
		Pointer_to_String_between_2_quot_marks[i] = Pointer_to_String_with_2quot_marks[i + quot_marks_pos[0] + 1];
		Pointer_to_String_between_2_quot_marks[i + 1] = '\0';
	}
}





void String_Operationen::Positionen_von_Elementen_in_String(char InputString[], char Character_to_search_for, int *zeiger_auf_array)
{
	int i = 0;
	int j = 0;
	while (InputString[i] != '\0')
	{
		if (InputString[i] == Character_to_search_for)
		{
			zeiger_auf_array[j] = i;
			j++;
		}
		i++;
	}
}

//gibt die L�nge eines Strings zur�ck
int String_Operationen::lenght(char* InputString)
{
	int i = 0;
	while (InputString[i] != '\0')
	{
		i++;
	}
	return i;
}


//Gibt true zur�ck, wenn zwei Char Arrays die gleichen "druckbaren" Zeichen enthalten, aber sich in der L�nge der angeh�ngten freien Stellen unterscheiden
//boolean String_Operationen::Compare_Char_Arrays(char[] String_1, char[] String_2)
bool String_Operationen::Compare_Char_Arrays(char* String_1, char* String_2)
{
	int i = 0;
	int mismatch = 0;
	for (i = 0; i < 50; i++) //i<50 verhindert, dass der Vergleich Amok l�uft
	{
		if ((String_1[i] != '\0') && (String_2[i] != '\0'))
		{
			if (is_printable_sign(String_1[i]) && is_printable_sign(String_2[i]))
			{
				if (String_1[i]==String_2[i])
				{
					//alles gut
				}
				else
				{
					//Die Beiden druckbaren Zeichen unterscheiden sich
					mismatch++;
				}
			}
			else  //Der String enthaelt nicht druckbare Zeichen
			{
				mismatch++;
			}
		}
		else //mindestens ein Zeichen ist '\0'
		{
			if (String_1[i] != String_2[i]) //nur ein Zeichen ist '\0'
			{
				mismatch++;
			}
			else //Beide Strings sind an ihrem Ende angekommen
			{
				if (mismatch <=0)
				{
					return true; //Beide Strings sind identisch, springe raus
				}
			}
		}
	}
	return false; //Es gab mindestens einen Unterschied zwischen den beiden Strings
}

void String_Operationen::write_short_into_long_string(char* ziel, char* quelle)
{
	for (int i = 0; i < lenght(quelle); i++)
	{
		ziel[i] = quelle[i];
		ziel[i+1] = '\0';
	}
}

int String_Operationen::char_array_to_int(char* InputString)
{
	int zahl = 0;
	bool negativ = false;
	int laufindex = 0;
	int Potenz = 0;
	if (InputString[0] == '-')
	{
		negativ = true;
		laufindex++;
	}
	for (; InputString[laufindex] != '\0'; laufindex++)
	{
		zahl = zahl * 10;

		Potenz++;
		switch (InputString[laufindex])
		{
			case '0':
			zahl = zahl;
			break;
			case '1':
			zahl = zahl + 1;
			break;
			case '2':
			zahl = zahl + 2;
			break;
			case '3':
			zahl = zahl + 3;
			break;
			case '4':
			zahl = zahl + 4;
			break;
			case '5':
			zahl = zahl + 5;
			break;
			case '6':
			zahl = zahl + 6;
			break;
			case '7':
			zahl = zahl + 7;
			break;
			case '8':
			zahl = zahl + 8;
			break;
			case '9':
			zahl = zahl + 9;
			break;
			default:
			//Fehlerfall sollte irgendwie noch abgehandelt werden
			break;
		}
		if (negativ)
		{
			zahl = zahl * (-1);
		}

	}

	return zahl;
}


//gibt true zur�ck wenn das �bergebene Zeichen ein "druckbares" Zeichen ist (Kein \0, CR oder �hnliches)
bool String_Operationen::is_printable_sign(char testzeichen)
{
	if((32 < testzeichen)&&(testzeichen < 127))
	{
		return true;
	} 
	else
	{
		return false;
	}
	
}
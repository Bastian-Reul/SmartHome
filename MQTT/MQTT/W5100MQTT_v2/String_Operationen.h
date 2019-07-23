/* 
* String_Operationen.h
*
* Created: 21.07.2019 15:35:13
* Author: Bastian
*/


#ifndef __STRING_OPERATIONEN_H__
#define __STRING_OPERATIONEN_H__


class String_Operationen
{
//variables
public:
protected:
private:

//functions
public:
	String_Operationen();
		static void search_for_next_two_quotation_marks(int start_position, char* String2searchFor, int* quotation_mark_position);
		static void String_between_quotation_marks(char* Pointer_to_String_with_2quot_marks, char* Pointer_to_String_between_2_quot_marks);
		static void Positionen_von_Elementen_in_String(char* InputString, char Character_to_search_for, int *zeiger_auf_array);
		static int lenght(char* InputString);
		static int char_array_to_int(char* InputString);
		static bool Compare_Char_Arrays(char* String_1, char* String_2);
		static void write_short_into_long_string(char* ziel, char* quelle);
		
	~String_Operationen();
protected:
private:
	String_Operationen( const String_Operationen &c );
	String_Operationen& operator=( const String_Operationen &c );

}; //String_Operationen

#endif //__STRING_OPERATIONEN_H__

package de.extern;

public class String_Operationen {

	public static int[] search_for_next_two_quotation_marks(int start_position, char[] String2searchFor)
	{
		int[] quotation_mark_position = { 0 , 0};
		int j=0;
		for(int i=start_position; String2searchFor[i]!='\n'; i++)
		{
			if (j<2)
			{
				if(String2searchFor[i]=='"') //wenn Anführungszeichen erkannt wurden
				{
					quotation_mark_position[j] = i;
					j++;
				}
				
			}
		}
		return quotation_mark_position;
	}
	
	public static char[] String_between_quotation_marks(char[] String_with_2quot_marks)
	{
		char[] Param = new char[30];
		int[] quot_marks_pos = search_for_next_two_quotation_marks(0, String_with_2quot_marks);
		for(int i=0; i<(quot_marks_pos[1]-quot_marks_pos[0]-1); i++)
		{
			Param[i] = String_with_2quot_marks[i+quot_marks_pos[0]+1];
			Param[i+1] = '\n';
		}
		for(int i=0; Param[i]!='\n'; i++)
		{
			System.out.print(Param[i]);
		}
		return Param;
	}
	
	public static int[] Positionen_von_Elementen_in_String(char[] InputString, char Character_to_search_for)
	{
		int[] Positionen = {999, 999, 999, 999, 999, 999, 999, 999, 999, 999};
		int i=0;
		int j=0;
		while(InputString[i]!='\n')
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
	
	//gibt die Länge eines Strings zurück
	public static int lenght(char[] InputString)
	{
		int i=0;
		while(InputString[i]!='\n')
		{
			i++;
		}
		return i;
	}
	
	public static char[] String_to_Char_Array(String eingabestring)
	{
		char[] AusgabeArray = new char[40];
		AusgabeArray= eingabestring.toCharArray();	
		return AusgabeArray;
	}
	
	public static int char_array_to_int(char[] InputString)
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
		for(; InputString[laufindex] != '\n'; laufindex++)
		{
			if(negativ)
			{
				Potenz = laufindex-1;
			}
			zahl = (int) (zahl * Math.pow(10.0, Potenz));
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
				System.out.println("Fehler in char_array_to_int");
				break;
			}
			if(negativ)
			{
				zahl = zahl *(-1);
			}
			
		}
		
		return zahl;
	}
	
}

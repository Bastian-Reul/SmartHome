
	package de.extern;
	import de.extern.String_Operationen;

public class Aktor {

	//public char[200] Topic; f�hrt in JAVA zu Compilerfehlern
	private int Topic_Laenge = 200;
	public char[] Topic = new char[Topic_Laenge];
	
	boolean status = false;
	int Schaltvorgaenge = 0;
	int Adresse = 0;
	boolean toogle_trigger = false; 
	
	public void schalte_ein()
	{
		status = true;
		Schaltvorgaenge++;
		System.out.println("Aktor wurde eingeschaltet.");
	}
	
	void schalte_aus()
	{
		status = false;
		System.out.println("Aktor wurde eingeschaltet.");
	}
	
	public void schalte(boolean einschalten)
	{
		if(!(einschalten == get_status())) 
		{
			if(einschalten == true)
			{
				schalte_ein();
			}
			else
			{
				schalte_aus();
			}
		}
		else
		{
			System.out.println("Aktor war bereits im angeforderten Status.");
		}
	}
	
	void toogle()
	{
		if(status == true)
		{
			schalte(false);
		}
		else
		{
			schalte(true);
		}
	}
	
	public boolean get_status()
	{
		return status;
	}
	
	public char[] get_topic()
	{
		//Sicherstellen, dass das Char Array einen Begrenzer hat, dass die Ausgabe des String auf jeden Fall enden l�sst
		//Topic[199] = '\n';
		return Topic;
	}
	
	public int get_Topic_Lanege()
	{
		return Topic_Laenge;
	}
	
	public int JSON_2_Aktor(char[] JSON_Input)
	{
		/*Im ersten Teil wird der JSON String an dem Kommata aufgeteilt, so dass die Parameter getrennt voneinander, jedoch mit ihren
		Bezeichner in einem String stehen:
		"_Topic":"Test/objects/Aktor1","_status":true,"_schaltvorgaenge":2,"Adresse":739,"_toggle_trigger":true
		wird zu:
		char Liste[5][40]
		[0]['"','_','T','o','p','i','c','"',':','"','T','e','s','t','/','o','b','j','e','c','t','s','/','A','k','t','o','r','1','"','\n']
		[1]['"','_','s','t','a','t','u','s','"',':','t','r','u','e','\n']
		[2]....
		[3]....
		[4]....
		*/
		int result = 0;
		System.out.println("JSON_2_Aktor:");

		char[][] Liste = new char[5][40];
		char[] typ = new char[40];
		char[] wert = new char[40];
		
		//Erkennen wieviele Kommata im Text �berhaupt sind
		int[] positionen = String_Operationen.Positionen_von_Elementen_in_String(JSON_Input, ',');
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
		int laenge_JSON_String = String_Operationen.lenght(JSON_Input);
		for(int i=0; i<=anzahl_Positionen; i++) //i bestimmt in welcher Zeile von Liste[i][0-39] wir sind
		{
			for(h=0; (j<positionen[i])&&(j<laenge_JSON_String); h++)
			{
				Liste[i][h] = JSON_Input[j];
				Liste[i][h+1] = '\n';
				j++;
			}
			j++;
		}
		//Ende erster Teil 
		
		//Anfang zweiter Teil
		/*Im zweiten Teil wird die char Liste[5][40] Zeile f�r Zeile durchgearbeitet
		 * Um Speicherplatz zu sparen, wird jedoch eine Zeile ausgelesen, am Doppelpunkt in zwei Char Arrays (char Zeile[2][40])
		 * gespeichert, beschnitten (Anf�hrungszeichen heraus, etc) und dann in den entsprechenden Aktor Parameter abgespeichert
		 * Danach wird genauso mit der n�chsten Zeile aus char Liste[5][40] verfahren. Daf�r kann dann wieder das gleiche char Zeile[2][40]
		 * benutzt werden um Speicherplatz zu sparen
		 * 		char Liste[5][40]
				[0]['"','_','T','o','p','i','c','"',':','"','T','e','s','t','/','o','b','j','e','c','t','s','/','A','k','t','o','r','1','"','\n']
				[1]['"','_','s','t','a','t','u','s','"',':','t','r','u','e','\n']
				 wird zu:
				char Zeile[2][40]
				[0]['_','T','o','p','i','c','\n']
				[1]['T','e','s','t','/','o','b','j','e','c','t','s','/','A','k','t','o','r','1','\n']
				
				und wird dann abgespeichert
				Topic = Zeile[1];
		 */
		
		char[][] Zeile = new char[2][40];
		
		//Topic speichern
		//Herausfinden wo der Doppelpunkt in der Zeile ist:
		positionen = String_Operationen.Positionen_von_Elementen_in_String(Liste[0], ':');
		j=0; //Zaehlervariable im Ausgangsstring, die bestimmt welcher Buchstabe grade eingelesen wird
		h=0; //Bestimmt in welcher Zeile wir von "Zeile" sind (0 oder 1) Zeile[h][0-39]
		int i=0;
		for(j=0; j<positionen[0];) // Der Teil vor dem : wird abgegrast
		{
			if((Liste[0][j] != '_') && (Liste[0][j] != ':') && (Liste[0][j] !=  '"') && (Liste[0][j] !=  '\n'))
			{
				Zeile[0][i] = Liste[0][j];
				Zeile[0][i+1] = '\n';
				i++;
			}
			j++;
		}
		i=0;
		for(; j<String_Operationen.lenght(Liste[0]);) // Der Teil nach dem : wird abgegrast
		{
			if((Liste[0][j] != '_') && (Liste[0][j] != ':') && (Liste[0][j] !=  '"') && (Liste[0][j] !=  '\n'))
			{
				Zeile[1][i] = Liste[0][j];
				Zeile[1][i+1] = '\n';
				i++;
			}
			j++;
		}
		
		typ = "Topic\n";
		if(Zeile[0] =  char[]("Topic\n"))    //  'T','o','p','i','c','\n')
		{
			
		}
		
		//Debugging
		System.out.println("Debugging:");
		for(int _i=0; _i<=1; _i++)
		{
			System.out.println(Zeile[_i]);
		}
		
	/*	
		int[] quot_marks_pos = String_Operationen.search_for_next_two_quotation_marks(0, JSON_Input);
		for(int i=0; i<(quot_marks_pos[1]-quot_marks_pos[0]-1); i++)
		{
			Param[0][i] = Topic[i+quot_marks_pos[0]+1];
			Param[0][i+1] = '\n';
		}
		for(int i=0; Param[0][i]!='\n'; i++)
		{
			System.out.print(Param[0][i]);
		}*/
		//Im gutfall eine R�ckmeldung geben, dass die Transformation geklappt hat
		return result;
	}
	

}


	package de.extern;
	import de.extern.String_Operationen;

public class Aktor {

	//public char[200] Topic; führt in JAVA zu Compilerfehlern
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
		//Sicherstellen, dass das Char Array einen Begrenzer hat, dass die Ausgabe des String auf jeden Fall enden lässt
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
		[0]['"','_','T','o','p','i','c','"',':','"','T','e','s','t','/','o','b','j','e','c','t','s','/','A','k','t','o','r','1','"']
		[1]['"','_','s','t','a','t','u','s','"',':','t','r','u','e']
		[2]....
		[3]....
		[4]....
		*/
		System.out.println("JSON_2_Aktor:");

		char[][] Liste = new char[5][40];
		
		//Erkennen wieviele Kommata im Text überhaupt sind
		int[] positionen = String_Operationen.Positionen_von_Elementen_in_String(JSON_Input, ',');
		int anzahl_Positionen = 0;
		for(int i=0; i<10; i++)
		{
			if(positionen[i]!=999)
			{
				anzahl_Positionen++;
			}
		}
		
		//im Bezug zum letzten Trennzeichen
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
		
		//Debugging
		for(int i=0; i<=anzahl_Positionen; i++)
		{
			System.out.println(Liste[i]);
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
		//Im gutfall eine Rückmeldung geben, dass die Transformation geklappt hat
		return 0;
	}
	

}

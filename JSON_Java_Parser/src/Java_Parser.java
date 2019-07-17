import de.extern.Aktor;
import de.extern.String_Operationen;

public class Java_Parser {

	
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Aktor Relais1 = new Aktor();

		String JSON_string = "\"_Topic\":\"Test/objects/Aktor1\",\"_status\":false,\"_schaltvorgaenge\":2,\"_Adresse\":739,\"_toggle_trigger\":true";
		char[] JSON_char_Array = JSON_string.toCharArray();
		String JSON_string_neu = "\"_Topic\":\"Test/objects/Aktor1\",\"_status\":true,\"_schaltvorgaenge\":2,\"_Adresse\":739,\"_toggle_trigger\":true\0";
		char[] JSON_char_Array_neu = JSON_string_neu.toCharArray();
		
		
		for(int i=0; i<JSON_string.length(); i++)
		{
			System.out.print(JSON_char_Array[i]);
			Relais1.Topic[i] = JSON_char_Array[i];
		}
		System.out.println(" ");
		System.out.println("Ende");
		
		
		System.out.print("Der Status von Relais1 ist: ");
		System.out.println(Relais1.get_status());
		System.out.println("Relais1 wird eingeschaltet: ");
		Relais1.schalte(true);
		System.out.print("Der Status von Relais1 ist: ");
		System.out.println(Relais1.get_status());
		Relais1.schalte(true);
		
		char[] Relais_Array = Relais1.get_topic();
		

			System.out.print(JSON_char_Array_neu);

		
		System.out.println("wird gewandelt");
		System.out.println(" ");

	
		int[] positionen = new int[10];
		positionen = String_Operationen.Positionen_von_Elementen_in_String(JSON_char_Array_neu, ',');
		Relais1.Ausgabe_GesammtStatus();
		System.out.println(" ");
		if(Relais1.JSON_2_Aktor(JSON_char_Array_neu)!=0)
		{
			System.out.println("Fehler bei der JSON Konvertierung");
		}
		System.out.println(" ");
		Relais1.Ausgabe_GesammtStatus();
	/*	System.out.println("Das neue Topic: ");
		char [] neuer_Topic = Relais1.get_topic();
		for(int i=0; neuer_Topic[i]!='\0'; i++)
		{
			System.out.print(neuer_Topic[i]);
		}*/
	}

}

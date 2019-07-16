import de.extern.Aktor;

public class Java_Parser {

	
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Aktor Relais1 = new Aktor();

		String JSON_string = "\"_Topic\":\"Test/objects/Aktor1\",\"_status\":false,\"_schaltvorgaenge\":2,\"Adresse\":739,\"_toggle_trigger\":true";
		char[] JSON_char_Array = JSON_string.toCharArray();
		String JSON_string_neu = "\"_Topic\":\"Test/objects/Aktor1\",\"_status\":true,\"_schaltvorgaenge\":2,\"Adresse\":739,\"_toggle_trigger\":true\n";
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
		
		for(int i=0; i<Relais1.get_Topic_Lanege(); i++)
		{
			System.out.print(Relais_Array[i]);
		}
		System.out.println(" ");
		System.out.println("MQTT Topic Ende");
		//Relais_Array[50] = '\n';
		
		for(int i=0; i<100; i++)
		{
			System.out.print(Relais_Array[i]);
		}
		System.out.println(" ");
		Relais1.JSON_2_Aktor(JSON_char_Array_neu);
		System.out.println(" ");
		System.out.println("Das neue Topic: ");
		char [] neuer_Topic = Relais1.get_topic();
		for(int i=0; neuer_Topic[i]!='\n'; i++)
		{
			System.out.print(neuer_Topic[i]);
		}
	}

}

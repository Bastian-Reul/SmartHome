import de.extern.Aktor;

public class Java_Parser {

	
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Aktor Relais1 = new Aktor();
/*
		String JSON_string = "\"_Topic\":\"Test/objects/Aktor1\",\"_status\":false,\"_schaltvorgaenge\":2,\"Adresse\":739,\"_toggle_trigger\":true";
		char[] JSON_char_Array = JSON_string.toCharArray();
		
		for(int i=0; i<JSON_string.length(); i++)
		{
			System.out.print(JSON_char_Array[i]);
		}
		System.out.println(" ");
		System.out.println("Ende");
	*/	
		
		System.out.print("Der Status von Relais1 ist: ");
		System.out.println(Relais1.get_status());
		System.out.println("Relais1 wird eingeschaltet: ");
		Relais1.schalte_ein();
		System.out.print("Der Status von Relais1 ist: ");
		System.out.println(Relais1.get_status());
	}

}

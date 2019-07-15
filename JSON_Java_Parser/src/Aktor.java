
public class Aktor {

	//char[]Topic;
	boolean status = false;
	int Schaltvorgaenge = 0;
	int Adresse = 0;
	boolean toogle_trigger = false; 
	
	void schalte_ein()
	{
		status = true;
		Schaltvorgaenge++;
	}
	
	void schalte_aus()
	{
		status = false;
	}
	
	void schalte(boolean einschalten)
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
}

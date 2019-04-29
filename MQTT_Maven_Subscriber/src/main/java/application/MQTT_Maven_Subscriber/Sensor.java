package application.MQTT_Maven_Subscriber;

public class Sensor
{
	private String _Topic;
	private boolean _status = false;
	private int _schaltvorgaenge = 0;
	private boolean _impuls_aktiv = false;
	public int Adresse = 739;
	
	public void set_Status(boolean status)
	{
		_status = status;
		_schaltvorgaenge++;
	}
	
	public boolean get_status()
	{
		return _status;
	}
	
	public int get_schaltvorgaenge()
	{
		return _schaltvorgaenge;
	}
	
	public void reset_impuls()
	{
		_impuls_aktiv = false;
	}
	
	public void set_Topic(String Topic)
	{
		_Topic = Topic;
	}
	
	public String get_Topic()
	{
		return _Topic;
	}
	
	public void impuls_on()
	{
		_impuls_aktiv = true;
	}
	
	public boolean get_impuls_aktuell()
	{
		return _impuls_aktiv;
	}
	
	
}

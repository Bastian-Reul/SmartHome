package application.MQTT_Maven_Subscriber;

public class Aktor
{
	private String _Topic;
	private boolean _status = false;
	private int _schaltvorgaenge = 0;
	private boolean _toggle_trigger = false;
	
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
	
	public void set_Topic(String Topic)
	{
		_Topic = Topic;
	}
	
	public String get_Topic()
	{
		return _Topic;
	}
	
	public boolean get_Trigger()
	{
		return _toggle_trigger;
	}	
	public void reset_Trigger()
	{
		_toggle_trigger = false;
	}	
	
	public void toggle_status()
	{
		if(get_status())
		{
			set_Status(false);
		}
		else
		{
			set_Status(true);
		}
	}
	
}

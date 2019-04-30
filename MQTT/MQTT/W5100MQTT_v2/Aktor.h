/* 
* Aktor.h
*
* Created: 30.04.2019 12:26:22
* Author: Basti
*/


#ifndef __AKTOR_H__
#define __AKTOR_H__


class Aktor
{
//variables
public:
	String _Topic;
	bool _status = false;
	int _schaltvorgaenge = 0;
	bool _toggle_trigger = false;
	int Adresse = 739;
protected:
private:

//functions
public:
	Aktor();
	~Aktor();
protected:
private:
	Aktor( const Aktor &c );
	Aktor& operator=( const Aktor &c );

}; //Aktor

#endif //__AKTOR_H__

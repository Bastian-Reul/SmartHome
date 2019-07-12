#include "pch.h"
#include "JSON.h"


JSON::JSON()
{
	Objekttyp = 0;
}


JSON::JSON(Aktor AktorObject)
{
	Objekttyp = 1;
}
JSON::JSON(Taster TasterObject)
{
	Objekttyp = 2;
}

int JSON::ParseJson2Object()
{
	
}
int JSON::ParseObject2Jason()
{
	switch (Objekttyp)
	{
	case 0: //Fehlerhafte Deklaration des JSON Objekts
		break;
	case 1:	//Es handelt sich um einen Aktor
		
		break;
	case 2: //Es handelt sich um einen Taster
		break;

	default:
		break;
	}
}


JSON::~JSON()
{
}


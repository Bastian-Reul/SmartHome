#pragma once

#include "Aktor.h"
#include "Taster.h"

class JSON
{
	//Variables
public:
	
private:
	char pJSONString[50];
	__int8 Objekttyp;
protected:


	//Functions
public:
	JSON();
	JSON(Aktor AktorObject);
	JSON(Taster TasterObject);
	int ParseJson2Object();
	int ParseObject2Jason();
	~JSON();
	
private:
	

protected:
};


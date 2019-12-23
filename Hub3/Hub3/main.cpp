/*
 * Hub3.cpp
 *
 * Created: 22.12.2019 13:34:29
 * Author : Bastian
 */ 

#include <avr/io.h>
#include "Pin_ATMEGA128.h"

int main(void)
{
	Pin Status_LED('B', 3, false);
	Status_LED.setze_Status(true);
  
    /* Replace with your application code */
    while (1) 
    {
    }
}



//..begin "File Description"
/*--------------------------------------------------------------------------------*
   Filename   : Brewingssystem.h
   Description: 
 *--------------------------------------------------------------------------------*/
//..end "File Description"


//..begin "Ifdef"
#ifndef _Brewingsystem_H_
#define _Brewingsystem_H_
//..end "Ifdef"


//..begin "pragma"
#pragma once
//..end "pragma"

#include "globaldefines.h"
#include "waterpump.h"
#include "heater.h"

class Brewingsystem
{	
	
	public:
		Brewingsystem (void );
		~Brewingsystem (void );
		float brewCoffee (float TargetvolumeInMl);
        Waterpump * mWaterpumpHandle;
        Heater * mHeaterHandle;
	
	private:
};

//..begin "Endif"
#endif

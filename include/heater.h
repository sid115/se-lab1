
//..begin "File Description"
/*--------------------------------------------------------------------------------*
   Filename   : heater.h
   Description: 
 *--------------------------------------------------------------------------------*/
//..end "File Description"


//..begin "Ifdef"
#ifndef _HEATER_H
#define _HEATER_H
//..end "Ifdef"


//..begin "pragma"
#pragma once
//..end "pragma"

#include "globaldefines.h"

class Heater
{	
	public:
		Heater (void );
		~Heater (void );
		bool activateHeater ();
		bool deactivateHeater ();
		int measureWatertemperature (); 	/**	Value in Celsius	*/
        int heatupWatertank(int TargettemperatureInDegreesCelsius);		/**	Value in Celsius	*/
	
	private:
		int mWatertemperature;	/**	Thermometer, value in Celsius */
};

//..begin "Endif"
#endif

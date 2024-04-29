
//..begin "File Description"
/*--------------------------------------------------------------------------------*
   Filename   : Heater.cpp
   Description: 
 *--------------------------------------------------------------------------------*/
//..end "File Description"


#include "stdafx.h"
#include "brewingsystem.h"

Heater::Heater (void ){
	mWatertemperature = AMBIENTTEMPERATURE;
}

Heater::~Heater (void ){

}

bool Heater::activateHeater ()
{
	// Set corresponding Bit on I/O-Card 

	// Reset water tempetrature to ambient temperature for emulation
	mWatertemperature = AMBIENTTEMPERATURE;

	return (true); // No errors expected
}

bool Heater::deactivateHeater ()
{
	// Reset corresponding Bit on I/O-Card
	return (true); // No errors expected
}

int Heater::measureWatertemperature (){
	mWatertemperature ++;  // Emulate heating
	return (mWatertemperature);
}

int Heater::heatupWatertank (int TargettemperatureInCelsiusDegrees){
	if (measureWatertemperature() < TargettemperatureInCelsiusDegrees){
		activateHeater ();
		// Measure temperature and compare to target temperature
		do{
			measureWatertemperature();
		} while(mWatertemperature < TargettemperatureInCelsiusDegrees);
		deactivateHeater ();
	}
	return (mWatertemperature);
}

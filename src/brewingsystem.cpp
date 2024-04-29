
//..begin "File Description"
/*--------------------------------------------------------------------------------*
   Filename   : Brewingsystem.cpp
   Description: 
 *--------------------------------------------------------------------------------*/
//..end "File Description"


#include "stdafx.h"
#include "brewingsystem.h"

Brewingsystem::Brewingsystem (void ){
}

Brewingsystem::~Brewingsystem (void ){

}

float Brewingsystem::brewCoffee (float TargetvolumeInMl){
	float pumpedVolume;
	mWaterpumpHandle->openWatervalve ();
	mHeaterHandle->activateHeater();  // Fresh water at ambient temperature, turn on heater
	pumpedVolume = mWaterpumpHandle->pumpWater (TargetvolumeInMl);
	mHeaterHandle->deactivateHeater(); // Finished: Heater off
	mWaterpumpHandle->closeWatervalve();
	return (pumpedVolume);
}

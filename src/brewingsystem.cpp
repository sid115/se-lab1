
//..begin "File Description"
/*--------------------------------------------------------------------------------*
   Filename   : Brewingsystem.cpp
   Description: 
 *--------------------------------------------------------------------------------*/
//..end "File Description"


#include "stdafx.h"
#include "brewingsystem.h"

Brewingsystem::Brewingsystem (void ){
	mWatervolume = (float)0; // initial
	mWatervolume = measureWatervolume(); // Accurate volume on first call
	mWatervolume = measureWatervolume(); // Accurate volume difference on second call
	mWatertemperature = AMBIENTTEMPERATURE;
}

Brewingsystem::~Brewingsystem (void ){

}

bool Brewingsystem::activateHeater ()
{
	// Set corresponding Bit on I/O-Card 

	// Reset water tempetrature to ambient temperature for emulation
	mWatertemperature = AMBIENTTEMPERATURE;

	return (true); // No errors expected
}

bool Brewingsystem::deactivateHeater ()
{
	// Reset corresponding Bit on I/O-Card
	return (true); // No errors expected
}

bool Brewingsystem::activatePump ()
{
	// Set corresponding Bit on I/O-Card
	return (true); // No errors expected
}

bool Brewingsystem::deactivatePump ()
{
	// Reset corresponding Bit on I/O-Card
	return (true); // No errors expected
}

bool Brewingsystem::openWatervalve ()
{
	// Set corresponding Bit on I/O-Card
	return (true); // No errors expected
}

bool Brewingsystem::closeWatervalve ()
{
	// Reset corresponding Bit on I/O-Card
	return (true); // No errors expected
}

float Brewingsystem::pumpWater (float TargetvolumeInMl)
{
	// nominal inflow at 100ml/s -> 0,1ml/ms
	struct timespec scanDuration = {0, SCAN_DURATION_MS*1000};
	struct timespec rmD; // remainig duration
	float pumpedVolume; // Value in ml
	float startVolume = measureWatervolume(); // Value in ml
	float MinDeltaV = (float) ((1-EPSREL)*SCAN_DURATION_MS*(double)0.1); // 90% of nominal pumped volume in SCAN_DURATION_MS
	int countedPortions = 0;
	activatePump ();
	// Determine pumped volume and compare with target volume
	do{
		nanosleep(&scanDuration, &rmD); // Waiting for scanDuration ms => scanDuration * 0,1ml nominal
		// Calculate pumped volume since start of measurement
		// Calculate pumped volume since last time of measurement
		pumpedVolume = measureWatervolume() - startVolume;
		if (mActualDeltaV < MinDeltaV){
			break; // If pumping result is wrong: cancel process
		}
		countedPortions++;
	} while(pumpedVolume < TargetvolumeInMl);
	deactivatePump ();
	CURPOSGREENFTEXT(12, 32, "%-4d", countedPortions);
	CURPOSGREENFTEXT(12, 37, "%-3g", pumpedVolume);
	return (pumpedVolume);
}

float Brewingsystem::brewCoffee (float TargetvolumeInMl){
	float pumpedVolume;
	openWatervalve ();
	activateHeater();  // Fresh water at ambient temperature, turn on heater
	pumpedVolume = pumpWater (TargetvolumeInMl);
	deactivateHeater(); // Finished: Heater off
	closeWatervalve();
	return (pumpedVolume);
}

int Brewingsystem::measureWatertemperature (){
	mWatertemperature ++;  // Emulate heating
	return (mWatertemperature);
}

float Brewingsystem::measureWatervolume (){
	float lastVolume, deviation;
	// Save last value
	lastVolume = mWatervolume;
	// Measure
	deviation = (double)0.1001*(double)rand()/(double)RAND_MAX;
	mWatervolume += (0.1*SCAN_DURATION_MS*(1-deviation));  // Emulate volume flow rate
	// Calculate ActualDeltaV
	mActualDeltaV = mWatervolume - lastVolume;
	return (mWatervolume);
}

int Brewingsystem::heatupWatertank (int TargettemperatureInCelsiusDegrees){
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

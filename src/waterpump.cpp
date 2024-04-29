
//..begin "File Description"
/*--------------------------------------------------------------------------------*
   Filename   : Waterpump.cpp
   Description: 
 *--------------------------------------------------------------------------------*/
//..end "File Description"


#include "stdafx.h"
#include "waterpump.h"

Waterpump::Waterpump (void ){
	mWatervolume = (float)0; // initial
	mWatervolume = measureWatervolume(); // Accurate volume on first call
	mWatervolume = measureWatervolume(); // Accurate volume difference on second call
}

Waterpump::~Waterpump (void ){

}

bool Waterpump::activatePump ()
{
	// Set corresponding Bit on I/O-Card
	return (true); // No errors expected
}

bool Waterpump::deactivatePump ()
{
	// Reset corresponding Bit on I/O-Card
	return (true); // No errors expected
}

bool Waterpump::openWatervalve ()
{
	// Set corresponding Bit on I/O-Card
	return (true); // No errors expected
}

bool Waterpump::closeWatervalve ()
{
	// Reset corresponding Bit on I/O-Card
	return (true); // No errors expected
}

float Waterpump::pumpWater (float TargetvolumeInMl)
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

float Waterpump::measureWatervolume (){
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

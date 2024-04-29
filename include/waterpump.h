
//..begin "File Description"
/*--------------------------------------------------------------------------------*
   Filename   : waterpump.h
   Description: 
 *--------------------------------------------------------------------------------*/
//..end "File Description"


//..begin "Ifdef"
#ifndef _Waterpump_H_
#define _Waterpump_H_
//..end "Ifdef"


//..begin "pragma"
#pragma once
//..end "pragma"

#include "globaldefines.h"

class Waterpump
{	
	public:
		Waterpump (void );
		~Waterpump (void );
		bool activatePump ();
		bool deactivatePump ();
		bool openWatervalve ();
		bool closeWatervalve ();
		float pumpWater (float TargetvolumeInMl);
		float measureWatervolume ();

	private:
		float mWatervolume;	/**	latest count of the water meter, value in ml */
		float mActualDeltaV; /** watervolume as difference between the two latest times of measurement, value in ml	*/
};

//..begin "Endif"
#endif

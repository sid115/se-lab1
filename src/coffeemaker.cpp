
//..begin "File Description"
/*--------------------------------------------------------------------------------*
   Filename   : Coffeemaker.cpp
   Description: 
 *--------------------------------------------------------------------------------*/
//..end "File Description"

#include "stdafx.h"

const Consumptionrate Coffeemaker::mConsumptionrate[3][3]
= { //tiny, regular , large
	{{50,5},{120,10},{175,15}}, // delicate
	{{50,7},{120,14},{175,21}}, // medium
	{{50,9},{120,18},{175,27}}  // strong
};

const char Coffeemaker::sstext[4][17]={"READY         ", "PRODUCE COFFEE", "DESCALE       ", "ERROR         "};

//Constructor und Destructor
Coffeemaker::Coffeemaker(void){
	mGrinderHandle = new Grinder;
	mBrewingsystemHandle = new Brewingsystem;
	mStatus = sReady;
	CURPOSTEXT(4,  10, sstext[sReady]);
}

Coffeemaker::~Coffeemaker(void){
}

bool Coffeemaker::brewCup (sStrength aType, sCupsize bType){
	float ActualVolume;
	int ActualCoffeegrounds;
	int ActualTemperature;
	bool goodQuality = true;
	char logline[LOGLINELEN]={};
	struct timespec productionDuration = {PRODUCTION_DURATION_S, 0};
	struct timespec rmD; //remaining duration


	if (mStatus != sReady){
		return (false); // Brewing coffee only possibe at sReady.
	}

	// Change of state after sBrewing
	mStatus = sBrewing;
	CURPOSGREENTEXT(4,  10, sstext[sBrewing]);

	Consumptionrate Options = mConsumptionrate [(int)aType][(int)bType];
	snprintf(logline, LOGLINELEN, "Vol %dml, Strength %dg                                               ", Options.mlWater, Options.gCoffeegrounds);
	CURPOSGREENTEXT(5,  10, logline);

	// Grind coffee beans according to selected cup size and coffee strength
	ActualCoffeegrounds = mGrinderHandle->grindCoffeebeans(Options.gCoffeegrounds);
	nanosleep(&productionDuration, &rmD);
	if (abs(ActualCoffeegrounds-Options.gCoffeegrounds)>(EPSREL * Options.gCoffeegrounds)){
		goodQuality = false;
	}

	// Pour in coffee grounds
	mGrinderHandle->fillBrewingfilter();
	nanosleep(&productionDuration, &rmD);

	// Boil up water
	ActualTemperature = mBrewingsystemHandle->heatupWatertank(SETTEMPERATURE);
	if (abs(ActualTemperature-SETTEMPERATURE)>(EPSREL * SETTEMPERATURE)){
		goodQuality = false;
	}

	// Produce coffee
	ActualVolume = mBrewingsystemHandle->brewCoffee((float)Options.mlWater);
	if (fabs(ActualVolume-(float)Options.mlWater)>(EPSREL * (float) Options.mlWater)){
		goodQuality = false;
	}

	// Discard coffee grounds
	mGrinderHandle->emptyBrewingfilter();
	if (goodQuality==true){
		CURPOSGREENTEXT(5,  10, "Your Coffee is ready! Remove cup.                                   ");
	}
	else{
		PreparationError();
	}

	return (goodQuality);
}

void Coffeemaker::removeCup (){
	if (mStatus == sBrewing){
		//Preheat water tank to Tanktemperature
		mBrewingsystemHandle->heatupWatertank(TANKTEMPERATURE);

		// Change of state after sReady
		mStatus = sReady;
		CURPOSGREENTEXT(4,  10, sstext[sReady]);
		CURPOSGREENTEXT(5,  10, DEFAULTMESSAGE);
	}
}

void Coffeemaker::Ready (){
	if ((mStatus == sDescaling)|| (mStatus == sError)){
		// Change of state after sReady
		mStatus = sReady;
		CURPOSGREENTEXT(4,  10, sstext[sReady]);
		CURPOSGREENTEXT(5,  10, DEFAULTMESSAGE);
	}
}

void Coffeemaker::CleaningError (){
	if (mStatus == sDescaling){
		// Change of state after sError
		mStatus = sError;
		CURPOSGREENTEXT(4,  10, sstext[sError]);
		CURPOSGREENTEXT(5,  10, "Error during cleaning! Please contact service team.                   ");
	}
}

void Coffeemaker::PreparationError (){
	if (mStatus == sBrewing){
		// Change of state after sError
		mStatus = sError;
		CURPOSGREENTEXT(4,  10, sstext[sError]);
		CURPOSGREENTEXT(5,  10, "Error during preparation! Please contact service team.                ");
	}
}


bool Coffeemaker::descale (){
	struct timespec descaleDuration = {DESCALE_DURATION_S,0};
	struct timespec rmD; //remaining duration

	bool ok = false;
	if (mStatus != sReady){
		return (ok); // Descaling only possible at sReady.
	}

	// Change of state after sDescaling
	mStatus = sDescaling;
	CURPOSGREENTEXT(4,  10, sstext[sDescaling]);
	CURPOSGREENTEXT(5,  10, "please wait until coffeemachine has finished descaling.                ");

	// Descaling in process
	nanosleep(&descaleDuration, &rmD);
	ok = true;

	if (ok==true){
		CURPOSGREENTEXT(5,  10, "Descaling finished.                                                 ");
		mStatus = sReady;
		CURPOSGREENTEXT(4,  10, sstext[sReady]);
		CURPOSGREENTEXT(5,  10, DEFAULTMESSAGE);
	}
	else{
		CleaningError();
	}

	return (ok);
}

void Coffeemaker::Screen(void){
    CLS;
	CURPOSTEXT(1,      1, "Coffeemachine - (c) 2024-04 F07");
	CURPOSTEXT(2,      1, "-----------------------------------------------------------------------------");
	CURPOSGREENTEXT(4, 1, "Status : Ready                                                               ");
	CURPOSGREENTEXT(5, 1, "Note   : Please select                                                       ");
	CURPOSGREENTEXT(6, 1, "Setting: Cup Size: REGULAR,  Strength: MEDIUM                                ");
	//X                    1234567890          1234567890          1234567890          1234567890
	//X                              1234567890          1234567890          1234567890          1234567
	CURPOSTEXT(8,      1, "-----------------------------------------------------------------------------");
	CURPOSTEXT(10,     1, "Select Cup Size:     tiny (t), regular (r),  large (l)                       ");
	CURPOSTEXT(11,     1, "Select Strength: delicate (d), medium  (m), strong (s)                       ");
	CURPOSTEXT(12,     1, "Produce coffee            (p)");
	CURPOSTEXT(13,     1, "Cup removed               (c)");
	CURPOSTEXT(14,     1, "Descale                   (a)");
	CURPOSTEXT(15,     1, "Exit programm             (x)");
	CURPOSTEXT(17,     1, "Your Choice               < >");
	CURPOSTEXT(19,     1, "-----------------------------------------------------------------------------");
}

void Coffeemaker::run (){
	bool drinkable;
	char theCommand =' ';
	sCupsize vc = regularCup;
	sStrength vs = sMedium;
	char vctext[][8]={"TINY   ",  "REGULAR", "LARGE  "};
	char vstext[][9]={"DELICATE", "MEDIUM  ","STRONG  "};
	char chosenkeyclear[2] = " ";
	
	Screen();
	
	do{
		CURPOS(17, 28);
		theCommand = getch();
		switch (theCommand){
			case 't': {
				vc = smallCup;
				CURPOSGREENTEXT(6,  20, vctext[smallCup]); CURPOS(6, 1);
				CURPOSGREENTEXT(17, 28, chosenkeyclear);
				break;
			}
			case 'r': {
				vc = regularCup;
				CURPOSGREENTEXT(6,  20, vctext[regularCup]); CURPOS(6, 1);
				CURPOSGREENTEXT(17, 28, chosenkeyclear);
				break;
			}
			case 'l': {
				vc = largeCup;
				CURPOSGREENTEXT(6,  20, vctext[largeCup]); CURPOS(6, 1);
				CURPOSGREENTEXT(17, 28, chosenkeyclear);
				break;
			}
			case 'd': {
				vs = sDelicate;
				CURPOSGREENTEXT(6,  40, vstext[sDelicate]); CURPOS(6, 1);
				CURPOSGREENTEXT(17, 28, chosenkeyclear);
				break;
			}
			case 'm': {
				vs = sMedium;
				CURPOSGREENTEXT(6,  40, vstext[sMedium]); CURPOS(6, 1);
				CURPOSGREENTEXT(17, 28, chosenkeyclear);
				break;
			}
			case 's': {
				vs = sStrong;
				CURPOSGREENTEXT(6,  40, vstext[sStrong]); CURPOS(6, 1);
				CURPOSGREENTEXT(17, 28, chosenkeyclear);
				break;
			}
			case 'p': {
				CURPOSTEXT(12, 32, "            ");
				CURPOSGREENTEXT(17, 28, chosenkeyclear);
				drinkable = brewCup(vs, vc);
				break;
			}
			case 'c': {
				CURPOSGREENTEXT(17, 28, chosenkeyclear);
				removeCup();
				break;
			}
			case 'a': {
				CURPOSGREENTEXT(17, 28, chosenkeyclear);
				descale();
				break;
			}
			case 'y': {
				CURPOSGREENTEXT(17, 28, chosenkeyclear);
				Ready();
				break;
			}
		}

		
		} while(theCommand != 'x');
	CURPOS(20,1);
}

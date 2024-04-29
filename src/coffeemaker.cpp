
//..begin "File Description"
/*--------------------------------------------------------------------------------*
   Filename   : Coffeemaker.cpp
   Description: 
 *--------------------------------------------------------------------------------*/
//..end "File Description"

#include "coffeemaker.h"
#include "stdafx.h"
#include <fstream>
#include <nlohmann/json.hpp>

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
    vessels[leftVessel] = vessels[rightVessel] = NULL;
	mStatus = sReady;
	CURPOSTEXT(4,  10, sstext[sReady]);
}

Coffeemaker::~Coffeemaker(void){
}

bool Coffeemaker::brewCup (sStrength aType, sCupsize bType, sVessel cType) {
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

    // Error when coffe in vessel is to low
	if(vessels[cType]->getWeightG() < Options.gCoffeegrounds + EPSREL * Options.gCoffeegrounds) {
		CURPOSGREENTEXT(5,  10, "Error during preparation! Please contact service team for refill.     ");
		goodQuality = false;
	}

	// Grind coffee beans according to selected cup size and coffee strength
	ActualCoffeegrounds = mGrinderHandle->grindCoffeebeans(Options.gCoffeegrounds);
	nanosleep(&productionDuration, &rmD);
	if (abs(ActualCoffeegrounds-Options.gCoffeegrounds)>(EPSREL * Options.gCoffeegrounds)){
		goodQuality = false;
	}

    // Reduce the weight in the vessel 
	vessels[cType]->setWeightG(vessels[cType]->getWeightG() - ActualCoffeegrounds);

	// Pour in coffee grounds
	mGrinderHandle->fillBrewingfilter();
	nanosleep(&productionDuration, &rmD);

	// Boil up water
	ActualTemperature = mBrewingsystemHandle->mHeaterHandle->heatupWatertank(SETTEMPERATURE);
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

bool Coffeemaker::weighCoffee(sVessel vessel, int targetWeightG)
{
    if (vessels[vessel] == NULL) return false; // error: no storage vessel at this index
    if (vessels[vessel]->getIsOpen()) return false; // error: storage vessel is open
    
    // Actually implement the weighing process by communicating with the coffee maker's scale
    vessels[vessel]->setWeightG(targetWeightG);

    // Check if the vessel is full
    if (targetWeightG >= MAXWEIGHT) vessels[vessel]->setIsFull(true);
    else vessels[vessel]->setIsFull(false);

    return true; // no errors expected
}

storageVessel* Coffeemaker::changeVessel()
{
    float weightG;
    sCoffeeSort sort;

    std::ifstream ifs(VESSEL_FILE);
    nlohmann::json j;
    ifs >> j;

    weightG = j.value("weightG", MAXWEIGHT);
    sort = j.value("sort", sCoffeeSort::Arabica);

    return new storageVessel(weightG, sort);
}

bool Coffeemaker::refillVessel(sVessel vessel, int targetWeightG)
{
    if (vessels[vessel] == NULL) return false; // error: no storage vessel at this index
    
    // limit the target weight to the maximum weight
    if (targetWeightG > MAXWEIGHT) targetWeightG = MAXWEIGHT;

    // open lid
    vessels[vessel]->openLid();

    // dummy to simulate the refill process
    vessels[vessel]->setWeightG(targetWeightG);

    // Weigh the coffee beans
    weighCoffee(vessel, targetWeightG);

    // Check if the vessel is full
    if (targetWeightG >= MAXWEIGHT) vessels[vessel]->setIsFull(true);
    else vessels[vessel]->setIsFull(false);

    // close lid
    vessels[vessel]->closeLid();

    return true; // no errors expected
}

void Coffeemaker::removeCup (){
	if (mStatus == sBrewing){
		//Preheat water tank to Tanktemperature
		mBrewingsystemHandle->mHeaterHandle->heatupWatertank(TANKTEMPERATURE);

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
	CURPOSTEXT(1,      1, "Coffeemachine - (c) 2024 F07");
	CURPOSTEXT(2,      1, "-----------------------------------------------------------------------------");
	CURPOSGREENTEXT(4, 1, "Status : Ready                                                               ");
	CURPOSGREENTEXT(5, 1, "Note   : Please select                                                       ");
	CURPOSGREENTEXT(6, 1, "Setting: Cup Size: REGULAR,  Strength: MEDIUM,  Vessel: LEFT                 ");
	CURPOSGREENTEXT(7, 1, "Your selected Coffeesort is EMPTY                                            ");
	//X                    1234567890          1234567890          1234567890          1234567890
	//X                              1234567890          1234567890          1234567890          1234567
	CURPOSTEXT(9,      1, "-----------------------------------------------------------------------------");
	CURPOSTEXT(11,     1, "Select Cup Size:     tiny (t), regular (r),  large (l)                       ");
	CURPOSTEXT(12,     1, "Select Strength: delicate (d), medium  (m), strong (s)                       ");
    CURPOSTEXT(13,     1, "Select Vessel:       left (L),   right (R)                                   ");
	CURPOSTEXT(14,     1, "Produce coffee            (p)");
	CURPOSTEXT(15,     1, "Cup removed               (c)");
	CURPOSTEXT(16,     1, "Descale                   (a)");
	CURPOSTEXT(17,     1, "Exit programm             (x)");
	CURPOSTEXT(18,	   1, "Service Mode              (S)");
	CURPOSTEXT(20,     1, "Your Choice               < >");
	CURPOSTEXT(21,     1, "-----------------------------------------------------------------------------");
}

void Coffeemaker::ServiceScreen(void) 
{
    CLS;
    CURPOSTEXT(1,      1, "Coffeemachine - Service Mode - (c) 2024 F07");
    CURPOSTEXT(2,      1, "-----------------------------------------------------------------------------");
    CURPOSGREENTEXT(4, 1, "Status : Ready                                                               ");
    CURPOSGREENTEXT(5, 1, "Note   : Please select                                                       ");
	CURPOSGREENTEXT(6, 1, "Setting: Cup Size: N/A,      Strength: N/A,     Vessel: LEFT                 ");
    CURPOSGREENTEXT(7, 1, "Your selected Coffeesort is EMPTY                                            ");
	//X                    1234567890          1234567890          1234567890          1234567890
	//X                              1234567890          1234567890          1234567890          1234567
    CURPOSTEXT(9,      1, "-----------------------------------------------------------------------------");
    CURPOSTEXT(11,     1, "Select Vessel:       left (L),   right (R)                                   ");
    CURPOSTEXT(12,     1, "Clean machine             (c)");
    CURPOSTEXT(13,     1, "Change vessel             (v)");
    CURPOSTEXT(14,     1, "Refill vessel             (r)");
    CURPOSTEXT(15,     1, "Exit Service Mode         (x)");
    CURPOSTEXT(17,     1, "Your Choice               < >");
    CURPOSTEXT(19,     1, "-----------------------------------------------------------------------------");
}

void Coffeemaker::handleServiceScreen(sVessel vessel) {
    char serviceCommand = ' ';
    sVessel vv = leftVessel;
    const char vvtext[][6]={"LEFT ", "RIGHT"};
    const char vcstext[][12] = { // coffee sort names
        "Arabica    ",
        "Robusta    ",
        "Liberica   ",
        "Excelsa    ",
        "Bourbon    ",
        "Typica     ",
        "Caturra    ",
        "Catimor    ",
        "Gesha      ", 
        "Pacamara   "
    };
	char chosenkeyclear[2] = " ";

    ServiceScreen();

    do {
        CURPOS(17, 28);
        serviceCommand = getch();
        switch (serviceCommand) {
            case 'L': {
                vv = leftVessel;
                CURPOSGREENTEXT(6,  57, vvtext[leftVessel]); CURPOS(6, 1);
                if(vessels[vv] != NULL) {
                    CURPOSGREENTEXT(7, 29, vcstext[vessels[vv]->getSort()]); 
                } else {
                    CURPOSGREENTEXT(7, 29, "EMPTY      ");
                }
                CURPOS(6, 1);
                CURPOSGREENTEXT(20, 28, chosenkeyclear);
                break;
            }
            case 'R': {
                vv = rightVessel;
                CURPOSGREENTEXT(6, 57, vvtext[rightVessel]); CURPOS(6, 1);
                if(vessels[vv] != NULL) {
                    CURPOSGREENTEXT(7, 29, vcstext[vessels[vv]->getSort()]); 
                } else {
                    CURPOSGREENTEXT(7, 29, "EMPTY      ");
                }
                CURPOS(6, 1);
                CURPOSGREENTEXT(20, 28, chosenkeyclear);
                break;
            }
            case 'c': {
                // Call the function that cleans the machine
                //cleanMachine();
		        CURPOSGREENTEXT(5,  10, "Machine has been cleaned.                       ");
                break;
            }
            case 'v': {
                // Call the function that changes the vessel
                vessels[vv] = changeVessel();
                if(vessels[vv] != NULL) {
                    CURPOSGREENTEXT(7, 29, vcstext[vessels[vv]->getSort()]); 
                } else {
                    CURPOSGREENTEXT(7, 29, "EMPTY      ");
                }
                CURPOS(6, 1);
                CURPOSGREENTEXT(20, 28, chosenkeyclear);
                break;
            }
            case 'r': {
                // Call the function that refills the vessel
	            if (!refillVessel(vv, MAXWEIGHT)) {
	            	mStatus = sError;
	            	CURPOSGREENTEXT(4,  10, sstext[sError]);
	            	CURPOSGREENTEXT(5,  10, "Error! No Vessel in selected slot.                ");
	            } else {
		            CURPOSGREENTEXT(5,  10, "Vessel has been refilled.                   ");
                }
                break;
            }
            default: break;
        }
    } while(serviceCommand != 'x');

    // Once exiting the service screen, call original screen
    Screen();
}

void Coffeemaker::run (){
	bool drinkable;
	char theCommand =' ';
	sCupsize vc = regularCup;
	sStrength vs = sMedium;
    sVessel vv = leftVessel;
	const char vctext[][8]={"TINY   ",  "REGULAR", "LARGE  "};
	const char vstext[][9]={"DELICATE", "MEDIUM  ","STRONG  "};
    const char vvtext[][6]={"LEFT ", "RIGHT"};
    const char vcstext[][12] = { // coffee sort names
        "Arabica    ",
        "Robusta    ",
        "Liberica   ",
        "Excelsa    ",
        "Bourbon    ",
        "Typica     ",
        "Caturra    ",
        "Catimor    ",
        "Gesha      ", 
        "Pacamara   "
    };
	char chosenkeyclear[2] = " ";
	
	Screen();
	
	do{
		CURPOS(20, 28);
		theCommand = getch();
		switch (theCommand){
			case 't': {
				vc = smallCup;
				CURPOSGREENTEXT(6,  20, vctext[smallCup]); CURPOS(6, 1);
				CURPOSGREENTEXT(20, 28, chosenkeyclear);
				break;
			}
			case 'r': {
				vc = regularCup;
				CURPOSGREENTEXT(6,  20, vctext[regularCup]); CURPOS(6, 1);
				CURPOSGREENTEXT(20, 28, chosenkeyclear);
				break;
			}
			case 'l': {
				vc = largeCup;
				CURPOSGREENTEXT(6,  20, vctext[largeCup]); CURPOS(6, 1);
				CURPOSGREENTEXT(20, 28, chosenkeyclear);
				break;
			}
			case 'd': {
				vs = sDelicate;
				CURPOSGREENTEXT(6,  40, vstext[sDelicate]); CURPOS(6, 1);
				CURPOSGREENTEXT(20, 28, chosenkeyclear);
				break;
			}
			case 'm': {
				vs = sMedium;
				CURPOSGREENTEXT(6,  40, vstext[sMedium]); CURPOS(6, 1);
				CURPOSGREENTEXT(20, 28, chosenkeyclear);
				break;
			}
			case 's': {
				vs = sStrong;
				CURPOSGREENTEXT(6,  40, vstext[sStrong]); CURPOS(6, 1);
				CURPOSGREENTEXT(20, 28, chosenkeyclear);
				break;
			}
			case 'p': {
				CURPOSTEXT(12, 32, "            ");
				CURPOSGREENTEXT(20, 28, chosenkeyclear);
                if(vessels[vv] != NULL) {
				    drinkable = brewCup(vs, vc, vv);
                } else {
		            CURPOSGREENTEXT(5,  10, "Slot is empty.                                 ");
                }
				break;
			}
			case 'c': {
				CURPOSGREENTEXT(20, 28, chosenkeyclear);
				removeCup();
				break;
			}
			case 'a': {
				CURPOSGREENTEXT(20, 28, chosenkeyclear);
				descale();
				break;
			}
			case 'y': {
				CURPOSGREENTEXT(20, 28, chosenkeyclear);
				Ready();
				break;
			}
            case 'L': {
                vv = leftVessel;
                CURPOSGREENTEXT(6,  57, vvtext[leftVessel]); CURPOS(6, 1);
                if(vessels[vv] != NULL) {
                    CURPOSGREENTEXT(7, 29, vcstext[vessels[vv]->getSort()]); 
                } else {
                    CURPOSGREENTEXT(7, 29, "EMPTY      ");
                }
                CURPOS(6, 1);
                CURPOSGREENTEXT(20, 28, chosenkeyclear);
                break;
            }
            case 'R': {
                vv = rightVessel;
                CURPOSGREENTEXT(6, 57, vvtext[rightVessel]); CURPOS(6, 1);
                if(vessels[vv] != NULL) {
                    CURPOSGREENTEXT(7, 29, vcstext[vessels[vv]->getSort()]); 
                } else {
                    CURPOSGREENTEXT(7, 29, "EMPTY      ");
                }
                CURPOS(6, 1);
                CURPOSGREENTEXT(20, 28, chosenkeyclear);
                break;
            }
			case 'S': {
                handleServiceScreen(vv);
                CURPOSGREENTEXT(20, 28, chosenkeyclear);
                break;

                vessels[vv] = changeVessel();
                if(vessels[vv] != NULL) {
                    CURPOSGREENTEXT(7, 29, vcstext[vessels[vv]->getSort()]); 
                } else {
                    CURPOSGREENTEXT(7, 29, "EMPTY      ");
                }
                CURPOS(6, 1);
                CURPOSGREENTEXT(20, 28, chosenkeyclear);

			}
        }
	} while(theCommand != 'x');
	CURPOS(20,1);
}

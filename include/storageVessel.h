
//..begin "File Description"
/*--------------------------------------------------------------------------------*
   Filename   : storageVessel.h
   Description: 
 *--------------------------------------------------------------------------------*/
//..end "File Description"


//..begin "Ifdef"
#ifndef _STORAGEVESSEL_H
#define _STORAGEVESSEL_H
//..end "Ifdef"

//..begin "pragma"
#pragma once
//..end "pragma"

#include <string>

using namespace std;

#define MAXWEIGHT 1000 // maximum weight of coffee beans in gram

// list of coffee sorts
typedef enum {
    Arabica=0,
    Robusta,
    Liberica,
    Excelsa,
    Bourbon,
    Typica,
    Caturra,
    Catimor,
    Gesha,
    Pacamara
} sCoffeeSort;

class storageVessel
{
    public:
        bool openLid();
        bool closeLid();
    	storageVessel(float weightG, sCoffeeSort sort);
        ~storageVessel(void);

        bool getIsFull();
        void setIsFull(bool isFull);
        bool getIsOpen();
        sCoffeeSort getSort();
        void setSort(sCoffeeSort sort);
        float getWeightG();
        void setWeightG(float weightG);

    private:
    	float weightG; // weight of coffee beans in gram
    	sCoffeeSort sort; // "name" of coffee sort
        bool isFull; // true if storage vessel is full
        bool isOpen; // true if storage vessel is open
};

//..begin "Endif"
#endif // _STORAGEVESSEL_H
// ..end "Endif"

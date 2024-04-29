
//..begin "File Description"
/*--------------------------------------------------------------------------------*
   Filename   : storageVessel.cpp
   Description: 
 *--------------------------------------------------------------------------------*/
//..end "File Description"

#include "stdafx.h"
#include "storageVessel.h"

storageVessel::storageVessel()
{
    this->weightG = 0;
    this->sort = sCoffeeSort::Arabica;
    this->isFull = (weightG == MAXWEIGHT) ? true : false;
    this->isOpen = false;
}

storageVessel::storageVessel(float weightG, sCoffeeSort sort)
{
    if (weightG < 0) weightG = 0;

    this->weightG = (weightG >= MAXWEIGHT) ? MAXWEIGHT : weightG;
    this->sort = (sort < 0 || sort >= NUMSORTS) ? sCoffeeSort::Arabica : sort;
    this->isFull = (weightG == MAXWEIGHT) ? true : false;
    this->isOpen = false;
}

storageVessel::~storageVessel() {}

bool storageVessel::openLid()
{
    if (isOpen) return false;

    isOpen = true;
    return true;
}

bool storageVessel::closeLid()
{
    if (!isOpen) return false;

    isOpen = false;
    return true;
}

bool storageVessel::getIsFull() { return isFull; }
void storageVessel::setIsFull(bool isFull) { this->isFull = isFull; }
bool storageVessel::getIsOpen() { return isOpen; }
sCoffeeSort storageVessel::getSort() { return sort; }
void storageVessel::setSort(sCoffeeSort sort) { this->sort = sort; }
float storageVessel::getWeightG() { return weightG; }
void storageVessel::setWeightG(float weightG) { this->weightG = weightG; }

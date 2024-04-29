#ifndef STORAGEVESSEL_H
#define STORAGEVESSEL_H

#include "coffeeSort.h"

class coffeeSort;

class storageVessel {

private:
	coffeeSort* sort;
	float containedCoffee;

public:
	storageVessel(void);
	void changeStorage();

	float weightCoffee();

	void addCoffeebeans();

	/**
	 * bool so that an error can be detected when the storage contains not enough coffeebeans
	 */
	bool useCoffeebeans();
};

#endif

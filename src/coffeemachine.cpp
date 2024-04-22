//Coffeemachine.cpp : Defines point of access to the console application.
//

#include "stdafx.h"


//int main(int argc, char* argv[]){
int main(void){
	
	Coffeemaker* theCoffeemaker;

	theCoffeemaker = new Coffeemaker;
	theCoffeemaker->run();
	
	return 0;
}


// stdafx.h : Include file for standard system include files,
// or project related include files, which are used very often,
//but changed irregularly

#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define UNIX
#ifdef WINDOWS
	#define _CRT_SECURE_NO_WARNINGS
#endif

#include "console.h"
#include "coffeemaker.h"
#include "brewingsystem.h"
#include "grinder.h"

// global variables


// TODO: Reference to additional header required by you programm
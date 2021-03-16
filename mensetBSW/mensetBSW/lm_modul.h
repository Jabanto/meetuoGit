#pragma once

#ifdef LIBRARYEXPORTS
#	define LIBRARY_API __declspec(dllexport)
#else
#	define LIBRARY_API __declspec(dllimport)
#endif

#include "CallConvention.h"
#include "lm_modul.h"
#include "lm_emun_test.h"
#include "Structures.h"

int  LM_function(int lmValue);

bool TAPP_function(subStruct *substrc, int *adresse);


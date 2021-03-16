#pragma once
#define RANGEOFSUBSTRUCT 3


typedef struct subStruct3 {

	int actTuId = 77;

};

typedef struct subStruct2 {

	subStruct3 subsStruct3[RANGEOFSUBSTRUCT];

};

typedef struct subStruct {

	int subStructValue = 7;
	subStruct2 substruct2;
};

typedef struct structDefined {

	int structID = 1;
	int structValue = 2;
	char structName[50] = "Default Struct Name";
	subStruct *subStruct1;

};



class Structures
{
public:
	Structures();
	~Structures();
};


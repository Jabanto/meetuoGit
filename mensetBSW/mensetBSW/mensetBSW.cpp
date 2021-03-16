// mensetBSW.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "tappapiniversal.h"
#include "tapp_tele.h"
#include <iostream>
#include <limits>

using namespace std;

typedef SBI_char_t MFC_id_t[12];

int SBICXXAPI main(void) {

	SBI_int32_t swValue = 0;
	SBI_char_t io_raw[32]="Begin";
	MFC_id_t segId = "-";
	SBI_int32_t intCnt = 5;
	SBI_int32_t segCapacity = 7;
	SBI_bool_t boolFunction = FALSE;
	SBI_bool_t conditionS = FALSE;

	switch (swValue)
	{
		
	case 0:

		cout << "Test Case00" << endl;
		conditionS = !boolFunction;

		if (conditionS)
		{
			cout << "Bool function hat ein wert von: " << boolFunction << endl;
			cout << "conditionS hat en wert von: " << conditionS << endl;
				
		}

	case 1:
		
		// String wird gefüllt , dann 11 backspaces , dann Int mit 2 backspaces and nochmal
		sprintf_s(io_raw,"%s>%-11s:%2d|%2d", io_raw, segId, intCnt, segCapacity);
		cout << io_raw << endl;

	case 2:
		cout << "Test Case02" << endl;
	default:

		cout << "Test default" << endl;

	break;
	}

	TAPP_msg_u_t		msgu;
	
	msgu.header.hdQuelle[0] = 'M';
	msgu.header.hdQuelle[1] = 'F';

	strncpy_s(msgu.sps, "01MF3A029988@@@@O_01__P605800000000_", SPS_MSG_LEN);

	strncpy_s(msgu.header.hdZiel, "5",2);


	cout << "Header Quelle " << msgu.header.hdQuelle;
	
	
	TAPPapUniversalp(&msgu);

	return 0;
}

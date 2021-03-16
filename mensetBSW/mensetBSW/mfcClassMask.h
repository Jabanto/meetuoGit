#pragma once

typedef long MYtype_int32;
typedef unsigned char My_byte_def;
const MYtype_int32 MFC_myConstant = 10;


class MFCClassMask
{

private:

		MYtype_int32 my_InterValue;
		My_byte_def my_Byte_Array[MFC_myConstant];
		void copyClassToClass(const MFCClassMask &x);

public:

		MFCClassMask(const MFCClassMask &x);
		MFCClassMask(MYtype_int32 x);

		void resetAll(void);
		void converToBits(MYtype_int32 x); //TypeCast
		
		MFCClassMask();

		//~mfcClassMask();			//Destructor
};

/*###############################################################################*/
/*----------------------- private inline Functions -------------------------*/
/*###############################################################################*/

inline void MFCClassMask::copyClassToClass(const MFCClassMask &x) {

	for (MYtype_int32 i = 0; i < MFC_myConstant; i++)
	{
		my_Byte_Array[i] = x.my_Byte_Array[i];
	}

}


inline void MFCClassMask::converToBits(MYtype_int32 x) {

	MYtype_int32 temp = x;

	resetAll();

	for (int i = 0; i < 32; i++)
	{
		if (temp & (1L << i))
		{
			temp &= ~(1L << i);
			my_Byte_Array[(i / 8)] |= (1 << (i % 8));
		}

	}

}




/*###############################################################################*/
/*----------------------- public inline Functions -------------------------*/
/*###############################################################################*/

inline void MFCClassMask::resetAll(void) {
	int resetValue = MFC_myConstant;
}

//*-------------*

inline MFCClassMask::MFCClassMask(const MFCClassMask &x) {

	copyClassToClass(x);
}

inline MFCClassMask::MFCClassMask(MYtype_int32 x) {

	if (x >= (8 * MFC_myConstant))
	{
		x = (8 * MFC_myConstant) - 1; //Bits werden von o gezaehlt
	}

	resetAll();
	my_Byte_Array[(x / 8)] = (1 << (x % 8));
}






#pragma 

/*-----------------------------------------------------------------------------
 * $Header: /abl/source/mfc/mfc/src/mfc_classes.h 17    24.08.17 10:57 Pschneider $
 *
 * File        : $Archive: /abl/source/mfc/mfc/src/mfc_classes.h $
 *
 * Copyright   : WITRON Logistik + Informatik GmbH
 *
 * Project     : MFC
 *
 * Description : Baseclasses for all MFC-Projects
 *
 * Version     : $Revision: 17 $
 *
 * Authors     : Herbert Fuellmeier
 *
 * Last change : $Modtime: 24.08.17 10:57 $ by $Author: Pschneider $
 *
 * Change History :
 *    30-Mar-1999 FUE   first version
 *
 *---------------------------------------------------------------------------*/

 /** @file */
 /**
  * \addtogroup     MFC
  * @{
  * \addtogroup     MFC_Interface
  * @{
  */

#ifndef __MFC_CLASSES_H    
#define __MFC_CLASSES_H    


#if !defined(IDL_COMPILER)
#include "sbi_if.h"
#else
#endif /* IDL_COMPILER */


#ifndef SBI_VMS
#include <crtdbg.h>
#else
#include <assert.h>
#endif


#if defined(__cplusplus)
extern "C" {
#endif


	/*###############################################################################*/
	/*----------------------------- MFC - UpdMask-Klasse ----------------------------*/
	/*###############################################################################*
	 *
	 * Authors:     Herbert Fuellmeier
	 *
	 * Description:
	 *              64bit Datentyp zur definition von Selektionsmasken (Bit 0 bis 63)
	 *
	 * Version:     1.0
	 *
	 * Change History:
	 *
	 *    30-03-1999 FUE   first version
	 *
	 * Anwendungsbeispiele:
	 *      const MFC_updMask_t DEFINE_1= 4  //Bit 4 (5.Bit) wird gesetzt
	 *      const MFC_updMask_t DEFINE_2= 6  //Bit 6 wird gesetzt
	 *
	 *            MFC_updMask_t updMask = DEFINE_2 | DEFINE_1
	 *                                              //Bit 4 und 6 werden gesetzt
	 *
	 *            MFC_RESET (updMask, DEFINE_1)     //Bit 4 wird zurueckgesetzt
	 *
	 *-------------------------------------------------------------------------------*/

const SBI_int32_t MFC_updMaskMaxBytes = 10; 

class SBIDLLAPI MFC_updMask_t {
private:
	SBI_uint8_t m_byte[MFC_updMaskMaxBytes];          //array von 10 Bytes == 80 Bit
	void convIntToClass(SBI_int32_t x);
	void copyClassToClass(const MFC_updMask_t &x);

public:
	SBIAPI  MFC_updMask_t();                        //Konstruktor
	SBIAPI  MFC_updMask_t(const MFC_updMask_t &x);  //Copy-Konstruktor
	SBIAPI  MFC_updMask_t(SBI_int32_t x);           //TypeCast
	//SBIAPI ~MFC_updMask_t() ;                       //Destruktor

	void SBIAPI resetAll(void);                      //alle Bits zuruecksetzen
	void SBIAPI convToBits(SBI_int32_t x);
	SBI_bool_t SBIAPI getNextBit(SBI_int32_t &actBit);//naechstes Bit nach actBit

	MFC_updMask_t  operator  | (const MFC_updMask_t &x) const;
	MFC_updMask_t  operator  & (const MFC_updMask_t &x) const;
	SBI_bool_t     operator == (const MFC_updMask_t &x);
	SBI_bool_t     operator != (const MFC_updMask_t &x);
	MFC_updMask_t &operator  ~ ();
	MFC_updMask_t &operator &= (const MFC_updMask_t &x);
	MFC_updMask_t &operator |= (const MFC_updMask_t &x);
	MFC_updMask_t &operator  = (const MFC_updMask_t &x);
	MFC_updMask_t &operator  = (SBI_int32_t x);
	MFC_updMask_t  operator  ^ (const MFC_updMask_t &x) const;
};


/*###############################################################################*/
/*------------------------ private inline Funktionen ----------------------------*/
/*###############################################################################*/

/*----------------------------- copyClassToClass --------------------------------
 *
 * Kopiert den Inhalt der Memebervariable m_byte[] von einer Klasse zur anderen
 *
 *-------------------------------------------------------------------------------*/
inline void MFC_updMask_t::copyClassToClass(const MFC_updMask_t &x) {
	for (SBI_int32_t i = 0; i < MFC_updMaskMaxBytes; i++)
		m_byte[i] = x.m_byte[i];
}

/*------------------------------- convIntToClass --------------------------------
 *
 * Convertiert einen Integer x (x == Bit, das gesetzt werden soll)
 *
 *-------------------------------------------------------------------------------*/
inline void MFC_updMask_t::convIntToClass(SBI_int32_t x) {
	if (x >= (8 * MFC_updMaskMaxBytes)) {
#ifndef SBI_VMS
		_ASSERT(x < 8 * MFC_updMaskMaxBytes);
#else
		assert(x < 8 * MFC_updMaskMaxBytes);
#endif
		x = (8 * MFC_updMaskMaxBytes) - 1;   //Bits werden von 0 gezaehlt
	}
	resetAll();
	m_byte[(x / 8)] = (1 << (x % 8));
}


/*###############################################################################*/
/*----------------------- oeffenliche inline Funktionen -------------------------*/
/*###############################################################################*/

/*----------------------------------- resetAll ----------------------------------
 *
 * Alle Bits der Membervariable werden zurueckgesetzt
 *
 *-------------------------------------------------------------------------------*/
inline void SBIAPI MFC_updMask_t::resetAll(void) {
	for (SBI_int32_t i = 0; i < MFC_updMaskMaxBytes; i++)  m_byte[i] = '\0';
}


/*------------------------------- convToBits -------------------------------------
 *
 * Convertiert einen Integer x in Bits
 *
 *-------------------------------------------------------------------------------*/
inline void SBIAPI MFC_updMask_t::convToBits(SBI_int32_t x) {
	SBI_int32_t temp = x;

	resetAll();
	for (int i = 0; i < 32 && temp != 0; i++) {
		if (temp & (1L << i)) {
			temp &= ~(1L << i);
			m_byte[(i / 8)] |= (1 << (i % 8));
		}
	}
}

/*--------------------------------- Konstruktoren -------------------------------
 *
 * Convertiert einen Integer x (x == Bit, das gesetzt werden soll)
 *
 *-------------------------------------------------------------------------------*/

inline SBIAPI MFC_updMask_t::MFC_updMask_t() {
	resetAll();
}
inline SBIAPI MFC_updMask_t::MFC_updMask_t(const MFC_updMask_t &x) {
	copyClassToClass(x);
}
inline SBIAPI MFC_updMask_t::MFC_updMask_t(SBI_int32_t x) {
	convIntToClass(x);
}

	/*--------------------------- Ende MFC - DynInt-Klasse -------------------------*/

#if defined(__cplusplus)
}
#endif

#endif 
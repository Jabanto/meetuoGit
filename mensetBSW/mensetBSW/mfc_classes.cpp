#include "pch.h"

/*-----------------------------------------------------------------------------
 * $Header: /abl/source/mfc/mfc/src/mfc_classes.cpp 3     14.12.01 11:46 Rgebauer $
 *
 * File        : $Archive: /abl/source/mfc/mfc/src/mfc_classes.cpp $
 *
 * Copyright   : WITRON Logistik + Informatik GmbH
 *
 * Project     : MFC
 *
 * Description : Funktionen fuer MFC-Klassen
 *
 * Version     : $Revision: 3 $
 *
 * Authors     : Herbert Fuellmeier
 *
 * Last change : $Modtime: 14.12.01 10:43 $ by $Author: Rgebauer $
 *
 * Change History :
 *    30-03-1999  FUE    1. Version
 *
 *
 *---------------------------------------------------------------------------*/
#include "mfc_classes.h"


 /*****************************************************************************/
 /* ++
  * Function:    MFC_updMask_t::getNextBit(int &actBit) {
  *
  * Authors:     Herbert Fuellmeier
  * Created:     30-03-1999
  *
  * Description: Ausgehend vom Argument actBit wird in der Uebergabevariable
  *		der Standort des naechsten gesetzten Bits der
  *		aktuellen Instanz zurueckgegeben.
  *
  *		Damit das erste Bit gefunden werden kann, muss actBit auf -1
  *		initialsiert werden.
  *
  * ErrorCode:   kein
  *
  * ReturnCode:	TRUE,  falls gesetztes Bit gefunden
  *		FALSE, falls kein Bit mehr gefunden
  *
  * Change History:
  *    30-03-1999    FUE	  1. Version
  */
  /*****************************************************************************/

SBI_bool_t SBIAPI MFC_updMask_t::getNextBit(SBI_int32_t &io_actBit) {
	io_actBit++;
	if ((io_actBit >= 0) && (io_actBit < 8 * MFC_updMaskMaxBytes)) {
		for (SBI_int32_t i = io_actBit / 8; i < MFC_updMaskMaxBytes; i++) {
			for (SBI_int32_t k = io_actBit % 8; k < 8; k++) {
				if (m_byte[i] & (1 << k)) {
					return (TRUE);  //Bit gefunden
				}
				io_actBit++;
			}
		}
	}
	return (FALSE);
}


/*****************************************************************************/
/* ++
 * Function:    MFC_updMask_t::operator |
 *
 * Authors:     Herbert Fuellmeier
 * Created:     30-03-1999
 *
 * Description: Operator | wird fuer Klasse MFC_updMask_t uerberladen
 *
 * ErrorCode:   kein
 *
 * Change History:
 *    30-03-1999    FUE	  1. Version
 */
 /*****************************************************************************/

MFC_updMask_t MFC_updMask_t::operator | (const MFC_updMask_t &x) const {
	MFC_updMask_t od;
	for (SBI_int32_t i = 0; i < MFC_updMaskMaxBytes; i++)
		od.m_byte[i] = m_byte[i] | x.m_byte[i];
	return od;
}

/*****************************************************************************/
/* ++
 * Function:    MFC_updMask_t::operator &
 *
 * Authors:     Herbert Fuellmeier
 * Created:     30-03-1999
 *
 * Description: Operator & wird fuer Klasse MFC_updMask_t uerberladen
 *
 * ErrorCode:   kein
 *
 * Change History:
 *    30-03-1999    FUE	  1. Version
 */
 /*****************************************************************************/

MFC_updMask_t MFC_updMask_t::operator & (const MFC_updMask_t &x) const {
	MFC_updMask_t od;
	for (SBI_int32_t i = 0; i < MFC_updMaskMaxBytes; i++)
		od.m_byte[i] = m_byte[i] & x.m_byte[i];
	return od;
}



/*****************************************************************************/
/* ++
 * Function:    MFC_updMask_t::operator ==
 *
 * Authors:     Herbert Fuellmeier
 * Created:     30-03-1999
 *
 * Description: Operator == wird fuer Klasse MFC_updMask_t uerberladen
 *
 * ErrorCode:   kein
 *
 * Change History:
 *    30-03-1999    FUE	  1. Version
 */
 /*****************************************************************************/

SBI_bool_t MFC_updMask_t::operator == (const MFC_updMask_t &x) {

	SBI_bool_t ret = TRUE;
	for (SBI_int32_t i = 0; i < MFC_updMaskMaxBytes; i++)
	{
		if ((m_byte[i]) != (x.m_byte[i]))
		{
			ret = FALSE;
			break;
		}
	}
	return ret;
}

/*****************************************************************************/
/* ++
 * Function:    MFC_updMask_t::operator !=
 *
 * Authors:     Herbert Fuellmeier
 * Created:     30-03-1999
 *
 * Description: Operator != wird fuer Klasse MFC_updMask_t uerberladen
 *
 * ErrorCode:   kein
 *
 * Change History:
 *    30-03-1999    FUE	  1. Version
 */
 /*****************************************************************************/
SBI_bool_t MFC_updMask_t::operator != (const MFC_updMask_t &x) {

	SBI_bool_t ret = FALSE;
	for (SBI_int32_t i = 0; i < MFC_updMaskMaxBytes; i++)
	{
		if ((m_byte[i]) != (x.m_byte[i])) {
			ret = TRUE;
			break;
		}
	}
	return ret;
}


/*****************************************************************************/
/* ++
 * Function:    MFC_updMask_t::operator ~
 *
 * Authors:     Herbert Fuellmeier
 * Created:     30-03-1999
 *
 * Description: Operator ~ wird fuer Klasse MFC_updMask_t uerberladen
 *
 * ErrorCode:   kein
 *
 * Change History:
 *    30-03-1999    FUE	  1. Version
 */
 /*****************************************************************************/

MFC_updMask_t &MFC_updMask_t::operator ~ () {
	for (SBI_int32_t i = 0; i < MFC_updMaskMaxBytes; i++)
		m_byte[i] = ~(m_byte[i]);
	return *this;
}

/*****************************************************************************/
/* ++
 * Function:    MFC_updMask_t::operator &=
 *
 * Authors:     Herbert Fuellmeier
 * Created:     30-03-1999
 *
 * Description: Operator &= wird fuer Klasse MFC_updMask_t uerberladen
 *
 * ErrorCode:   kein
 *
 * Change History:
 *    30-03-1999    FUE	  1. Version
 */
 /*****************************************************************************/

MFC_updMask_t &MFC_updMask_t::operator &= (const MFC_updMask_t &x) {

	for (SBI_int32_t i = 0; i < MFC_updMaskMaxBytes; i++)
	{
		m_byte[i] &= x.m_byte[i];
	}
	return *this;
}


/*****************************************************************************/
/* ++
 * Function:    MFC_updMask_t::operator |=
 *
 * Authors:     Herbert Fuellmeier
 * Created:     30-03-1999
 *
 * Description: Operator |= wird fuer Klasse MFC_updMask_t uerberladen
 *
 * ErrorCode:   kein
 *
 * Change History:
 *    30-03-1999    FUE	  1. Version
 */
 /*****************************************************************************/

MFC_updMask_t &MFC_updMask_t::operator |= (const MFC_updMask_t &x) {

	for (SBI_int32_t i = 0; i < MFC_updMaskMaxBytes; i++)
	{
		m_byte[i] |= x.m_byte[i];
	}
	return *this;
}

/*****************************************************************************/
/* ++
 * Function:    MFC_updMask_t::operator =
 *
 * Authors:     Herbert Fuellmeier
 * Created:     30-03-1999
 *
 * Description: Operator = wird fuer Klasse MFC_updMask_t uerberladen
 *
 * ErrorCode:   kein
 *
 * Change History:
 *    30-03-1999    FUE	  1. Version
 */
 /*****************************************************************************/

MFC_updMask_t &MFC_updMask_t::operator = (const MFC_updMask_t &x) {

	copyClassToClass(x);

	return *this;
}

MFC_updMask_t &MFC_updMask_t::operator = (SBI_int32_t x) {

	convIntToClass(x);
	return *this;
}



/*****************************************************************************/
/* ++
 * Function:    MFC_updMask_t::operator^
 *
 * Authors:     Christopher Höchtl
 * Created:     03-07-2001
 *
 * Description: Operator ^ wird fuer Klasse MFC_updMask_t uerberladen
 *
 * ErrorCode:   kein
 *
 * Change History:
 *    03-07-2001    FUE	  1. Version
 */
 /*****************************************************************************/

	MFC_updMask_t MFC_updMask_t::operator ^ (const MFC_updMask_t &x) const {
	MFC_updMask_t od;
	for (SBI_int32_t i = 0; i < MFC_updMaskMaxBytes; i++)
		od.m_byte[i] = m_byte[i] ^ x.m_byte[i];
	return (od);
}

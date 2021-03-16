#include "pch.h"

/*-----------------------------------------------------------------------------
 * $Header: /abl/source/mfc/mfc/src/mfc_error.cpp 26    3.05.16 6:31 Pschneider $

/*###############################################################################*/
/*----------------------------- MFC - ErrorMask-Klasse -------------------------*/
/*###############################################################################*
 *
 * Authors:     Peter Schneider
 *
 * Description:
 *              Datentyp zum handling von Fehlern einer TU (LVR/MFC/SPS-Fehler)
 *
 * Version:     1.0
 *
 * Change History:
 *
 *    06-12-2000 PS   first version
 *    09-04-2003 RG   getErrorAsString2       ( Thread Safe functions )
 *                    getInspectionAsString2
 *                    getCheckedAsString2
 *                    old functions kept for compatibility
 *
 * Anwendungsbeispiele:
 *            typedef enum {
 *               DEFINE_1 = 4,  //Bit 4 (5.Bit) wird gesetzt
 *               DEFINE_2 = 6   //Bit 6 wird gesetzt
 *            } MFC_tu_error_t;
 *
 *            MFC_error_t  tuError;
 *
 *            MFC_error_t  tuError.set (DEFINE_2 | DEFINE_1)
 *                                              //Bit 4 und 6 werden gesetzt
 *
 *            tuError.reset (tuError, DEFINE_1) //Bit 4 wird zurueckgesetzt
 *
 *-------------------------------------------------------------------------------*/
#include "mfc_error.h"
#include "mfc_if.h"

#define MFC_ERR_SIZE_SPS_MSG           4   /* max. size der Dimensionsfehler */
#define MFC_ERR_OFFSET_SPS_ERR         MFCI_TU_ERR_OVERLEN_F
#define MFC_ERR_END_SPS_ERR            MFCI_TU_ERR_OVERLEN_F -1 + (MFC_ERR_SIZE_SPS_MSG*6)

/*****************************************************************************
* Function:    MFC_error_t::getText
*
* Description : Fehlertext für Fehler - oder Checked - Index zurückgeben
*
/*****************************************************************************/

SBI_char_t * SBIAPI MFC_error_t::getText(SBI_int32_t    i_select,
										 SBI_char_t     i_separator) {

	static MFC_err_text_t		errText[MFC_ERR_TEXT_CNT_MAX];	
	static SBI_int32_t			cntText = 0;
		   SBI_int32_t			errIdx;
		   SBI_bool_t			first = TRUE;
		   SBI_int32_t          lenText = 0;
	/* In Macros für Protokolierung werden mehrer variablen verwendet!*/

		   if (cntText == MFC_ERR_TEXT_CNT_MAX - 1) {
			   cntText = 0;
		   }else
		   {
			   cntText++;
		   }
		   errText[cntText][0] = '\0';
		   for (errIdx = MFC_TU_ERR_IDX_MIN; errIdx <= MFC_TU_ERR_IDX_MAX; errIdx++)
		   {

		   }

		   return(errText[cntText]);
}


/*****************************************************************************
 * Function:    MFC_error_t::isSet
 *
 * Description: Prüft, ob ein bestimmter Fehler gesetzt ist
 *              -> TRUE wenn gesetzt
 *              -> FALSE wenn nicht gesetzt
 *
/*****************************************************************************/
SBI_bool_t SBIAPI MFC_error_t::isSet(SBI_int32_t i_idx) {

	SBI_bool_t    retval = FALSE;

	if (!isInit) {
		this->init();
	}
	if (mfcCheckErrorIdx(i_idx)) {
		if (MFC_CHECK(m_error[i_idx], MFC_TU_ERR_ACTIVE)) {
			retval = TRUE;
		}
	}
	return (retval);
}


/*****************************************************************************
 * Function:    MFC_error_t::setError
 *
 * Description: Setzen eines Fehlers und update checked
 *
/*****************************************************************************/
void SBIAPI MFC_error_t::setError(SBI_int32_t   i_idx) {

	if (!isInit) {
		this->init();
	}
	if (mfcCheckErrorIdx(i_idx)) {
		if (MFC_CHECK(m_error[i_idx], MFC_TU_ERR_ACTIVE) == FALSE) {
			MFC_SET(m_error[i_idx], MFC_TU_ERR_ACTIVE);
			m_errorCnt++;
		}
		if (MFC_CHECK(m_error[i_idx], MFC_TU_ERR_CHECKED) == FALSE) {
			MFC_SET(m_error[i_idx], MFC_TU_ERR_CHECKED);
			m_checkedCnt++;
		}
		MFC_SET(m_error[MFC_TU_ERR_IDX_ALL], MFC_TU_ERR_ACTIVE);
		MFC_SET(m_error[MFC_TU_ERR_IDX_ALL], MFC_TU_ERR_CHECKED);
	}
}

/*****************************************************************************
 * Function:    MFC_error_t::resetError
 *
 * Description: Rücksetzen eines Fehlers
 *
/*****************************************************************************/
void SBIAPI MFC_error_t::resetError(SBI_int32_t   i_idx) {

	if (mfcCheckErrorIdx(i_idx)) {
		if (MFC_CHECK(m_error[i_idx], MFC_TU_ERR_ACTIVE)) {
			MFC_RESET(m_error[i_idx], MFC_TU_ERR_ACTIVE);
			m_errorCnt--;
			if (m_errorCnt < 0) {
				this->init();
			}
			else {
				if (m_errorCnt == 0) {
					MFC_RESET(m_error[MFC_TU_ERR_IDX_ALL], MFC_TU_ERR_ACTIVE);
				}
			}
		}
		if (MFC_CHECK(m_error[i_idx], MFC_TU_ERR_CHECKED) == FALSE) {
			MFC_SET(m_error[i_idx], MFC_TU_ERR_CHECKED);
			m_checkedCnt++;
		}
		MFC_SET(m_error[MFC_TU_ERR_IDX_ALL], MFC_TU_ERR_CHECKED);
	}
}

/*****************************************************************************
 * Function:    MFC_error_t::updError
 *
 * Description: Aktualiziert/Ändern eines Fehlers
 *
/*****************************************************************************/

void SBIAPI MFC_error_t::updError(SBI_int32_t i_idx , SBI_bool_t i_setIt){

	if (!isInit)
	{
		this->init();
	}
	if (i_setIt)
	{
		this->setError(i_idx);
	}
	else
	{
		this->resetError(i_idx);
	}

}

/*****************************************************************************
 * Function:    MFC_error_t::isOk
 *
 * Description: Prüft ob ein Fehler gesetzt ist oder nicht. TRUE wenn Fehler nicht
 *              gesetzt ist (OK)
 *
/*****************************************************************************/

SBI_bool_t SBIAPI MFC_error_t::isOk(SBI_int32_t i_idx) {

	SBI_bool_t retVal;
	if (!isInit)
	{
		this->init();
	}
	if (mfcCheckErrorIdx(i_idx))
	{
		retVal = (MFC_CHECK(m_error[i_idx], MFC_TU_ERR_ACTIVE) == FALSE);
	}

	return retVal;
}

/*****************************************************************************
 * Function:    MFC_error_t::isChecked
 *
 * Description: Prüft, ob ein bestimmter Fehler gecheckt wurde
 *              -> TRUE wenn gecheckt
 *              -> FALSE wenn nicht gecheckt
 *
/*****************************************************************************/

SBI_bool_t SBIAPI MFC_error_t::isChecked(SBI_int32_t i_idx) {

	SBI_bool_t retVal;
	if (!isInit)
	{
		this->init();
	}
	if (mfcCheckErrorIdx(i_idx))
	{
		retVal = (MFC_CHECK(m_error[i_idx], MFC_TU_ERR_CHECKED));
	}
	else
	{
		retVal = FALSE;
	}

	return retVal;
}

/*****************************************************************************
 * Function:    MFC_error_t::resetChecked
 *
 * Description: Zurücksetzen checked-Bit eines Fehlers
 *
/*****************************************************************************/

void SBIAPI MFC_error_t::resetChecked(SBI_int32_t i_idx) {

	if (!isInit)
	{
		this->init();
	}
	if (mfcCheckErrorIdx(i_idx))
	{
		if (MFC_CHECK(m_error[i_idx], MFC_TU_ERR_CHECKED))
		{
			MFC_RESET(m_error[i_idx], MFC_TU_ERR_CHECKED);
			m_checkedCnt--;
		}
		if (m_checkedCnt <=0 )
		{
			m_checkedCnt = 0;
			MFC_RESET(m_error[i_idx], MFC_TU_ERR_CHECKED);
		}
	}
}

/*****************************************************************************
 * Function:    MFC_error_t::setInspection
 *
 * Description: setzen des Flags für Inspection für einen Fehler
 *
/*****************************************************************************/

void SBIAPI MFC_error_t::setInspection(SBI_int32_t i_idx) {

	if (!isInit) {
		this->init();
	}
	if (mfcCheckErrorIdx(i_idx))
	{
		MFC_SET(m_error[i_idx], MFC_TU_ERR_INSPECTION);
	}
}

/*****************************************************************************
 * Function:    MFC_error_t::resetInspection
 *
 * Description: rücksetzen des Flags für Inspection für einen Fehler
 *
/*****************************************************************************/

void SBIAPI MFC_error_t::resetInspection(SBI_int32_t i_idx) {
	
	if (!isInit)
	{
		this->init();
	}
	if (mfcCheckErrorIdx(i_idx))
	{
		MFC_RESET(m_error[i_idx], MFC_TU_ERR_INSPECTION);
	}

}


/*****************************************************************************
 * Function:    MFC_error_t::isForInspection
 *
 * Description: Pruefen, ob ein Fehler geprüft werden muss
 *
/*****************************************************************************/


SBI_bool_t SBIAPI MFC_error_t::isForInspection(SBI_int32_t i_idx) {

	SBI_bool_t retVal;

	if (!isInit)
	{
		this->init();
	}
	if (mfcCheckErrorIdx(i_idx))
	{
		retVal = MFC_CHECK(m_error[i_idx], MFC_TU_ERR_INSPECTION);
	}
	else {
		retVal = FALSE;
	}

	return retVal;
}

/*****************************************************************************
 * Function:    MFC_error_t::sendErrorInfo
/*****************************************************************************/

SBI_bool_t SBIAPI MFC_error_t::sendErrorInfo(MFCI_tu_id_t		i_tuId,
											 SBI_int32_t		i_errorIndex,
											 SBI_bool_t (USER_sndTuError (MFCI_id_t  ituId,
											 SBI_int32_t		i_errorIndex,
											 SBI_bool_t			i_errorValue,
											 SBI_int32_t		*o_error))) {

	SBI_bool_t			retVal = FALSE;
	SBI_int32_t			i, err;

	if (! isInit )
	{
		this->init();
	}
	if (i_errorIndex == MFCI_TU_ERR_SEND_ALL)
	{
		retVal = TRUE;
		for  (i =  MFC_TU_ERR_IDX_MIN; i <= MFC_TU_ERR_IDX_MAX; i++)
		{
			if (USER_sndTuError(i_tuId, i, this->isSet (i), &err)==FALSE)
			{
				retVal = FALSE;
				break;
			}
		}
	}
	else
	{
		if (mfcCheckErrorIdx(i_errorIndex))
		{
			retVal = USER_sndTuError(i_tuId, i_errorIndex, this->isSet(i_errorIndex), &err);
		}
	}
	return retVal;
}

/*****************************************************************************
 * Function:    MFC_error_t::getError
 *
 * Description: Gibt den ersten Fehler zurück, der gesetzt ist
 *              -> TRUE wenn gefunden
 *              -> FALSE wenn kein Fehler gesetzt
 *
/*****************************************************************************/

inline SBI_bool_t SBIAPI MFC_error_t::getError(SBI_int32_t  *o_idx) {

	SBI_int32_t     i;
	SBI_bool_t      fnd = FALSE;

	if (!isInit) {
		this->init();
	}
	if (o_idx != NULL) {
		*o_idx = 0;
	}
	if (MFC_CHECK(m_error[MFC_TU_ERR_IDX_ALL], MFC_TU_ERR_ACTIVE)) {
		for (i = MFC_TU_ERR_IDX_MIN; i <= MFC_TU_ERR_IDX_MAX; i++) {
			if (MFC_CHECK(m_error[i], MFC_TU_ERR_ACTIVE)) {
				if (o_idx != NULL) {
					*o_idx = i;
				}
				fnd = TRUE;
				break;
			}
		}
	}
	return (fnd);
}

/*****************************************************************************
 * Function:    MFC_error_t::getNextError
 *
 * Description: gibt den nächsten Fehler nach dem übergebenen actError zurück
 *              -> TRUE wenn gefunden
 *              -> FALSE wenn kein Fehler mehr gesetzt
 *
/*****************************************************************************/

inline SBI_bool_t SBIAPI MFC_error_t::getNextError(SBI_int32_t  *io_idx) {

	SBI_int32_t			i;
	SBI_int32_t			idx;
	SBI_bool_t			retVal = FALSE;

	if (!isInit) {
		this->init();
	}
	if (MFC_CHECK(m_error[MFC_TU_ERR_IDX_ALL], MFC_TU_ERR_ACTIVE))
	{
		idx = (*io_idx) + 1;
		if (mfcCheckErrorIdx (idx))
		{
			for (i = idx; i <= MFC_TU_ERR_IDX_MAX; i++)
			{
				if (MFC_CHECK(m_error[i], MFC_TU_ERR_ACTIVE))
				{
					*io_idx = i;
					retVal = TRUE;
					break;
				}
			}
		}
	}
	return retVal;
}

/*****************************************************************************
 * Function:    MFC_error_t::getNotChecked
 *
 * Description: gibt den ersten noch nicht gecheckten Fehler zurück
 *              -> TRUE wenn gefunden
 *              -> FALSE wenn kein Fehler mehr gesetzt
 *
/*****************************************************************************/

inline SBI_bool_t SBIAPI MFC_error_t::getNotChecked(SBI_int32_t  *o_idx) {

	SBI_int32_t				i;
	SBI_bool_t				fnd = FALSE;
	if (!isInit) {
		this->init();
	}
	if (o_idx != NULL)
	{
		*o_idx = 0;
	}
	if (MFC_CHECK(m_error[MFC_TU_ERR_IDX_ALL], MFC_TU_ERR_ACTIVE))
	{
		for (i = MFC_TU_ERR_IDX_MIN; i<= MFC_TU_ERR_IDX_MAX ; i++)
		{
			if (MFC_CHECK(m_error[i], MFC_TU_ERR_CHECKED) == FALSE)
			{
				if (o_idx != NULL)
				{
					*o_idx = i;
				}
				fnd = TRUE;
				break;
			}
		}
	}
	return fnd;
}

/*****************************************************************************
 * Function:    MFC_error_t::getNextNotChecked
 *
 * Description: gibt den nächsten noch nicht gecheckten Fehler nach dem
 *              übergebenen io_error zurück
 *              -> TRUE wenn gefunden
 *              -> FALSE wenn kein Fehler mehr gesetzt
 *
/*****************************************************************************/

inline SBI_bool_t SBIAPI MFC_error_t::getNextNotChecked(SBI_int32_t	*io_idx) {

	SBI_int32_t			i;
	SBI_int32_t			idx;
	SBI_bool_t			retVal = FALSE;

	if (!isInit)
	{
		this->init();
	}
	if (MFC_CHECK(m_error[MFC_TU_ERR_IDX_ALL], MFC_TU_ERR_ACTIVE))
	{
		idx = (*io_idx) + 1;
		if (mfcCheckErrorIdx (idx))
		{
			for (i = idx; i <= MFC_TU_ERR_IDX_MAX; i++)
			{
				if (MFC_CHECK(m_error[i], MFC_TU_ERR_CHECKED) == FALSE)
				{
					*io_idx = i;
					retVal = TRUE;
					break;
				}
			}
		}
	}

	return retVal;
}

/*****************************************************************************
 * Function:    MFC_error_t::allCheckedOk
 *
 * Description: Pruefe ob alle bereits gecheckten Fehler ok waren
 *              -> TRUE wenn alle gecheckt und ok oder noch keiner gecheckt wurde
 *              -> FALSE wenn ein gecheckter Fehler nicht ok
 *
/*****************************************************************************/

SBI_bool_t SBIAPI MFC_error_t::allCheckedOk() {

	SBI_int32_t			i;
	SBI_bool_t			retVal = TRUE;

	if ( ! isInit )
	{
		this->init();
	}
	if (MFC_CHECK(m_error[MFC_TU_ERR_IDX_ALL], MFC_TU_ERR_CHECKED))
	{
		for ( i = MFC_TU_ERR_IDX_MIN; i <= MFC_TU_ERR_IDX_MAX; i++)
		{
			if (MFC_CHECK(m_error[i], MFC_TU_ERR_CHECKED))
			{
				if (MFC_CHECK(m_error[i], MFC_TU_ERR_ACTIVE))
				{
					retVal = FALSE;
					break;
				}
			}
		}
	}
	return retVal;
}

/*****************************************************************************
 * Function:    MFC_error_t::getCheckedNotOk
 *
 * Description: Liefert den ersten Fehler der gecheckt wurde und nicht ok war
 *              -> TRUE wenn gecheckter Fehler gefunden wurde der gesetzt ist
 *              -> FALSE wenn nichts gefunden -> alle gecheckten sind ok
 *                       oder nichts gecheckt
 *
/*****************************************************************************/

SBI_bool_t SBIAPI MFC_error_t::getCheckedNotOk(SBI_int32_t *o_idx) {

	SBI_int32_t			i;
	SBI_bool_t			fnd = FALSE;

	if ( ! isInit )
	{
		this->init();
	}
	if (o_idx != NULL)
	{
		*o_idx = 0;
	}
	if (MFC_CHECK(m_error[MFC_TU_ERR_IDX_ALL], MFC_TU_ERR_CHECKED))
	{
		for ( i =  MFC_TU_ERR_IDX_MIN; i < MFC_TU_ERR_IDX_MAX; i++)
		{
			if (MFC_CHECK(m_error[i], MFC_TU_ERR_CHECKED))
			{
				if (MFC_CHECK(m_error[i], MFC_TU_ERR_ACTIVE))
				{
					if (o_idx != NULL)
					{
						*o_idx = i;
					}
					fnd = TRUE;
					break;
				}
			}
		}
	}
	return fnd;
}

/*****************************************************************************
 * Function:    MFC_error_t::getNextCheckedNotOk
 *
 * Description: Liefert den nächsten Fehler der gecheckt wurde und nicht ok
 *              war zurück, nach dem übergebenen io_idx
 *              -> TRUE wenn gefunden
 *              -> FALSE wenn nichts mehr gefunden
 *
/*****************************************************************************/
SBI_bool_t SBIAPI MFC_error_t::getNextCheckedNotOk(SBI_int32_t  *io_idx) {

	SBI_int32_t     i;
	SBI_int32_t     idx;
	SBI_bool_t      retval = FALSE;

	if (!isInit) {
		this->init();
	}
	if (MFC_CHECK(m_error[MFC_TU_ERR_IDX_ALL], MFC_TU_ERR_CHECKED)) {
		idx = (*io_idx) + 1;
		if (mfcCheckErrorIdx(idx)) {
			for (i = idx; i <= MFC_TU_ERR_IDX_MAX; i++) {
				if (MFC_CHECK(m_error[i], MFC_TU_ERR_CHECKED)) {
					if (MFC_CHECK(m_error[i], MFC_TU_ERR_ACTIVE)) {
						*io_idx = i;
						retval = TRUE;
						break;
					}
				}
			}
		}
	}
	return (retval);
}
/*****************************************************************************
 * Function:    MFC_error_t::getErrorTextAll
 *
 * Description: Fehlertext für alle gesetzten Fehler zurückgeben
 *
/*****************************************************************************/

SBI_char_t * SBIAPI MFC_error_t::getErrorTextAll(SBI_char_t     i_separator) {

	if (!isInit) {
		this->init();
	}
	return (this->getText(MFC_TU_ERR_ACTIVE, i_separator));
}

/*****************************************************************************
 * Function:    MFC_error_t::getErrorText
 *
 * Description: Fehlertext für einen bestimmten Fehler zurückgeben
 *
/*****************************************************************************/
SBI_char_t * SBIAPI MFC_error_t::getErrorText(SBI_int32_t    i_idx) {

	static SBI_char_t    errText[MFC_ERR_VAL_TEXT_LEN + 1];

	if (!isInit) {
		this->init();
	}
	if (mfcCheckErrorIdx(i_idx)) {
		//sprintf(errText, "%s", MFC_msgGet (0, MFC_ERR_MSG_OFFSET + i_idx));

		/* Umstellung:  Vorher -> Auslesen aus mfc_err.msg
		   mbo20090427  Nachher-> Auslesen aus mfc_state.msg

			strncpy ( errText, MFC_msgGet (0, MFC_ERR_MSG_OFFSET + i_idx),
							  MFC_ERR_VAL_TEXT_LEN ) ;
		*/

		/*strncpy(errText, MFC_convStateToStr("mfc", i_idx, MFC_ERR_MSG_OFFSET),
			MFC_ERR_VAL_TEXT_LEN);
			*/
		errText[MFC_ERR_VAL_TEXT_LEN] = 0;
	}
	else {
		errText[0] = '\0';
	}
	return (errText);
}

/*****************************************************************************
 * Function:    MFC_error_t::getInspectionTextAll
 *
 * Description: Fehlertext für alle noch zu prüfenden Fehler zurückgeben
 *
/*****************************************************************************/

SBI_char_t * SBIAPI MFC_error_t::getInspectionTextAll(SBI_char_t i_separator) {


	if (!isInit)
	{
		this->init();
	}
	return (this->getText(MFC_TU_ERR_INSPECTION, i_separator));
}




/*****************************************************************************/
/* ++858 linie
 * Function:    MFC_error_t::operator |
 *
 * Authors:     Peter Schneider
 * Created:     04-03-2002
 *
 * Description: Operator | wird fuer Klasse MFC_error_t uerberladen
 *
 * ErrorCode:   kein
 *
 * Change History:
 *    04-03-2002    PS    1. Version
 */
 /*****************************************************************************/

MFC_error_t MFC_error_t::operator | (MFC_error_t &x) {

	MFC_error_t   od;

	if (!isInit) {
		this->init();
	}
	for (SBI_int32_t i = MFC_TU_ERR_IDX_MIN; i <= MFC_TU_ERR_IDX_MAX; i++) {
		if (this->isSet(i) || x.isSet(i)) {
			od.setError(i);
		}
		else {
			if (this->isChecked(i) || x.isChecked(i)) {
				od.resetError(i);
			}
		}
			if (this->isForInspection(i) || x.isForInspection(i)) {
				od.setInspection(i);
		}
	}
	return (od);
}

/*****************************************************************************/
/* ++
 * Function:    MFC_error_t::operator &
 *
 * Authors:     Ralf Gebauer
 * Created:     04-03-2002
 *
 * Description: Operator & wird fuer Klasse MFC_error_t uerberladen
 *
 * ErrorCode:   kein
 *
 * Change History:
 *    07-03-2002    RG    1. Version
 */
 /*****************************************************************************/
MFC_error_t MFC_error_t::operator & (MFC_error_t &x) {

	MFC_error_t   und;

	if (!isInit) {
		this->init();
	}
	for (SBI_int32_t i = MFC_TU_ERR_IDX_MIN; i <= MFC_TU_ERR_IDX_MAX; i++) {
		if (this->isSet(i) && x.isSet(i)) {
			und.setError(i);
		}
		if (this->isForInspection(i) && x.isForInspection(i)) {
			und.setInspection(i);
		}
	}
	return (und);
}

/*****************************************************************************/
/*! ++
 * Function:    MFC_error_t::operator &=
 *
 * Authors:     Martin Baier
 * Created:     13-03-2002
 *
 * Description: Operator &= wird fuer Klasse MFC_error_t uerberladen
 *
 * ErrorCode:   kein
 *
 * Change History:
 *    13-03-2002    mb    1. Version
 */
 /*****************************************************************************/
MFC_error_t &MFC_error_t::operator &= (MFC_error_t &x) {

	if (!isInit) {
		this->init();
	}
	*this = *this & x;
	return *this;
}

/*****************************************************************************/
/*! ++
 * Function:    MFC_error_t::operator |=
 *
 * Authors:     Martin Baier
 * Created:     13-03-2002
 *
 * Description: Operator |= wird fuer Klasse MFC_error_t uerberladen
 *
 * ErrorCode:   kein
 *
 * Change History:
 *    13-03-2002    mb    1. Version
 */
 /*****************************************************************************/
MFC_error_t &MFC_error_t::operator |= (MFC_error_t &x) {

	if (!isInit) {
		this->init();
	}
	*this = *this | x;
	return *this;
}

/*****************************************************************************/
/* ++
 * Function:    MFC_error_t::operator ==
 *
 * Authors:     Ralf Gebauer
 * Created:     17-03-2004
 *
 * Description: Operator == wird fuer Klasse MFC_error_t uerberladen
 *              Prüft NUR Fehler, keine Inspection etc...
 * ErrorCode:   kein
 *
 * Change History:
 *    07-03-2002    RG    1. Version
 */
 /*****************************************************************************/

SBI_bool_t MFC_error_t::operator == (MFC_error_t &x) {

	SBI_bool_t retVal = TRUE;

	if (!isInit)
	{
		this->init();
	}
	for (SBI_int32_t i = MFC_TU_ERR_IDX_MIN; retVal && i <= MFC_TU_ERR_IDX_MAX; i++)
	{
		if (this->isSet(i) != x.isSet(i))
		{
			retVal = FALSE;
		}
	}
	return retVal;
}

/*****************************************************************************/
/* ++
 * Function:    MFC_error_t::operator !=
 *
 * Authors:     Ralf Gebauer
 * Created:     17-03-2004
 *
 * Description: Operator != wird fuer Klasse MFC_error_t uerberladen
 *              Prüft NUR Fehler, keine Inspection etc...
 * ErrorCode:   kein
 *
 * Change History:
 *    07-03-2002    RG    1. Version
 */
 /*****************************************************************************/

 SBI_bool_t MFC_error_t::operator!= (MFC_error_t &x){
 
	 SBI_bool_t retVal = TRUE;

	 retVal = (*this == x);

	 return (!retVal);
 }
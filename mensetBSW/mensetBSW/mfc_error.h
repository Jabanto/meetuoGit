#pragma once

/*-----------------------------------------------------------------------------
 * $Header: /abl/source/mfc/mfc/src/mfc_error.h 27    14.01.15 14:17 Dheindl $
 *
 * File        : $Archive: /abl/source/mfc/mfc/src/mfc_error.h $
 * Copyright   : WITRON Logistik + Informatik GmbH
 * Project     : MFC
 *
/*###############################################################################*/
/*----------------------------- MFC - ErrorMask-Klasse -------------------------*/
/*###############################################################################*
 *
 * Description : Datentyp zum handling von Fehlern einer TU (LVR/MFC/SPS-Fehler)
 *
 * Anwendungsbeispiele:
 *            typedef enum {
 *	         DEFINE_1 = 4,	//Bit 4 (5.Bit) wird gesetzt
 *               DEFINE_2 = 6	//Bit 6 wird gesetzt
 *            } MFC_ERR_VAL_or_t;
 *
 *            MFC_error_t  error;
 *
 *	      MFC_error_t  error.set (DEFINE_2 | DEFINE_1)
 *						//Bit 4 und 6 werden gesetzt
 *
 *	      error.reset (DEFINE_1)	//Bit 4 wird zurueckgesetzt
 *
 * Version     : $Revision: 27 $
 *
 * Authors:    : Peter Schneider
 *
 * Last change : $Modtime: 14.01.15 14:17 $ by $Author: Dheindl $
 *
 * Change History :
 *    06-12-2000 PS   first version
 *
 *
 *---------------------------------------------------------------------------*/

 /** @file */
 /**
  * \addtogroup     MFC
  * @{
  * \addtogroup     MFC_Interface
  * @{
  */

#ifndef MFC_ERROR_H
	#define MFC_ERROR_H

	#include "mfc_def.h"
	#include "mfci_typ.h"		/* wj mfci muss sein weil in mfc_dce.h MFC_error_t verwendet wird*/

	typedef SBI_char_t		MFC_errorVb_t[MFC_TU_ERR_SIZE];		/* Null terminierte string */
																/* Für Übergabe an VB ,Byte 0 sagt ob ein Fehler */
																/* Gezetz ist oder nicht , der String wird durch */
																/* getErrorAsString gefullt */
	#if !defined(IDL_COMPILER)
		#include "sbi_if.h"
		#include "mfc_classes.h"
		#include "wchar.h" /* Manuel fragen wann wird diese Klasse(Header) aufgerufen*/
 
		#ifndef SBI_VMS
			#include <crtdbg.h>
		#else
			#include <assert.h>
		#endif // !SBI_VMS


		#if defined(__cplusplus)
	extern "C" {
#endif

		/* Definition der Fehlerbits */

#define MFC_ERR_VAL_NONE				0  /* init-value                     */
#define MFC_CHR_0_VALUE                '0' 
#define MFC_CHR_1_VALUE                '1' 

#define MFC_TU_ERR_INIT_CHAR            '@'

#define MFC_TU_ERR_ACTIVE               (1L << 0)
#define MFC_TU_ERR_CHECKED              (1L << 1)
#define MFC_TU_ERR_INSPECTION           (1L << 2)

#define MFC_ERR_MSG_OFFSET              1000			/* Zugriff auf MSG-File mit offset + Fehler-Index */

typedef SBI_char_t   MFC_err_text_t[MFC_ERR_VAL_TEXT_LEN * MFC_TU_ERR_CNT_ALL];

	class SBIDLLAPI MFC_error_t {
		protected:

			SBI_int32_t     m_errorCnt;
			SBI_int32_t     m_checkedCnt;
			SBI_char_t      m_error[MFC_TU_ERR_SIZE];
			SBI_bool_t      isInit;
			/* Kurztext für einen oder mehrere Fehler zurückgeben mit Separator */
			SBI_char_t *    SBIAPI getText(SBI_int32_t,SBI_char_t = '|');

			void copyClassToClass(MFC_error_t &x);

			/* spezielle Löschfunktion die alle Bytes mit '0' initialisiert */

			void clear(void); 

			/* einen Fehler setzen, ohne checked zu berücksichtigen */
			void SBIAPI setErrorOnly(SBI_int32_t);

		#define MFC_ERR_TEXT_CNT_MAX      3  /* Anzahl Fehler gleichzeitig in sprintf-MACRO */

		public:

			SBIAPI  MFC_error_t();							 /* Konstruktor */
			SBIAPI  MFC_error_t(MFC_error_t &x);             /* Copy-Konstruktor */

			MFC_error_t  operator  |  (MFC_error_t &x);
			MFC_error_t  operator  &  (MFC_error_t &x);
			MFC_error_t &operator  &= (MFC_error_t &x);
			MFC_error_t &operator  |= (MFC_error_t &x);
			SBI_bool_t   operator  == (MFC_error_t &x);
			SBI_bool_t   operator  != (MFC_error_t &x);

			/* -------------------------- Öffentlichen Methoden -------------------------- */		

			/* alle Daten zurücksetzen auf 0 / FALSE */
			void SBIAPI init();

			/* einen Fehler setzen */
			void SBIAPI setError(SBI_int32_t);

			/* einen Fehler zurücksetzen */
			void SBIAPI resetError(SBI_int32_t);

			/* einen Fehler ändern */
			void SBIAPI updError(SBI_int32_t, SBI_bool_t);

			/* pruefen, ob ein Fehler gesetzt ist */
			SBI_bool_t SBIAPI isSet(SBI_int32_t);

			/* pruefen, ob ein Fehler nicht gesetzt ist */
			SBI_bool_t SBIAPI isOk(SBI_int32_t);

			/* Zurücksetzen checked-Bit eines Fehlers */
			SBI_bool_t SBIAPI isChecked(SBI_int32_t);

			/* res, ob ein Fehler schon geprüft ist */
			void SBIAPI resetChecked(SBI_int32_t);

			/* Fehler an übergeordn. System melden */
			SBI_bool_t SBIAPI sendErrorInfo (MFCI_tu_id_t  i_tuId,
											SBI_int32_t   i_errorIndex,
											SBI_bool_t(USER_sndTuError(MFCI_tu_id_t i_tuId,
											SBI_bool_t   i_errorValue,
											SBI_int32_t  i_errorIndex,
											SBI_int32_t *o_error)));

			/* Gibt den ersten Fehler zurück, der gesetzt ist -> TRUE wenn gefunden / FALSE wenn nicht */
			SBI_bool_t SBIAPI getError(SBI_int32_t *o_idx = NULL);

			/* Gibt den nächsten Fehler nach dem übergebenen actError zurück -> TRUE wenn gefunden / FALSE wenn nicht */
			SBI_bool_t SBIAPI getNextError(SBI_int32_t *);

			/* gibt den ersten noch nicht gecheckten Fehler zurück */
			SBI_bool_t SBIAPI getNotChecked(SBI_int32_t *o_idx = NULL);

			/* gibt den nächsten noch nicht gecheckten Fehler nach dem übergebenen actError zurück */
			SBI_bool_t SBIAPI getNextNotChecked(SBI_int32_t *);

			/* Pruefe ob alle bereits gecheckten Fehler ok waren */
			SBI_bool_t SBIAPI allCheckedOk();

			/* Liefert den ersten Fehler der gechecked wurde und nicht ok war */
			SBI_bool_t SBIAPI getCheckedNotOk(SBI_int32_t *o_idx = NULL);

			/* Liefert den nächsten Fehler der gechecked wurde und nicht ok war zurück, nach dem übergebenen actError */
			SBI_bool_t SBIAPI getNextCheckedNotOk(SBI_int32_t *);

			/* Kurztext für alle gesetzten Fehler zurückgeben mit Separator */
			SBI_char_t * SBIAPI getErrorTextAll(SBI_char_t = '|');

			/* Kurztext für einen bestimmten Fehler zurückgeben */
			SBI_char_t * SBIAPI getErrorText(SBI_int32_t);

			/* Kurztext für alle Checked Fehler zurückgeben mit Separator */
			//SBI_char_t * SBIAPI getCheckedTextAll(SBI_char_t = '|');

			/* Gibt den Fehler-String zurück -> für Dialoge zum Auswerten etc. -> nur '0' und '1' */
			/* wird benutzt, d.h. es werden nur die Fehlerstati gesetzt, checked und inspection   */
			/* wird ignoriert!                                                                    */
			//SBI_char_t * SBIAPI getErrorAsString2(SBI_char_t o_errStr[MFC_TU_ERR_SIZE]); /* Thread Safe */
			//SBI_char_t * SBIAPI getErrorAsString();

			//SBI_char_t * SBIAPI getInspectionAsString2(SBI_char_t o_errStr[MFC_TU_ERR_SIZE]); /* Thread Safe */
			//SBI_char_t * SBIAPI getInspectionAsString();

			//SBI_char_t * SBIAPI getCheckedAsString2(SBI_char_t o_errStr[MFC_TU_ERR_SIZE]); /* Thread Safe */
			//SBI_char_t * SBIAPI getCheckedAsString();

			/* Kopiert die Fehler aus einem String wieder zurück in die Klasse */
			//void SBIAPI copyErrorStringToClass(SBI_char_t  i_errStr[], SBI_int32_t);

			/* Eintragen der Fehler von SPS-Message in die Daten */
			/*void SBIAPI insertErrorFromSpsMsg(SBI_char_t &,
				SBI_int32_t,
				SBI_int32_t i_checkMask = 0x3F3F3F3F);*/

			/* Zurückschreiben der Fehler aus tuError in Dimensionsfehler der SPS-Msg */
			//void SBIAPI writeErrorToSpsMsg(SBI_char_t  *,
			//	SBI_int32_t);



			void SBIAPI setInspection(SBI_int32_t);

			void SBIAPI resetInspection(SBI_int32_t);

			/* pruefen, ob ein Fehler geprüft werden soll (für WS - Parametrierung) */
			SBI_bool_t SBIAPI isForInspection(SBI_int32_t);

			SBI_char_t * SBIAPI getInspectionTextAll(SBI_char_t = '|');

			SBI_int32_t SBIAPI cntErrors();

		private:

			/*Prüft den Index i_idx auf erlaubte Werte*/
			SBI_bool_t	mfcCheckErrorIdx(SBI_int32_t);

		};

	/* -------------------------- Protected Funktionen -------------------------- */
	/*****************************************************************************
	* Function:    MFC_error_t::copyClassToClass
	*
	* Description: Kopiert den Inhalt der Memebervariablen MFC_error_t von einer
	*              Klasse zur anderen
	*
	*****************************************************************************/
	inline void MFC_error_t::copyClassToClass(MFC_error_t &x) {

		if (isInit == FALSE)
		{
			this->init();
		}
		memcpy(m_error, x.m_error, (sizeof(SBI_char_t) * MFC_TU_ERR_SIZE));
		m_errorCnt = x.m_errorCnt;
		m_checkedCnt = x.m_checkedCnt;
	}

	/*****************************************************************************
	* Function:    MFC_error_t::init
	*
	* Description: Rücksetzen aller Daten
	*
	*****************************************************************************/
	inline void SBIAPI MFC_error_t::init(void){
		
		memset(m_error, MFC_TU_ERR_INIT_CHAR, (sizeof(SBI_char_t) * MFC_TU_ERR_CNT_ALL + 1));
		m_error[MFCI_TU_ERR_SIZE - 1] = '\0';
		m_errorCnt = 0;
		m_checkedCnt = 0;
		isInit = TRUE;
	}

	/*****************************************************************************
	* Function:    MFC_error_t::clear
	*
	* Description: Löscht alle Bytes auf '0' nach vorherigem init
	*
	*****************************************************************************/
	inline void MFC_error_t::clear(void) {
		this->init();
		memset(m_error, MFC_CHR_0_VALUE, (sizeof(SBI_char_t) * MFC_TU_ERR_SIZE - 1));
		m_error[MFC_TU_ERR_SIZE - 1] = '\0';
	}

	/*****************************************************************************
	* Function:    MFC_error_t::setErrorOnly
	*
	* Description: Setzen eines Fehlers OHNE update checked -> internal use only
	*
	*****************************************************************************/
	inline void SBIAPI MFC_error_t::setErrorOnly(SBI_int32_t   i_idx) {

		if (isInit == FALSE) {
			this->init();
		}
		if (mfcCheckErrorIdx(i_idx)) {
			if (MFC_CHECK(m_error[i_idx], MFC_TU_ERR_ACTIVE) == FALSE) {
				MFC_SET(m_error[i_idx], MFC_TU_ERR_ACTIVE);
				m_errorCnt++;
			}
			MFC_SET(m_error[MFC_TU_ERR_IDX_ALL], MFC_TU_ERR_ACTIVE);
		}
	}


	/*****************************************************************************
	* Function:    mfcCheckErrorIdx
	*
	* Description: Prüft den Index i_idx auf erlaubte Werte
	*
	*****************************************************************************/
	inline SBI_bool_t  MFC_error_t::mfcCheckErrorIdx(SBI_int32_t     i_idx) {

		if (i_idx >= MFC_TU_ERR_IDX_MIN) {
			if (i_idx <= MFC_TU_ERR_IDX_MAX) {
				return (TRUE);
			}
		}
		return (FALSE);
	}

	/* -------------------------- Publik Funktionen -------------------------- */
	/*****************************************************************************
	* Function:    MFC_error_t::MFC_error_t
	*
	* Description: Initialisierungen für MFC_error_t
	*
	*****************************************************************************/
	inline SBIAPI MFC_error_t::MFC_error_t() {
		init();
	}

	/*****************************************************************************
	* Function:    cntErrors
	*
	* Description: Prüft den Index i_idx auf erlaubte Werte
	*
	*****************************************************************************/
	inline SBI_int32_t SBIAPI MFC_error_t::cntErrors() {
		return (m_errorCnt);
	}

	/*****************************************************************************
	* Function:    MFC_error_t::MFC_Error_(MFC_error_t)
	*
	* Description: Kopieren eines Klassen-Elementes auf ein anderes
	*
	*****************************************************************************/
	inline SBIAPI MFC_error_t::MFC_error_t(MFC_error_t &x) {

		if (isInit == FALSE)
		{
			this->init();
		}
		copyClassToClass(x);
	}



	#else		 /*Für DLL Compiler*/

	#endif		/*Für DLL Compiler*/

	#if defined(__cplusplus)
		}
	#endif



#endif // !MFC_ERROR_H



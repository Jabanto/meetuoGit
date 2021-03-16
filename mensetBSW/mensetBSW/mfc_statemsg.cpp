#include "pch.h"
#include "mfc_statemsg.h"


#define MFC_MAX_TXT 33
#define MFC_STATE_MSG_MAX_FILES 30

/*-----------------------------------------------------------------------------
 * $Header: /abl/source/mfc/mfc/src/mfc_statemsg.cpp 10    7.07.09 19:08 Wjakob $
 *
 * File        : $Archive: /abl/source/mfc/mfc/src/mfc_statemsg.cpp $
 *
 * Copyright   : WITRON Logistik + Informatik GmbH
 *
 * Project     : O
 *
 * Description : Funktionen fuer MSG - Texte
 *
 * Version     : $Revision: 10 $
 *
 * Authors     : Geiling Jens
 *
 * Last change : $Modtime: 7.07.09 19:08 $ by $Author: Wjakob $
 *
 * Change History :
 *   06-Dez-2001 jg  HP, 1. Version
 *
 *
 *---------------------------------------------------------------------------*/

#include "sbi_if.h"
//#include "msg_if.h"
#include "mfc_if.h"



typedef struct coMsgHndl_s {

	//MSGhandle_typ  hndl;
	SBI_char_t     modul[10];
	SBI_bool_t     openDone;
} coMsgHndl_t;


static SBI_int32_t  ownTextIdx = -1;
static SBI_char_t   ownText[MFC_MAX_TXT][256];
static SBI_bool_t   MsgInitDone = FALSE;
static coMsgHndl_t  MsgHndl[MFC_STATE_MSG_MAX_FILES];
static SBI_int32_t  ownMsgIdx = -1;

#define MFC_MSG_STR_LEN 256
static char_typ     ownMsgString[MFC_MAX_TXT][MFC_MSG_STR_LEN];

/* ++
 * Function:    MFC_convStateToStr
 *
 * Authors:     Geiling Jens
 * Created:     06-12-2001
 * Arguments:
 *
 * Return:      Msg Text
 *
 * Description: Convertert Offset zu String
 *
 * ErrorCode:
 *
 * Change History:
 *
 * --
*/

const SBI_char_typ *MFC_convStateToStr(SBI_char_t      *i_modul,
									   SBI_int32_t      i_state,
									   SBI_int32_t      i_offset) {
	SBI_char_t         *TextBuf;
	SBI_bool_t          FileIsOpen = FALSE;
	SBI_int32_t         MsgFileIdx = 0;
	SBI_int32_t         origState;

	origState = i_state;
	i_state += i_offset;

	if (ownTextIdx < MFC_MAX_TXT - 1) {
		++ownTextIdx;
	}
	else {
		ownTextIdx = 0;
	}

	if (MsgInitDone == FALSE) {
		memset(MsgHndl, 0, sizeof(coMsgHndl_t) * MFC_STATE_MSG_MAX_FILES);
		MsgInitDone = TRUE;
	}

	/*
	for (SBI_int32_t i = 1; i <= MFC_STATE_MSG_MAX_FILES; i++) {
		if (strcmp(MsgHndl[i].modul, i_modul) == 0) {
			FileIsOpen = TRUE;
			MsgFileIdx = i;
			break;
		}
	}*/

/*
	
	if (!FileIsOpen) {
		FileIsOpen = mfcStateMsgOpen(i_modul, &MsgFileIdx);
	}

	if (FileIsOpen) {
		if (MsgFileIdx < MFC_STATE_MSG_MAX_FILES) {
			if (MsgHndl[MsgFileIdx].hndl != NULL) {
				TextBuf = MSG_get(MsgHndl[MsgFileIdx].hndl, i_state);
				/* MSG_get does not allocate memory internally,
				   so no free is necessary afterwards
				   TextBuf points to memory within MSG module */
				//if (strcmp(TextBuf, "???") == 0) {
					/* this is too long for Info screens
					sprintf(ownText[ownTextIdx],"-E-Kein Eintrag fuer Modul: %s, State: %d, Offset: %d",i_modul,origState,i_offset);
					*/
					//sprintf(ownText[ownTextIdx], "%d <??\?>, Module %s, Offset %d",
					//	origState, i_modul, i_offset); // Achtung: trigraph Translation
	//			}
	//			else {
	//				SBI_int32_t TextLen = strlen(TextBuf);
	//				if (TextLen > MFC_MSG_STR_LEN - 1) TextLen = MFC_MSG_STR_LEN - 1;
	//				strncpy(ownText[ownTextIdx], TextBuf, TextLen);  ownText[ownTextIdx][TextLen] = '\0';
	//				/*mn20081029 nach eMail von SchneiderP
	//						  sprintf(ownText[ownTextIdx],"%s",TextBuf); */
	//		
	//			}
	//		}
	//	}
	//}
	//else {
	//	sprintf(ownText[ownTextIdx], "can not open MSG-file, Module %s", i_modul);
	//	//sprintf(ownText[ownTextIdx],"-E-Kein Modul: %s",i_modul);
	//}

	
	return (ownText[ownTextIdx]);

}

/* ++
 * Function:    MFC_convMsgClose
 * Authors:     Geiling Jens
 * Created:     04-12-2001
 * Arguments:
 *
 * Return:
 *
 * Description: Schlieﬂen der MsgFiles
 *
 * ErrorCode:
 *
 * Change History:
 *
 * --
*/


 bool_typ MFC_convMsgClose () {

	bool_typ           retval = TRUE;
	//MSGerrorCode_typ   retcode;
	int32_typ          i;

	for (i = 0; i < MFC_STATE_MSG_MAX_FILES; i++) {
		if (MsgHndl[i].openDone != NULL) {
			//retcode = MSG_close(&MsgHndl[i].hndl);
			MsgInitDone = FALSE;
			/*if (retcode != MSG_OK) {
				retval = FALSE;
			}*/
		}
	}
	return (retval);

}


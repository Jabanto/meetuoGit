#pragma once


/*---------------------------------------------------------------------------- -
*$Header: / abl / source / mfc / mfc / src / mfc_statemsg.h 4     14.01.15 14 : 17 Dheindl $
*
* File : $Archive : / abl / source / mfc / mfc / src / mfc_statemsg.h $
*
* Copyright : WITRON Logistik + Informatik GmbH
*
* Project : ABL
*
* Description : Diese Header beinhaltet alle moduluebergreifenden
*               Prototypes.
*
* Version : $Revision : 4 $
*
* Authors : Werner Jakob
*
* Last change : $Modtime: 14.01.15 14 : 17 $ by $Author : Dheindl $
*
* Change History :
*08 - OCT - 2002 wj  mfcb, 1. Version
*
*
*-------------------------------------------------------------------------- - */

/** @file */
/**
 * \addtogroup     MFC
 * @{
 * \addtogroup     MFC_Interface
 * @{
 */

#if !defined(MFC_STATE_MSG_H)
#define MFC_STATE_MSG_H

 /*---------------------------- Include Files --------------------------------*/

#include "SBI_dce.h"
#include "sbi_if.h"

#if defined (__cplusplus)
	extern "C" {
#endif

SBIDLLAPI const SBI_char_typ* SBIAPI MFC_convStateToStr (SBI_char_t      *i_modul,
														 SBI_int32_t      i_state,
														 SBI_int32_t      i_offset);

SBIDLLAPI bool_typ SBIAPI MFC_convMsgClose();


#if defined (__cplusplus)
}
#endif

#endif /* MFC_STATE_MSG_H */

/* ende mfc_statemsg.h */



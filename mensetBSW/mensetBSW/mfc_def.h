#pragma once

#if !defined( MFC_DEF_H )
#define MFC_DEF_H

/*---------------------------- Include Files --------------------------------*/

#include "mfci.h"

#if defined (MFCI_AEVT)
#include "aevt_def.h"
#endif

#if !defined(IDL_COMPILER)

#include "mfc_classes.h"

#endif /* IDL Compiler */


#if defined ( __cplusplus )
extern "C" {
#endif


/*---------------------------- const MFC_tuError_t --------------------------*/
/* Konstanten für die Klasse MFC_tuError_t -> müssen wegen RPC-Comm. hier mit*/
/* exportiert werden, da RPC keine Klassen versteht                          */
/* ------------------------------------------------------------------------- */
/* Anzahl verschiedener Fehler    */
#define MFC_TU_ERR_CNT_ALL				 MFCI_TU_ERR_CNT_ALL 

/* String-Länge der Error-Information                                        */
#define MFC_TU_ERR_SIZE					 MFCI_TU_ERR_SIZE

#define MFC_ERR_VAL_TEXT_LEN			16 /* Fehlertextlaenge Single-Error  */


#define MFC_TU_ERR_IDX_ALL				0  /* Sammelinformation des Strings  */
#define MFC_TU_ERR_IDX_MIN				1  /* Minimaler Errror               */ 
#define MFC_TU_ERR_IDX_MAX				MFC_TU_ERR_CNT_ALL /*L108*/

#define MFCI_TU_ERR_SEND_ALL            0 /* senden aller Error-Info an LVR  L=121*/
#if defined ( __cplusplus )
}
#endif

/*
 * !!!!!
 * !!!!! weitere Überladene Versionen fuer MFC_SET,MFC_RESET,MFC_CHECK,MFC_IN
 * !!!!! gibts in mfc_error.h
 * !!!!!
 */

 /*
  * BIT-OPERATOREN
  *
  *   & (AND):                     | (OR):
  *
  *      |*******|*******|*****|      |*******|*******|*****|
  *      | Wert1 | Wert2 | Erg |      | Wert1 | Wert2 | Erg |
  *      |*******|*******|*****|      |*******|*******|*****|
  *      |   0   |   0   |  0  |      |   0   |   0   |  0  |
  *      |-------|-------|-----|      |-------|-------|-----|
  *      |   0   |   1   |  0  |      |   0   |   1   |  1  |
  *      |-------|-------|-----|      |-------|-------|-----|
  *      |   1   |   0   |  0  |      |   1   |   0   |  1  |
  *      |-------|-------|-----|      |-------|-------|-----|
  *      |   1   |   1   |  1  |      |   1   |   1   |  1  |
  *      |*******|*******|*****|      |*******|*******|*****|
  *
  *
  *   ^ (EXCLUSIVE OR / XOR):      ~ (NOT):
  *
  *       |*******|*******|*****|     |*******|*****|
  *       | Wert1 | Wert2 | Erg |     | Wert1 | Erg |
  *       |*******|*******|*****|     |*******|*****|
  *       |   0   |   0   |  0  |     |   0   |  1  |
  *       |-------|-------|-----|     |-------|-----|
  *       |   0   |   1   |  1  |     |   1   |  0  |
  *       |-------|-------|-----|     |*******|*****|
  *       |   1   |   0   |  1  |
  *       |-------|-------|-----|
  *       |   1   |   1   |  0  |
  *       |*******|*******|*****|
  *
 */

inline void MFC_SET(MFC_updMask_t &x, MFC_updMask_t y) { x |= y; }
inline void MFC_SET(SBI_int32_t   &x, SBI_int32_t y) { x |= y; }
inline void MFC_SET(SBI_char_t    &x, SBI_int32_t y) { x |= y; }

inline void MFC_RESET(MFC_updMask_t &x, MFC_updMask_t y) { x &= ~y; }
inline void MFC_RESET(SBI_int32_t   &x, SBI_int32_t y) { x &= ~y; }
inline void MFC_RESET(SBI_char_t    &x, SBI_int32_t y) { x &= ~y; }

/* FUE 30-03-1999
   Makros werden ersetzt mit Inline-Funktionen (wg. Klasse MFC_updMask_t)
   wg. Ueberladung ausserhalb von __cplusplus

#define MFC_SET(x,y)   (x) |= (y)
#define MFC_RESET(x,y) (x) &= ~(y)
#define MFC_CHECK(x,y) (((x) & (y))?TRUE:FALSE)
#define MFC_INIT(x)    (x) = 0
*/

inline SBI_bool_t MFC_CHECK(SBI_int32_t x, SBI_int32_t y) { return (((x) & (y)) ? TRUE : FALSE); }
inline SBI_bool_t MFC_CHECK(SBI_char_t  x, SBI_int32_t y) { return (((x) & (y)) ? TRUE : FALSE); } //line872


#if !defined(IDL_COMPILER)


#endif /* IDL_COMPILER */

#endif  /* MFC_DEF_H */
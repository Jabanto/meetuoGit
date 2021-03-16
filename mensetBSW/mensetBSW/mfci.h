#pragma once

#define MFCI_ID_LEN            12    /* Laenge von Zielkennungen             */


#define MFCI_TU_ID_LEN_MSG     13       /* Laenge der TU-Nummer im Telegramm + 1 */
//20100708wj immer volle laenge wie in DB verwenden 
#define MFCI_TU_ID_LEN         19       /* Laenge der TU-Nummer + 1 */
#define MFCI_TOTE_ID_LEN_MSG   20       /* Laenge der Kisten-Nummer (DPS/ATS) im Telegramm */


#define MFCI_SSCC_ID_LEN_MSG   19		/*Länge der SSCC-Nummer in Telegramm +1*/


/*------------Constants for quit-queue------------------*/

#define MFCI_MODUL_LEN			4		/* Format: MMM */

/* ^^^^^^ END   Anpassen erlaubt ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/* --- Defines fuer ErrorCodes ---------------------------------------------- */
/*     Aenderungen und Ergaenzungen muessen auch im                           */
/*     mfciert.c -> mfciCvtErrorCode                                          */
/*     gemacht werden !!!!!!!!!!!!!!!                                         */
/* -------------------------------------------------------------------------- */
#define MFCI_TU_ERR_CNT_ALL        80 /* Anzahl erlaubter Errors          */
#define MFCI_TU_ERR_SIZE           82
/* 20051206wj sonst geht constconv nicht !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*#define MFCI_TU_ERR_SIZE            MFCI_TU_ERR_CNT_ALL + 1 + 1         */
/* -------------------------------------------------------------------------- */

/* !!!!! Konturefehler müssen blockweise hintereinander kommen ohne Lücken !!!! */
/* Konturenfehler Byte 1 in SPS-Message */
#define MFCI_TU_ERR_OVERLEN_F       41          /* Überlänge vorne                */
#define MFCI_SPS_ERR_OVERLEN_F      ( 1L << 0 ) /* Stelle in Msg: Bit 0 in Byte 1 -L1035*/


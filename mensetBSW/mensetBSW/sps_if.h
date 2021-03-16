#pragma once
/*-----------------------------------------------------------------------------
 * $Header: /abl/source/mfc/sps/src/sps_if.h 28    12.05.17 9:40 Ehaeupler $
 *
 * File        : $Archive: /abl/source/mfc/sps/src/sps_if.h $
 *
 * Copyright   : WITRON Logistik + Informatik GmbH
 *
 * Project     : SPS
 *
 * Description : Header-File fuer die SPS Interface Funktionen
 *
 * Version     : $Revision: 28 $
 *
 * Authors     : Werner Jakob
 *
 * Last change : $Modtime: 12.05.17 9:40 $ by $Author: Ehaeupler $
 *
 * Change History :
/* ch,om#MFCB_CC 2014-12-15 automatic libinclude
 *    04-04-1995 wj  1. Version
 *    08-05-1995 ma  Beruecksichtigung des IDL Compiler
 *
 *
 *---------------------------------------------------------------------------*/

 /** @file */
 /**
  * \addtogroup     SPS
  * @{
  * \addtogroup     SPS_Interface
  * @{
  */

#if !defined(SPS_IF_H)
#define SPS_IF_H

  /*--- include Files ---------------------------------------------------------*/

#if !defined(IDL_COMPILER)
#include "sbi_if.h"
#include "vots_if.h"
#endif /* IDL_COMPILER */

#if defined(__cplusplus)
extern "C" {
#endif

	/* Nur ab Studio 10.0 */
#if (SBI_WINNT && _MSC_VER >= 1600)
//#ifndef LIB_AC_sps  /* ch,om#MFCB_CC 2014-12-15 automatic libinclude
//					   wird im jeweiligen Propeperty Sheet
//					   (o:\asl\runtime\etc\dllProject.props bzw. exeProject.props)
//					   des Projekts (*.vcprj) gesetzt um eine Selbstincludierung zu vermeiden.
//					   Siehe: View -> PropertyManager -> dllxxx -> Debug|Win32 -> dllProject*/
//#pragma comment (lib,"R:\\abl\\runtime\\lib\\dllsps.lib")
//#endif
#endif

	/*--- Konstantendefinitionen ------------------------------------------------*/
/* Laengenkonstanten */
#define SPS_MSG_LEN				1025    /* Laenge des Message Puffers        */
#define SPS_MAX_MELDEPUNKTE		4000 + 1/* maximale Anzahl Meldepunkte       
											* im shared memory. (2 x 256)    */
#define SPS_MAX_BL_TRM			39		/* maximale Anzahl Messages pro      *
										    * Block bei Blocking			 */
#define SPS_HELPTXT_LEN			63		/* Laenge Hilfetext                  */
#define SPS_USERSTR_LEN			33		/* Laenge User String                */
#define SPS_KENN_LEN			3		/* Laenge Kennung                    */
#define SPS_COMTYP_LEN			5       /* Laenge Produktkennung             */
#define SPS_FNAME_LEN			257     /* Laenge Dateinamen                 */
#define SPS_INDC_LEN			513		/* Laenge fuer Indices Zwischenpuffer*/
#define SPS_LN_LEN				3           

#define SPS_MSG_LEN				1025	/* Länge des Message Puffers*/

/*--- Defines fuer den Meldungsheader ---------------------------------------*/
#define SPS_M_HEADER_LEN		8		/* Laenge des Meldungsheaders        */
#define SPS_M_SRC_POS 			0		/* Position Quelle                   */
#define SPS_M_MS_POS			4		/* Position Meldestelleneintrag      */
#define SPS_M_LNR_LEN			2           /* Laenge der Laufnummer             */
#define SPS_M_LNR_POS			6		/* Position der Laufnummer           */
#define SPS_M_MAX_LNR			99		/* groesste moegliche Laufnummer     */
#define SPS_M_TGT_POS			2		/* Position Ziel                     */


	/* Blocking ON/OFF */
#define SPS_BLOCKING_ON			1		/* Blocking On                       */
#define SPS_BLOCKING_OFF		0		/* Blocking Off                      */

/* Userdaten anzeigen ON/OFF */
#define SPS_USER_DATA_ON		1		/* User Daten anzeigen               */
#define SPS_USER_DATA_OFF		0		/* User Daten nicht anzeigen         */

/* Status nicht gesetzt */
#define SPS_STATUS_NONE			-1
#define SPS_CHR_STATUS_NONE		'\0'

/* Konstanten fuer die Konvertierung der Zeitdarstellung */
#define SPS_DOUBLE_TIMEVAL		0		/* konvertiert double -> timeval     */
#define SPS_TIMEVAL_DOUBLE		1		/* konvertiert timeval -> double     */

	/* Konstanten fuer Stati */
#define SPS_MSG_CODE_OK			'L'           /* Msg war ok (trm,rcv) Line         */
#define SPS_MSG_CODE_SIM		'S'           /* Msg war ok (trm,rcv) simuliert    */
#define SPS_MSG_CODE_ERR		'E'           /* Msg mit Formatfehler              */
												/*         (Empfang von Leitung)     */
#define SPS_MSG_CODE_SE			'F'           /* Msg mit Formatfehler              */
												/*         (Empfang simuliert)       */
#define SPS_MSG_CODE_BLCK		'B'           /* geblockte Msg                     */
#define SPS_MSG_CODE_TSIM		'T'           /* simulierte Sende Msg (trm)        */
#define SPS_MSG_CODE_BREAK		'X'		    	/* Receive wurde durch Timeout oder  */
					/* Event unterbrochen */

#define SPS_MPVKZ_NOCHECK		'I'           /* Laufnummern werden nicht geprueft */
#define SPS_MPVKZ_SLAVE			'S'           /* Slave  LN wird geprueft, Msg      */
					/*           selbst. wiederholt      */
#define SPS_MPVKZ_MASTER		'M'           /* Master (with response)            */
#define SPS_MPVKZ_ORDER			'O'           /* Master (no response) = Order      */


#define SPS_FLAG_ON				1             /* Flag eingeschaltet                */
#define SPS_FLAG_OFF			0             /* Flag ausgeschaltet                */

/* Konstanten fuer Meldungstypen */
#define SPS_ACT_RCV_MSG			1			  /* letzte empfangene Meldung         */
#define SPS_LAST_RCV_MSG		2			  /* vor der letzten empfangene Meldung*/
#define SPS_ACT_TRM_MSG			3			  /* letzte gesendete Meldung          */

/* Verbindungsprodukte */
#define SPS_COM_VOTS			1		   	  /* Verbindung ueber VOTS            */
#define SPS_COM_TCP				2             /* Verbindung ueber TCP             */

	/* Meldungsstati (Fuer Send nur SPS_MSG_LINE und SPS_MSG_SIM_SEND zulaessig) */
/* der Verbindungsprodukte                                                   */
#define SPS_MSG_LINE			0             /* Meldung von/fuer eine Line        */
#define SPS_MSG_LINE_MORE		1             /* Meldung von/fuer eine Line, es    */
					/* folgen jedoch weitere Daten       */
#define SPS_MSG_SIM_RECEIVE		2             /* simulierte Empfangsmeldung        */
#define SPS_MSG_SIM_SEND		3             /* simulierte Sendemeldung           */
#define SPS_MSG_TIMEOUT			4             /* Timeout beim Receive              */
#define SPS_MSG_EVENT			5             /* Anstoss von Aussen                */

#define SPS_M_SLAVE_LN_TERM		'@'           /* zur Zerstörung der Laufnummer einer vorangegangenen 
					   Transmitmessage 981005 gl */

/* auszuwertende Fehlerwerte der Verbindungsprodukte */
#define SPS_COM_ERR_ACCESS     -17			  /* Fehler beim Zugriff auf Verbindung*/
#define SPS_COM_ERR_TIMEOUT    -18			  /* Timeout                          */
#define SPS_COM_ERR_DISCONNECT -19		      /* Disconnect detektiert            */

/* Rueckgabewerte der Funktionen */
#define SPS_OK					0			  /* Aufruf OK                         */
#define SPS_NOK					-1	       	  /* allgemeiner Fehlercode (nicht     */
												/* benutzt)                          */
#define SPS_EQUAL				0             /* Rueckgabe Vergleich: Werte sind   */
												/* gleich                            */
#define SPS_LESS				1             /* Rueckgabe Vergleich: erster Wert  */
												/* ist kleiner als der zweite        */
#define SPS_GREATER				2             /* Rueckgabe Vergleich: erster Wert  */
												/* ist groesser als der zweite       */
#define SPS_ERR_VERSION     	-2			  /* Version von SPS mit dem des SHM   */
#define SPS_ERR_WRONG_PARAM 	-3			  /* Uebergabeparameter sind nicht     */
												/* korrekt                           */
#define SPS_ERR_MEMORY			-4			  /* Speicherfehler, konnte nicht allo-*/
												/* kieren                            */
#define SPS_ERR_SHM_OPEN  	    -5		      /* shared memory konnte nicht geoef- */
												/* fnet werden                       */
#define SPS_ERR_SHM_CREATE 		-6	          /* shared memory konnte nicht er-    */
												/* zeugt werden                      */
#define SPS_ERR_SHM_ACCESS 		-7			  /* Fehler beim Zugriff auf shared    */
												/* memory                            */
#define SPS_ERR_SHM_CLOSED 		-8			  /* Kein Zugriff auf SHM              */
#define SPS_ERR_MP_BUSY    		-9			  /* Meldepunkt wird bereits bearbeitet*/
#define SPS_ERR_NOT_INITIALIZED -10			  /* Kein SPS Init erfolgt             */
#define SPS_ERR_INITIALIZED 	-11			  /* SPS Init erfolgt zum wiederholten */
												/* Male                              */
#define SPS_ERR_PARAM_FILE 		-12			  /* Fehler in der Parameterdatei oder */
												/* Datei nicht gefunden              */
#define SPS_ERR_COMLIB 			-13			  /* Kommunikationsbibliothek nicht    */
												/* gefunden oder Zuweisung der       */
												/* Zeiger auf die Kommunikations-    */
												/* funktionen nicht moeglich         */
#define SPS_ERR_COM_OPEN 		-14			  /* Fehler beim Oeffnen der Kom.      */
												/* Verbindung                        */
#define SPS_ERR_COM_SEND 		-15			  /* Fehler beim Senden                */
#define SPS_ERR_COM_RECV		-16			  /* Fehler beim Empfangen             */
#define SPS_ERR_COM_CLOSE		-17 		  /* Fehler beim Beenden der Kom.      */
												/* Verbindung                        */
#define SPS_ERR_MSG_FORMAT 		-20			  /* Meldungsformat nicht korrekt      */
#define SPS_ERR_MP_NOT_FOUND   	-21		   	  /* Meldepunktindex konnte nicht      */
												/* gefunden werden, bzw. gehoert     */
												/* nicht zum aktuellen Prozess       */
#define SPS_ERR_INCOMPLETE_RCV 	-22			  /* Meldung wurde nicht vollstaendig  */
												/* empfangen                         */

#define SPS_ERR_LOG_FILE       	-23			  /* Fehler beim oeffnen der Logdatei  */
#define SPS_ERR_REQ_REPEAT     	-24			  /* Timeout Meldung wurde wiederholt  */
#define SPS_ERR_HOSTNAME       	-25			  /* hostname konnte nicht bestimmt    */
												/* werden oder fehlt im sps.ini file */
#define SPS_ERR_NOSERVER        -26			  /* rpc-server not found              */
#define SPS_ERR_COM_INIT 		-27			  /* Fehler beim Initialisieren der Kom*/
												/* Verbindung                        */
#define SPS_ERR_MSG_IGNORED     -28			  /*  Meldung Empfangen wird aber      */
												/*  ignoriert (PLC Warmfahrprogramm) */
#define SPS_ERR_AUTO_RECONNECT  -29			  /* keine Meldung geliefert da        */
												/*  automatischer reconnect erfolgte */
#define SPS_HOST_NAME			"spsd"
#define SPS_LOG_PREFIX			"spsd_log_"

/*--- Typendefinitionen -----------------------------------------------------*/
#ifndef SPS_DCE
	typedef char   SPS_msg_t[SPS_MSG_LEN];	  /* SPS-Message                       */
	typedef char   SPS_sr_t[SPS_KENN_LEN];	  /* Rechnerkennung                    */
	typedef char   SPS_gr_t[SPS_KENN_LEN];	  /* Gruppenkennung (UST:SPS, RFZ,...) */
	typedef char   SPS_ms_t[SPS_KENN_LEN];	  /* Meldestellenkennung               */
	typedef char   SPS_ln_t[SPS_KENN_LEN];	  /* Laufnummer                        */
	typedef char   SPS_comtpy_t[SPS_COMTYP_LEN];
	/*  Kommunikationsproduktkennung */
	typedef char   SPS_ms_help_t[SPS_HELPTXT_LEN]; /* Meldestellen Help Text    */
	typedef char   SPS_user_str_t[SPS_USERSTR_LEN]; /* User-String              */


	typedef long SPS_int_t;


#endif // !SPS_DCE


/* Handle Struktur */
#if !defined(IDL_COMPILER)
typedef struct SPS_hndl {
	/* vorher: void	    *com_des; */
	VOTS_lineDes_typ    *com_des;	/* Deskriptor fuer Kommunikation     */
								/* z.B. VOTS, TCP, ...               */
	SPS_int_t            line_idx;	/* Index der Verbindungsline         */
	SPS_int_t            line_rcvFlag;/* Status der empfangenen Meldung  */
	char   com_typ[SPS_COMTYP_LEN]; /* Kommunikationsproduktkennung      */
	/* SCF steht fuer Sps Communiction Function war noetig 		     */
	/* wg exit function und C++ - Compiler				     */
	/* vorher: SBI_callFunction_typ SCFstart;  */
	VOTS_int_typ(*SCFstart)(VOTS_lineDes_typ **, VOTS_int_typ);
	/* Start - Funktion, d.h. Initiali-  */
					/* sierung, wobei die Parameter aus  */
					/* einer Datei gelesen werden        */
	void *start_fhndl;		/* Funktionshandle                   */
	/* vorher: SBI_callFunction_typ SCFopen; */
	VOTS_int_typ(*SCFopen)(VOTS_lineDes_typ *);
	/* Open - Funktion                   */
	void *open_fhndl;		/* Funktionshandle                   */
	/* vorher: SBI_callFunction_typ SCFsend; */
	VOTS_int_typ(*SCFsend)(VOTS_lineDes_typ *, VOTS_msg_typ *, VOTS_int_typ);
	/* Send - Funktion                   */
	void *send_fhndl;		/* Funktionshandle                   */
	/* vorher: SBI_callFunction_typ SCFreceive; */
	//VOTS_int_typ(*SCFreceive)(VOTS_lineDes_typ *, VOTS_int_typ *, VOTS_msg_typ *, VOTS_timeval_typ *, VOTS_int_typ *);
	/* Receive - Funktion                */
	void *receive_fhndl;		/* Funktionshandle                   */
	/* vorher: SBI_callFunction_typ SCFreconnect; */
	VOTS_int_typ(*SCFreconnect)(VOTS_lineDes_typ *);
	/* Reconnect - Funktion              */
	void *reconnect_fhndl;		/* Funktionshandle                   */
	/* vorher: SBI_callFunction_typ SCFclose; */
	VOTS_int_typ(*SCFclose)(VOTS_lineDes_typ *);
	/* Close - Funktion                  */
	void *close_fhndl;		/* Funktionshandle                   */
	/* vorher: SBI_callFunction_typ SCFdelete;  */
	VOTS_int_typ(*SCFdelete)(VOTS_lineDes_typ **);
	/* Delete - Funktion                 */
	void *delete_fhndl;		/* Funktionshandle                   */

#ifdef SPS_CALLSHARE 
	SBI_callFunction_typ SCFexit;	/* Exit - Handler - Funktion         */
	void *exit_fhndl;		/* Funktionshandle                   */
	SBI_callFunction_typ SCFwakeUp;	/* Wakeup - Handler - Funktion       */
	void *wakeUp_fhndl;		/* Funktionshandle                   */
	SBI_callFunction_typ SCFwakeClose;/* Wakeup - Handler - Funktion     */
	void *wakeClose_fhndl;		/* Funktionshandle                   */
#else
		/* vorher: void(* SCFexit)();	*/
	void(*SCFexit)(VOTS_lineDes_typ **);
	/* Exit - Handler - Funktion         */
	void *exit_fhndl;		/* Funktionshandle                   */
	/*vorher: SBI_callFunction_typ SCFwakeUp;   */
	VOTS_int_typ(*SCFwakeUp)(VOTS_int_typ);
	/* Wakeup - Handler - Funktion       */
	void *wakeUp_fhndl;		/* Funktionshandle                   */
	void(*SCFwakeClose)();         /* Wakeup - Handler - Funktion       */
	void *wakeClose_fhndl;		/* Funktionshandle                   */
#endif /* SPS_CALLSHARE */

	SBI_shmHandle_typ    shm_des;   /* Deskriptor fuer SPS Shm           */
	//SPS_gsec_typ         sps_ptr;   /* Pointer auf SPS Struktur          */
	//SPS_int_t	     mp_start;	/* kleinster Meldepunktindex         */
	//SPS_int_t 	     mp_end;	/* groesster Meldepunktindex         */
	//SPS_int_t	     rcon_cnt;	/* Timeoutzaehler fuer Reconnect     */
} SPS_hndl_t;



#endif /* IDL_COMPILER */

#if defined(__cplusplus)
}
#endif

#endif /* SPS_IF_H */
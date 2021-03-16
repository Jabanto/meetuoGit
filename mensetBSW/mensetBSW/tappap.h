#pragma once
#include "sbi_if.h"
#include "mfc_if.h"
#include "lm_if.h"

/*-----------Descriptor for TAPPap....function------------*/

typedef struct tapp_app {

	MFC_modul_nr_t		subProjekt;
	LM_ap_t				*ap;
	MFC_updMask_t		apUpdMsk;		// for LM_apUpdp at end of TAPP_selecWork
	SBI_bool_t			newRequest;		// Set by TAPPchkNewRequest rcvMsgSeqNum  /= preMsg
	SBI_bool_t			noRead;			// Set by TAPPcheckScanner
	MFC_timeVal_t		*timeStart;		// set by TAPP_selectwork start of processing
	MFC_timeVal_t		timeStartProc;	// Set by TAPP_selectwork start of processing
	MFC_updMask_t		tuUdpMsk;		// For TU_upd in TCO_bookTu
	MFC_error_t			prevTuError;	/*Filled initial by TAPPprepare after 1st TU_getNoLock for 
										//use TAPPdoTuUdp to call of CMFC_udpTuError */
	SPS_hndl_t			*spsHndl;		
	SBI_bool_t			async;			// FALSE für receive von S%, TRUE wenn asysnchrone Bearbeitung
	SBI_int32_t			apId0x;			// AP als sscanf %x --> switches auf apId0x möglich!
	//Conf::Configuration	*conf;			// Additionalconfiguration handler

}TAPP_app_t;


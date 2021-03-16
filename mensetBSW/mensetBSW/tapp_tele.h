#pragma once

#include "sbi_if.h"
#include "sps_if.h"
#include "lm_def.h"
#include "abl_typ.h"
#include "SBI_dce.h"

#define TAPP_TELEK_LEN_1		2		//Telegrammkennung Header
										// Quelle, Ziel
#define TAPP_MS_LEN				3		//Header Meldestelle
#define TAPP_MS_LEN_1			2		//Header Meldestelle
#define TAPP_LN_LEN_1			12		//Header Laufnummer

#define TAPP_HVO_LEN			3		//Laenge Hvo-Information
#define TAPP_ELEMENT_LEN		3		//LAenge Element-Information
#define TAPP_STOER_INFO_LEN		2		//Laenge Stoerinformation +1
#define TAPP_STAU_INFO_LEN		4		//Lange Stauinformation +1
#define TAPP_KENNUNG_LEN		3		// Laenge Kennungs-Feldö

#define TAPP_TU_LENGTH_LEN			5			// Laenge TU-Laenge + 1 
#define TAPP_TU_WIDTH_LEN			5			// Länge TU-Breite + 1
#define TAPP_TU_HEIGHT_LEN			5			// Länge tu-Höhe +1
#define TAPP_TU_WEIGHT_LEN			7			// Länge tu-Gewicht +1
#define TAPP_TU_WEIGHT_LEN_SICK		8			// Länge tu-Gewicht + 1 Sick Waage
#define TAPP_SC_WEIGHT_IDX_LEN		11			// Länge Gewichtsindex in Waage
#define TAPP_TU_KK_ERR_LEN			5			// Länge konturenfehler + 1

#if !defined(DAPP_TELE_H)
// defines für die Arrays der uni-print-message                              -/
#define TAPP_NUM_PRINTER_MAX   4
#define TAPP_PRINT_LABELSEQUENZ_LEN  2
#define TAPP_PRINT_CONTROLLABEL_LEN  20
#define TAPP_PRINT_CHECKBARCODE_LEN  2
#define TAPP_PRINT_HEIGHT_LEN        4
#endif

#define TAPP_MAX_HVO_ANZ		50


#define TAPP_EVENTIDENT_LEN           5			// Laenge Event Identifier           -/
#define TAPP_EXTERNALSIGNAL_ANZ       25		// Anzahl Event´s                    -/


#define TAPP_UNI_TU_ANZ			LM_AP_MAX_TU_ANZ
#define TAPP_SL_STATE_LEN       17				 // Laenge shipping lane state 16 + 1   (16SL) -/

#define MFCI_TRACK_CODE_LEN		3

// defines für die Arrays der crn-order-message
#define TAPP_KOORD_LEN			3				// Anzahl TU on a lam of a crane


typedef struct tapp_header_msg {

	SBI_char_t hdQuelle [TAPP_TELEK_LEN_1];		// Header Quelle
	SBI_char_t hdZiel   [TAPP_TELEK_LEN_1];		// Header Ziel
	SBI_char_t hdMs		[TAPP_MS_LEN_1];		// Header Meldestelle
	SBI_char_t hdLn		[TAPP_LN_LEN_1];		//Header Laufnummer

}TAPP_header_msg_t;

typedef SBI_char_t			TAPP_tu_id_t[MFCI_TU_ID_LEN_MSG - 2];
typedef SBI_char_t			TAPP_rf_id_t[MFCI_TU_ID_LEN - 1];		// Prinzipell keine Seitenkennung
typedef SBI_char_t			TAPP_tote_id_t[MFCI_TOTE_ID_LEN_MSG];	//MFCI_TU_ID_LEN	

//Definitionen fuer die Orientierung einer TU anhand des Labels



//------------ Spezial-Felder für Messages OPM ---------------------------------/

typedef SBI_char_t TAPP_sl_state_t[TAPP_SL_STATE_LEN - 1];


typedef struct ats_dim {
	SBI_char_t              lengthSeperator;                    // L                  -/
	SBI_char_t              caseLength[TAPP_TU_LENGTH_LEN - 1];  // llll               -/
	SBI_char_t              widthSeperator;                     // W                  -/
	SBI_char_t              caseWidth[TAPP_TU_WIDTH_LEN - 1];    // wwww               -/
	SBI_char_t              heightSeperator;                    // H                  -/
	SBI_char_t              caseHeight[TAPP_TU_HEIGHT_LEN - 1];  // hhhh               -/
} TAPP_ats_dim_t;


//--Info-Teil der Message

typedef SBI_char_t TAPP_hvo_t[TAPP_HVO_LEN - 1];	//Hco-Nummer vom SPS

typedef struct tapp_pos_msg {

	TAPP_hvo_t hvo;									//HVO nummer von SPS
	SBI_char_t elem[TAPP_ELEMENT_LEN - 1];			//Element-Nummer von SPS
}TAPP_pos_msg_t;

typedef struct tapp_occ_msg
{
	SBI_char_t status;								// s Status (E,O- V.L)
	SBI_char_t filler;								// Filler
}TAPP_occ_msg_t;


//------Steuer-Teil der Message-------
typedef struct tapp_ctrl_msg {

	TAPP_occ_msg_t		occ;						   //s Occupation block
	SBI_char_t			dest[MFCI_TRACK_CODE_LEN - 1]; //dd transportrichtungskennung
	SBI_char_t			kenn[TAPP_KENNUNG_LEN - 1];

}TAPP_ctrl_msg_t;

typedef struct tapp_info_msg {

	TAPP_pos_msg_t	pos;							// hhnn
	SBI_char_t		stoer[TAPP_STOER_INFO_LEN - 1];	// @ stoerung-Informationen
	SBI_char_t		stau[TAPP_STAU_INFO_LEN - 1];	// @@@ Stauinformationen

}TAPP_info_msg_t;

typedef struct tapp_order_msg {                     // oOOOOOOOOOO         -/
	SBI_char_t              fillerOrderNr;            // o                   -/
	SBI_char_t              orderNr[MFCI_ID_LEN - 2];   // OOOOOOOOOO          -/
} TAPP_order_msg_t;

//--------SSCC-Teil der Message

typedef struct tapp_sscc_msg {

	SBI_char_t		scStatus;							//Scannerstatus (P,*,..)
	SBI_char_t		ssccId[MFCI_SSCC_ID_LEN_MSG - 1];	// c SSCC-Identnumer

}TAPP_sscc_msg_t;


//------------ SSCC-Teil der Message -------------------------------------------/
typedef struct tapp_sscc_short_msg {
	SBI_char_t       scStatus;                    // l Scannerstatus (P,*,..)   -/
	SBI_char_t       ssccId[MFCI_SSCC_ID_LEN_MSG - 1];  // c SSCC 20 Stellen     !!!! -/
} TAPP_sscc_short_msg_t;

//---------Wrapper-Parameter

typedef struct TAPP_wrapParam_msg {
	SBI_char_t   stretchStart[2];// Folienspannung Start  (0-31) 
	SBI_char_t   stretchUp[2];// Folienspannung oben   (0-31)
	SBI_char_t   stretchCenter[2];// Folienspannung mitte  (0-31)
	SBI_char_t   stretchDown[2];// Folienspannung unten  (0-31)
	SBI_char_t   wrapHeadNum[2];// Anzahl Kopfwicklungen (1-15)
	SBI_char_t   wrapFootNum[2];// Anzahl Fußwicklungen  (1-15)
	SBI_char_t   ringSpeedLow[3];// langsame Geschwindigkeit (LS), Ring (4-8) [%]
	SBI_char_t   ringSpeedMedium[3];// mittlere Geschwindigkeit (MS), Ring (10-40) [%]
	SBI_char_t   ringSpeedHigh[3];// schnelle Geschwindigkeit (HS), Ring (55-100) [%]
	SBI_char_t   sfSpeedLow[3];// langsame Geschwindigkeit (LS), SF   (6-12) [%]
	SBI_char_t   sfSpeedUp[3];// mittlere Geschwindigkeit heben (MS up) / Wickelgeschw., SF    (12-55) [%]
	SBI_char_t   sfSpeedDown[3];// mittlere Geschwindigkeit senken (MS down) / Wickelgeschw., SF (12-55) [%]
	SBI_char_t   sfSpeedHigh[3];// schnelle Geschwindigkeit (HS), SF   (50-100) [%]
	SBI_char_t   reserve1[4];
	SBI_char_t   offPal[4];// Offset Oberkante Palette (Heben über Mitte Folienrolle, Index:S76) [Schritte] 
	SBI_char_t   sfLower[4];// SF senken (filmflag) / Einwickeln Folienfahne  [Schritte]
	SBI_char_t   sfStop[4];// SF stopp vor Oberkante Palette beim Hochwickeln (SFB) [Schritte]
	SBI_char_t   sfHeave[4];// SF heben vor Abschneiden obere Endlage  [Schritte]
	SBI_char_t   foilWeldTime[4];// Zeit Folienschweißen                    [ms]
	SBI_char_t   foilEndNum[4];// Zähler "Folie fast zu Ende", Übertragung an Ring-SPS
	SBI_char_t   ringSpeedSwitch[4];// Geschw.-umsch. MS -> HS Ring, 1-4 Umdr., Dauer DBW 14  (0-1424) [Schritte]
	SBI_char_t   wrapWidth[4];// Wickelbreite bei Teilwicklung [Schritte]
	SBI_char_t   reserve2[4];
	SBI_char_t   preStretchLev;// 1     Prestretch Level (optional)   (0-7) 
	SBI_char_t   wrapPrgmId[3];// Wicklerprogramm-Id
} TAPP_wrapParam_t;

#define TAPP_WRAP_PARAM_LEN SBImaxOf(sizeof(TAPP_wrapParam_t)+1, sizeof(ABL_info_t)+1)

typedef union TAPP_wrapParam_union{

	SBI_char_t				rawWrapParam[TAPP_WRAP_PARAM_LEN - 1];
	TAPP_wrapParam_t		wrapParam;

}TAPP_wrapParam_tu;

// Definition of Haloila

typedef struct TAPP_wrappStateHaloila_msg {
	//****siganle vom Wrapper nach den verheiraten ****
	SBI_char_t		sysPalIsFull;		//Systempallet full (Marriage onto system pallet or not )			| Auslagermeldepunkt
	SBI_char_t		pakCorIsEmpty;		// PacCorner=Pick container Empty (Marriage onto fork of wrapper)	| Auslagermeldepunkt
	
	//****Signale vom wrapper nach dem verheiraten ****
	SBI_char_t		sysPalEmpty;		//Systempallet empty (Physisch)										| Einlagermeldepunkt
	SBI_char_t		sysPalIsBad;		//Bad System Pallet (failure (Datentechnisch|CPs))					| Einlagermeldepunkt
	SBI_char_t		pakCorCnvBook;		//Paökcorner (wrap programm xx and book onto conveyor)				| Einlagermeldepunkt
	SBI_char_t		pakCorisBad;		//Bad Packcorner=Pick container (failure (Datentechnisch|CPS))		| Einlagermeldepunkt

}TAPP_wrapStateHaloila_t;


#define TAPP_WRAP_STATE_HALOILA_LEN  sizeof(TAPP_wrapStateHaloila_t)+1

typedef union TAPP_wrapStateHaloila_union {

	SBI_char_t					rawWrapState[TAPP_WRAP_STATE_HALOILA_LEN - 1];
	TAPP_wrapStateHaloila_t		wrapState;

}TAPP_wrapStateHaloila_tu;

typedef struct TAPP_wrapParamHaloila_msg {
	SBI_char_t   totalHeight[4];		// Oberkante Palette
	SBI_char_t   wrapFoilStart[4];		// Offset für Wickelbeginn (Wickeln beginnen (totalHeight-offSetFoil)
	SBI_char_t   wrapFoilStop[4];		// Offset für Wickelende   (Wickeln ende (totalHeight-(offSetFoil+Folienbreite))
	SBI_char_t   wrapPrgmId[2];			// Wicklerprogramm-Id
} TAPP_wrapParamHaloila_t;

#define TAPP_WRAP_PARAM_HALOILA_LEN  SBImaxOf( sizeof(TAPP_wrapParamHaloila_t)+1, sizeof (ABL_info_t)+1 )

typedef union TAPP_wrapParamHaloila_union {
	SBI_char_t                rawWrapParam[TAPP_WRAP_PARAM_HALOILA_LEN - 1];
	TAPP_wrapParamHaloila_t   wrapParam;
}TAPP_wrapParamHaloila_tu;


//------------ RFID-Teil der Message -------------------------------------------/
typedef struct tapp_rfid_tu_msg {
	SBI_char_t       scStatus;                     // l Scannerstatus (P,*,..)   -/
	TAPP_rf_id_t     tuId;                         // p RFID-Identnummer         -/
	SBI_char_t       filler;                       //   Filler                   -/
} TAPP_rfid_tu_msg_t;
//--END------- RFID-Teil der Message -------------------------------------------/

//------------ Tote-Teil der Message -------------------------------------------/
typedef struct tapp_toteid_tu_msg {
	SBI_char_t       scStatus;                     // l Scannerstatus (P,*,..)   -/
	TAPP_tote_id_t   tuId;                         // p Tote-Identnummer         -/
	//SBI_char_t       filler;                     //   Filler                   -/
} tapp_toteid_tu_msg_t;
//--END------- Tote-Teil der Message -------------------------------------------/




//--------TU_Teil der Message

typedef struct tapp_tu_msg {

	SBI_char_t		scStatus;					//Scannerstatus (P, *,...)
	TAPP_tu_id_t	tuId;						//TU-Identnummer	
												//Orientierungs der TU
												// 0 = undefiniert
												// 1= left links
												// 2= fron vorne
												// 3= right rechts
												// 4= rear hinten
	SBI_char_t		side;
	SBI_char_t		filler;						// Filler
}TAPP_tu_msg_t;



//---------Ziel-Verfolgungs-Teil der Message

typedef struct tapp_zvf_msg {

	TAPP_ctrl_msg_t		ctrl;				// s_ddtt
	TAPP_tu_msg_t		tu;					// lpppppppppppp_...

}TAPP_zvf_msg_t;

typedef struct tapp_bc_rfid_msg {

	TAPP_ctrl_msg_t		ctrl;				// s_ddtt
	TAPP_tu_msg_t		barcode;			// lpppppppppppp_
	TAPP_rfid_tu_msg_t	rfId;				// lpppppppppppppppppppppppp_

}TAPP_bc_rfid_msg_t;

typedef struct tapp_zvf_tote_msg {

	TAPP_ctrl_msg_t			ctrl;				// s_ddtt
	tapp_toteid_tu_msg_t	tu;					// lpppppppppppppppppppp

}tapp_zvf_tote_msg_t;


//--------Konturenfehler der Message

typedef struct tapp_kontur_msg {

	SBI_char_t		kontErr[TAPP_TU_KK_ERR_LEN - 1];	//Konturenfehler
	SBI_char_t		height[TAPP_TU_HEIGHT_LEN - 1];		// Höhe
	SBI_char_t		weight[TAPP_TU_WEIGHT_LEN - 1];		// Gewicht

}TAPP_kk_msg_t;


typedef struct tapp_kontur_sick1_msg {
	SBI_char_t   kontErr[TAPP_TU_KK_ERR_LEN - 1];      // Konturenfehler          -/
	SBI_char_t   height[TAPP_TU_HEIGHT_LEN - 1];      // Hoehe                   -/
	SBI_char_t   scaleState;                          // Waagenstatus P,*,&,#,   -/
	SBI_char_t   weight[TAPP_TU_WEIGHT_LEN_SICK - 1]; // Gewicht                 -/
	SBI_char_t   filler1;                             // Filler '_'              -/
	SBI_char_t   filler2;                             // Filler '_'              -/
} TAPP_kk_sick1_msg_t;

typedef struct tapp_kontur_sick2_msg {
	SBI_char_t   kontErr[TAPP_TU_KK_ERR_LEN - 1];      // Konturenfehler          -/
	SBI_char_t   height[TAPP_TU_HEIGHT_LEN - 1];      // Hoehe                   -/
	SBI_char_t   scaleState;                          // Waagenstatus P,*,&,#,   -/
	SBI_char_t   weight[TAPP_TU_WEIGHT_LEN_SICK - 1]; // Gewicht                 -/
	SBI_char_t   weightUnit;                          // k-kg, g-gramm,...       -/
	SBI_char_t   filler1;                             // Filler ';'              -/
	SBI_char_t   weightIdx[TAPP_SC_WEIGHT_IDX_LEN - 1]; // Weight idx in sc memory -/
	SBI_char_t   filler2;                             // Filler '_'              -/
	SBI_char_t   filler3;                             // Filler '_'              -/
} TAPP_kk_sick2_msg_t;

// Definition Strewi
#define TAPP_WRAP_STREWI_SURFACE_SIZE   25
#define TAPP_WRAP_STREWI_AREAUSAGE_LEN  2

typedef struct TAPP_wrapSurfaceStrewi_msg {
	SBI_char_t   areaUsage[TAPP_WRAP_STREWI_AREAUSAGE_LEN];  // Flächennutzungsgrad in 100mm
} TAPP_wrapSurfaceStrewi_t;

typedef struct TAPP_wrapParamStrewi_msg {
	SBI_char_t                 startPrgId;
	SBI_char_t                 wrapPrgId[2];  // Wicklerprogrammnummer
	SBI_char_t                 startLength;
	SBI_char_t                 length[TAPP_TU_LENGTH_LEN - 1];
	SBI_char_t                 startWidth;
	SBI_char_t                 width[TAPP_TU_WIDTH_LEN - 1];
	SBI_char_t                 startHeight;
	SBI_char_t                 height[TAPP_TU_HEIGHT_LEN - 1];
	SBI_char_t                 startWeight;
	SBI_char_t                 weight[TAPP_TU_WEIGHT_LEN - 1];
	SBI_char_t                 startSurface;
	TAPP_wrapSurfaceStrewi_t   surface[TAPP_WRAP_STREWI_SURFACE_SIZE];   // Flächennutzungsgrad in 100mm Höhenraster
	SBI_char_t                 terminator;    // end of message               -/
} TAPP_wrapParamStrewi_t;

#define TAPP_WRAP_PARAM_STREWI_LEN  sizeof(TAPP_wrapParamStrewi_t) + 1

typedef union TAPP_wrapParamStrewi_union {
	SBI_char_t                rawWrapParam[TAPP_WRAP_PARAM_STREWI_LEN - 1];
	TAPP_wrapParamStrewi_t    wrapParam;
} TAPP_wrapParamStrewi_tu;


// Definition Movitec
typedef struct TAPP_wrapStateMovitec_msg {
	// ***** Signale vom Wraper nach dem verheiraten *****
	SBI_char_t   sysPalIsFull;		// Systempallet full (Marrige onto system pallet or not) | Auslagermeldepunkt
	SBI_char_t   pakCorIsEmpty;		// Packcorner empty (Marrige onto fork of wrapper)       | Auslagermeldepunkt
	// ***** Signale vom Wraper vor dem verheiraten *****
	SBI_char_t   sysPalEmpty;		// System Pallet empty (Physisch)                        | Einlagermeldepunkt
	SBI_char_t   sysPalIsBad;		// Bad System Pallet (failure (Datentechnisch|CPS))      | Einlagermeldepunkt
	SBI_char_t   pakCorCnvBook;		// PackCorner (wrap program xx and book onto conveyor)   | Einlagermeldepunkt | Dieses bit wird gebraucht für ATS Paletten
	SBI_char_t   pakCorIsBad;		// Bad PackCorner (failure (Datentechnisch|CPS))         | Einlagermeldepunkt
} TAPP_wrapStateMovitec_t;

#define TAPP_WRAP_STATE_MOVITEC_LEN  sizeof(TAPP_wrapStateMovitec_t)+1

typedef union TAPP_wrapStateMovitec_union {
	SBI_char_t                rawWrapState[TAPP_WRAP_STATE_MOVITEC_LEN - 1];
	TAPP_wrapStateMovitec_t   wrapState;
} TAPP_wrapStateMovitec_tu;

typedef struct TAPP_wrapParamMovitec_msg {
	SBI_char_t   totalHeight[4];			// Oberkante Palette
	SBI_char_t   wrapFoilStart[4];			// Offset für Wickelbeginn (Wickeln beginnen (totalHeight-offSetFoil)
	SBI_char_t   wrapFoilStop[4];			// Offset für Wickelende   (Wickeln ende (totalHeight-(offSetFoil+Folienbreite))
	SBI_char_t   wrapPrgmId[2];				// Wicklerprogramm-Id
} TAPP_wrapParamMovitec_t;

#define TAPP_WRAP_PARAM_MOVITEC_LEN  SBImaxOf( sizeof(TAPP_wrapParamMovitec_t)+1, sizeof (ABL_info_t)+1 )

typedef union TAPP_wrapParamMovitec_union {
	SBI_char_t                rawWrapParam[TAPP_WRAP_PARAM_MOVITEC_LEN - 1];
	TAPP_wrapParamMovitec_t   wrapParam;
} TAPP_wrapParamMovitec_tu;


// Definition Strewi V2
typedef struct TAPP_wrapParamStrewiV2_msg {
	SBI_char_t                 startPrgId;
	SBI_char_t                 wrapPrgId[2];                            // Wicklerprogrammnummer
	SBI_char_t                 startLength;
	SBI_char_t                 length[TAPP_TU_LENGTH_LEN - 1];            // Länge[mm]
	SBI_char_t                 startWidth;
	SBI_char_t                 width[TAPP_TU_WIDTH_LEN - 1];             // Breite[mm]
	SBI_char_t                 startHeight;
	SBI_char_t                 height[TAPP_TU_HEIGHT_LEN - 1];            // Höhe[mm]
	SBI_char_t                 startWeight;
	SBI_char_t                 weight[TAPP_TU_WEIGHT_LEN - 1];            // Gewicht[Kg]
	SBI_char_t                 startOffsetTopEdge;
	SBI_char_t                 offsetTopEdge[TAPP_TU_HEIGHT_LEN - 1];     // Start offset für Wicklung[mm]
	SBI_char_t                 startStripWidth;
	SBI_char_t                 stripWidth[TAPP_TU_HEIGHT_LEN - 1];        // Wickelhöhe ab start offset für Wicklung [mm]
	SBI_char_t                 startSurface;
	TAPP_wrapSurfaceStrewi_t   surface[TAPP_WRAP_STREWI_SURFACE_SIZE];  // Flächennutzungsgrad in 100mm Höhenraster
	SBI_char_t                 terminator;    // end of message               -/
} TAPP_wrapParamStrewiV2_t;

#define TAPP_WRAP_PARAM_STREWIV2_LEN  sizeof(TAPP_wrapParamStrewiV2_t) + 1

typedef union TAPP_wrapParamStrewiV2_union {
	SBI_char_t                rawWrapParam[TAPP_WRAP_PARAM_STREWIV2_LEN - 1];
	TAPP_wrapParamStrewiV2_t  wrapParam;
} TAPP_wrapParamStrewiV2_tu;



// Definition Strewi V3
typedef struct TAPP_wrapParamStrewiV3_msg {
	SBI_char_t                 startPrgId;
	SBI_char_t                 wrapPrgId[2];                            // Wicklerprogrammnummer
	SBI_char_t                 startLength;
	SBI_char_t                 length[TAPP_TU_LENGTH_LEN - 1];            // Länge[mm]
	SBI_char_t                 startWidth;
	SBI_char_t                 width[TAPP_TU_WIDTH_LEN - 1];             // Breite[mm]
	SBI_char_t                 startHeight;
	SBI_char_t                 height[TAPP_TU_HEIGHT_LEN - 1];            // Höhe[mm]
	SBI_char_t                 startWeight;
	SBI_char_t                 weight[TAPP_TU_WEIGHT_LEN - 1];            // Gewicht[Kg]
	SBI_char_t                 startHeightFirstPal;
	SBI_char_t                 heightFirstPal[TAPP_TU_HEIGHT_LEN - 1];    // Höhe[mm] der ersten Doppelstockpalette
	SBI_char_t                 startOffsetTopEdge;
	SBI_char_t                 offsetTopEdge[TAPP_TU_HEIGHT_LEN - 1];     // Start offset für Wicklung[mm]
	SBI_char_t                 startStripWidth;
	SBI_char_t                 stripWidth[TAPP_TU_HEIGHT_LEN - 1];        // Wickelhöhe ab start offset für Wicklung [mm]
	SBI_char_t                 startSurface;
	TAPP_wrapSurfaceStrewi_t   surface[TAPP_WRAP_STREWI_SURFACE_SIZE];  // Flächennutzungsgrad in 100mm Höhenraster
	SBI_char_t                 terminator;    // end of message               -/
} TAPP_wrapParamStrewiV3_t;

#define TAPP_WRAP_PARAM_STREWIV3_LEN  sizeof(TAPP_wrapParamStrewiV3_t) + 1

typedef union TAPP_wrapParamStrewiV3_union {
	SBI_char_t                rawWrapParam[TAPP_WRAP_PARAM_STREWIV3_LEN - 1];
	TAPP_wrapParamStrewiV3_t  wrapParam;
} TAPP_wrapParamStrewiV3_tu;




//---TODO---- Location prüfen ------

typedef struct tapp_ats_palletStackInfo_msg_DEMO {

	TAPP_header_msg_t			header;				// hhnn@@@@
	SBI_char_t					atsValue;			// Demo value 	

}TAPP_ats_palletStackInfo_msg_t;

typedef struct tapp_ats_packageInfo_msg_DEMO {

	TAPP_header_msg_t			header;				// hhnn@@@@
	SBI_char_t					atsValue;			// Demo value
}TAPP_ats_packageInfo_msg_t;



// Format 83 - ATS Stacker Status
// .........1.........2.........3.........4.........5.........6.........7.........8......
// 12345678901234567890123456789012345678901234567890123456789012345678901234567890123456
// qqzzmmllhhnn@@@@s_ddttlpppppppppppppppppppp_s_ddttlqqqqqqqqqqqqqqqqqqqqoOOOOOOOOOO_EE_
typedef struct tapp_ATS_msg_83 {
	TAPP_header_msg_t      header;                 // qqzzmmll                                                -/
	TAPP_info_msg_t        info;                   // hhnn@@@@                                                -/
	tapp_zvf_tote_msg_t    zvf[2];                 // s_ddttlpppppppppppppppppppp_s_ddttlqqqqqqqqqqqqqqqqqqqq -/
	TAPP_order_msg_t       order;                  // oOOOOOOOOOO                                             -/
	SBI_char_t             delimiter;              // _                                                       -/
	SBI_char_t             errorFlag[2];           // EE                                                      -/
	SBI_char_t             terminator;             // _                                                       -/
} TAPP_ats_msg_83_t;

// Format 84 - ATS Stacker input
// .........1.........2.........3.........4.........5.........6.........7.........8.........9.........0........
// 123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678
// qqzzmmllhhnn@@@@s_dd_sSSpPPssslr_LllllWwwwwHhhhh_ttlppppppppppppppppppppoOOOOOOOOOO_Sa_iiiiiiiiiiiiiiiiiiii_
typedef struct tapp_ATS_msg_84 {
	TAPP_header_msg_t               header;                       // qqzzmmll                     -/
	TAPP_info_msg_t                 info;                         // hhnn@@@@                     -/
	TAPP_occ_msg_t                  occ;                          // s_                           -/
	SBI_char_t                      dest[MFCI_TRACK_CODE_LEN - 1]; // dd                           -/
	SBI_char_t                      filler;                       // _                            -/
	TAPP_ats_palletStackInfo_msg_t  stackInfo;                    // sSS                          -/
	TAPP_ats_palletStackInfo_msg_t  palletInfo;                   // pPP                          -/
	SBI_char_t                      strap;                        // s                            -/
	SBI_char_t                      toteType;                     // s                            -/
	SBI_char_t                      levelFinish;                  // s                            -/
	SBI_char_t                      supportBar;                   // l                            -/
	SBI_char_t                      reduction;                    // r                            -/
	SBI_char_t                      filler1;                      // _                            -/
	TAPP_ats_dim_t                  dimension;                    // LllllWwwwwHhhhh              -/
	SBI_char_t                      filler2;                      // _                            -/
	SBI_char_t                      kenn[TAPP_KENNUNG_LEN - 1];    // tt                           -/
	tapp_toteid_tu_msg_t            tu;                           // lpppppppppppppppppppp        -/
	TAPP_order_msg_t                order;                        // oOOOOOOOOOO                  -/
	SBI_char_t                      filler3;                      // _                            -/
	TAPP_ats_packageInfo_msg_t      packageInfo;                  // Sa_                          -/
	SBI_char_t                      infoFields[20];               // iiiiiiiiiiiiiiiiiiii         -/
	SBI_char_t                      terminator;                   // _                            -/
} TAPP_ats_msg_84_t;

/*              qqzzmmllkShhnnArt      ,ort            ,text
							  123456789,123456789012345,
06:26:17.343 R: 54MF01llF11423W-GAPC-S ,CBU:54_14.06   ,small tray is not turned@ /<
06:29:23.290 R: 54MF01llF01423W-GAPC-S ,CBU:54_14.06   ,small tray is not turned@ /<
13:50:59.701 R: 54MF01llF14117W-TO-RUN ,SLC:54_41.08   ,unloading time@ /<
13:51:07.185 R: 54MF01llF02830W-CRASH  ,RC :54_28.02   ,crash before SLC 4108 @ /<
*/
typedef struct tapp_uni_fs_msg_01{

	TAPP_header_msg_t		header;			//qqzzmmll
	SBI_char_t				kenn;			//F
	SBI_char_t				state;			//0=unlocked, 1=on, F=secondary fault
	SBI_char_t				lac[2];			//Loacl area control
	SBI_char_t				errorNum[2];	//plc error number
	SBI_char_t				type[9];		//Prodis art
	SBI_char_t				typeEnd;		//Separator
	SBI_char_t				location[19];	//PRODIS ort
	SBI_char_t				locEnd;			//, separator
	SBI_char_t				text[70];		//Prodis Info

}TAPP_uni_fs_msg_t;



typedef struct tapp_uni_state_msg_02 {

	TAPP_header_msg_t		header;			//qqzzmmll
	SBI_char_t				group[2];
	TAPP_hvo_t				hvoAllg;
	TAPP_hvo_t				hvoOth[TAPP_MAX_HVO_ANZ];
	SBI_char_t				terminator;		// end of the message

}TAPP_uni_state_msg_t;


typedef struct tapp_uni_ctrl_msg_04 {

	TAPP_header_msg_t		header;			//qqzzmmll
	SBI_char_t				area[2];
	SBI_char_t				command[2];
	SBI_char_t				leapYear;
	SBI_char_t				weekDay;
	SBI_char_t				year[4];
	SBI_char_t				month[2];
	SBI_char_t				hour[2];
	SBI_char_t				minute[2];
	SBI_char_t				second[2];
	SBI_char_t				terminator;		//end of message

}TAPP_uni_ctrl_msg_t;


typedef struct tapp_uni_prot_msg_05 {

	TAPP_header_msg_t		header;			//qqzzmmll
	SBI_char_t				logType;
	SBI_char_t				fileIdent;
	SBI_char_t				info[498];
	SBI_char_t				end;			// @ textende
	SBI_char_t				terminator;		// end of message	

}TAPP_uni_prot_msg_t;

typedef struct tapp_uni_encoder_msg_06 {

	TAPP_header_msg_t		header;		//qqzzmmll
	SBI_char_t				type;
	SBI_char_t				x[TAPP_KOORD_LEN];
	SBI_char_t				y[TAPP_KOORD_LEN];
	SBI_char_t				side;
	SBI_char_t				fork;
	SBI_char_t				filler;
	SBI_char_t				terminator;	// End of message

}TAPP_uni_encoder_msg_t;	

typedef struct tapp_uni_msg_11 {

	TAPP_header_msg_t		header;					//qqzzmmll
	TAPP_info_msg_t			info;					//hhnn@@@@
	TAPP_zvf_msg_t			zvf[TAPP_UNI_TU_ANZ];	//Mas. Anzahl Datensaetze 3
	SBI_char_t				terminator;				// end of the message

}TAPP_uni_msg_t;


//12 Msg mit einem zielverfolgungsdatensatz und Konturenkontrolle
typedef struct tapp_uni_kk_msg_12 {

	TAPP_header_msg_t		header;					//qqzzmmll
	TAPP_info_msg_t			info;					//hhnn@@@@
	TAPP_zvf_msg_t			zvf[1];					//s_ddttlpppppppppppp_...
	TAPP_kk_msg_t			kk;			
	SBI_char_t				terminator;

}TAPP_uni_kk_msg_t;


typedef struct tapp_uni_sscc_msg_13 {

	TAPP_header_msg_t		header;			//qqzzmmll
	TAPP_info_msg_t			info;			//hhnn@@@@
	TAPP_zvf_msg_t			zvf[1];			// s_ddttlpppppppppppp_...
	TAPP_sscc_msg_t			sscc;
	SBI_char_t				terminator;		//end of message

}TAPP_uni_sscc_msg_t;


// 14 Msg mit einem Zielverfolgungsdatensatz + Konturenkontrolle + TU
typedef struct tapp_tu_kk_tu_msg_14 {

	TAPP_header_msg_t		header;			//qqzzmmll
	TAPP_info_msg_t			info;			//hhnn@@@@
	TAPP_zvf_msg_t			zvf[1];			//s_ddttlpppppppppppp_...
	TAPP_kk_msg_t			kk;
	SBI_char_t				fill_1;
	SBI_char_t				fill_2;
	TAPP_tu_msg_t			tu;				// 2. TU-Satz
	SBI_char_t				terminator;		// end of the message

}TAPP_tu_kk_tu_msg_t;

// 15 Msg mit einem Belegunsstatus
typedef struct tapp_uni_occ_msg_15 {

	TAPP_header_msg_t		header;			// qqzzmmll
	TAPP_info_msg_t			info;			// hhnn@@@@
	TAPP_occ_msg_t			occ;
	SBI_char_t				terminator;		// end of the message

}TAPP_uni_occ_msg_t;


//41 Mercadona - Labelverifikation
// MSG mit einem Zielverfolgungsdatensatz + SSCC_1 + SSCC_2

typedef struct tapp_uni_sscc2_msg_41 {

	TAPP_header_msg_t		header;		//qqzzmmll
	TAPP_info_msg_t			info;		//hhnn@@@@
	TAPP_zvf_msg_t			zvf[1];		//s_ddttlpppppppppppp_...
	TAPP_sscc_msg_t			sscc[2];
	SBI_char_t				terminator;	// end of message

}TAPP_uni_sscc2_msg_t;

typedef struct tapp_SepWrap_msg_42 {

	TAPP_header_msg_t		header;		//qqzzmmll
	TAPP_info_msg_t			info;		//hhnn@@@@
	TAPP_zvf_msg_t			zvf[2];		//s_ddttlpppppppppppp_....
	TAPP_wrapParam_tu		wrapParam;	// www...www
	SBI_char_t				terminator;	//end of message

}TAPP_SepWrap_msg_t;

// Mercadona frio drucker mit Konturenmeldung in -23C
// 43 msg mit einem Zielverfolgungsdatensatz + Konturenkontrolle +  SSCC
typedef struct tapp_tu_kk_tu_msg_43 {

	TAPP_header_msg_t		header;		//qqzzmmll
	TAPP_info_msg_t			info;		//hhnn@@@@
	TAPP_zvf_msg_t			zvf[1];		//s_ddttlpppppppppppp_....
	TAPP_kk_msg_t			kk;
	SBI_char_t				fill_1;
	SBI_char_t				fill_2;
	TAPP_sscc_msg_t			sscc;		// SSCC
	SBI_char_t				terminator;	//End of the message

}TAPP_tu_kk_sscc_msg_t;

// Telegrammformat Haloila
typedef struct tapp_SepWrapHaloila_msg_44 {

	TAPP_header_msg_t			header;		//qqzzmmll
	TAPP_info_msg_t				info;		//hhnn@@@@
	TAPP_zvf_msg_t				zvf[1];		//s_ddttlpppppppppppp_...
	TAPP_wrapStateHaloila_tu	wrapState;	//www...www
	TAPP_wrapParamHaloila_tu	wrapParam;	//www...www
	SBI_char_t					terminator;


}TAPP_SepWrapHaloila_msg_t;


// Telegrammformat Strewi
typedef struct tapp_SepWrapStrewi_msg_47 {
	TAPP_header_msg_t         header;               // qqzzmmll                     -/
	TAPP_info_msg_t           info;                 // hhnn@@@@                     -/
	TAPP_zvf_msg_t            zvf[1];               // s_ddttlpppppppppppp_...      -/
	TAPP_wrapParamStrewi_tu   wrapParam1;           // www...www                    -/
	TAPP_wrapParamStrewi_tu   wrapParam2;           // www...www                    -/
	SBI_char_t                terminator;           // end of message               -/
} TAPP_SepWrapStrewi_msg_t;


// Telegrammformat Movitec
typedef struct tapp_SepWrapMovitec_msg_48 {
	TAPP_header_msg_t         header;               // qqzzmmll                     -/
	TAPP_info_msg_t           info;                 // hhnn@@@@                     -/
	TAPP_zvf_msg_t            zvf[1];               // s_ddttlpppppppppppp_...      -/
	TAPP_wrapStateMovitec_tu  wrapState;            // www...www                    -/
	TAPP_wrapParamMovitec_tu  wrapParam;            // www...www                    -/
	SBI_char_t                terminator;           // end of message               -/
} TAPP_SepWrapMovitec_msg_t;


// Telegrammformat Strewi V2
typedef struct tapp_SepWrapStrewiV2_msg_49 {
	TAPP_header_msg_t         header;               // qqzzmmll                     -/
	TAPP_info_msg_t           info;                 // hhnn@@@@                     -/
	TAPP_zvf_msg_t            zvf[1];               // s_ddttlpppppppppppp_...      -/
	TAPP_wrapParamStrewiV2_tu wrapParam1;           // www...www                    -/
	TAPP_wrapParamStrewiV2_tu wrapParam2;           // www...www                    -/
	SBI_char_t                terminator;           // end of message               -/
} TAPP_SepWrapStrewiV2_msg_t;


// Telegrammformat Strewi V3
typedef struct tapp_SepWrapStrewiV3_msg_51 {
	TAPP_header_msg_t         header;               // qqzzmmll                     -/
	TAPP_info_msg_t           info;                 // hhnn@@@@                     -/
	TAPP_zvf_msg_t            zvf[1];               // s_ddttlpppppppppppp_...      -/
	TAPP_wrapParamStrewiV3_tu wrapParam1;           // www...www                    -/
	TAPP_wrapParamStrewiV3_tu wrapParam2;           // www...www                    -/
	SBI_char_t                terminator;           // end of message               -/
} TAPP_SepWrapStrewiV3_msg_t;


// 112 Msg mit einem Zvf und Kk SICK Waage nicht geeicht                       -/
typedef struct tapp_uni_kk_sick1_msg_112 {
	TAPP_header_msg_t      header;               // qqzzmmll                     -/
	TAPP_info_msg_t        info;                 // hhnn@@@@                     -/
	TAPP_zvf_msg_t         zvf[1];               // s_ddttlpppppppppppp_...      -/
	TAPP_kk_sick1_msg_t    kk;                   // ffffhhhhlggggggg__           -/
	SBI_char_t             terminator;           // end of message               -/
} TAPP_uni_kk_sick1_msg_t;

// 212 Msg mit einem Zvf und Kk SICK Waage geeicht                             -/
typedef struct tapp_uni_kk_sick2_msg_212 {
	TAPP_header_msg_t      header;               // qqzzmmll                       -/
	TAPP_info_msg_t        info;                 // hhnn@@@@                       -/
	TAPP_zvf_msg_t         zvf[1];               // s_ddttlpppppppppppp_...        -/
	TAPP_kk_sick2_msg_t    kk;                   // ffffhhhhlgggggggu;nnnnnnnnnn__ -/
	SBI_char_t             terminator;           // end of message                 -/
} TAPP_uni_kk_sick2_msg_t;

//--END-Protocol----Message-----

//--BEGIN--- External Event MESSAGE ------------------------------------------/
#define TAPP_NUM_EVENT_SEC  3  //max. number of event sections in message
#define TAPP_EVENT_ID_LEN   4  //length of event identifier

typedef struct tapp_extEvent {
	SBI_char_t eventId[TAPP_EVENT_ID_LEN]; //identifer of event
	SBI_char_t sep;                        //separator character
	SBI_char_t eventStatus; //status of event: [0] inactiv, [1] activ, [-] ignore
	SBI_char_t filler;
} TAPP_extEvent_t;

typedef struct tapp_uni_ext_msg_50 {
	TAPP_header_msg_t   header;                  // qqzzmmll                  -/
	TAPP_info_msg_t     info;                    // hhnn@@@@                  -/
	SBI_char_t          filler;
	TAPP_extEvent_t     evt[TAPP_NUM_EVENT_SEC]; // event sections
} TAPP_uni_ext_msg_t;


// Telegrammformat Access Request
// MF611F00_<TYP:61_01.01|TSEB01A|0><TYP:61_02.02|TSEB01B|0>...<ttt:gg_hh.nn|zzzzzzz|s>_
typedef struct tapp_accessRequest_msg_71 {
	TAPP_header_msg_t       header;                    // qqzzmmll                     -/
	SBI_char_t              delimiter;                 //  _
	SBI_char_t              accessRequestStream[486];  // 18 x <TYP:61_01.01|TSEB01A   |1>
	SBI_char_t              terminator;                // end of message               -/
} TAPP_accessRequest_msg_t;


// 72 Msg with external signal data 
typedef struct externalSignal_data {
	SBI_char_t  eventIdent[TAPP_EVENTIDENT_LEN - 1];  // textual description of the event -/
	SBI_char_t  sep;                               // :  (separator character)         -/
	SBI_char_t  eventStatus;                        // 0 event is not active            -/
	//                                                 1 event is active                -/
	//                                                 - ignore event status            -/
	SBI_char_t  delimiter;                          // _ (delimiter)                    -/
} TAPP_externalSignal_data_t;

// 61MF1F010101@@@@_FA01:0_FA02:1_USV1:0_USV2:1_
typedef struct tapp_externalSignal_msg_72 {
	TAPP_header_msg_t           header;             // qqzzmmll                         -/
	TAPP_info_msg_t             info;               // hhnn@@@@                         -/
	SBI_char_t                  delimiter;          // _ (delimiter)                    -/
	TAPP_externalSignal_data_t  extSignalData[TAPP_EXTERNALSIGNAL_ANZ];  // ttttts_    * 25                  -/
} TAPP_externalSignal_msg_t;

typedef struct TAPP_stk_3tu_msg_55 {
	TAPP_header_msg_t      header;               // qqzzmmll                     -/
	TAPP_info_msg_t        info;                 // hhnn@@@@                     -/
	TAPP_zvf_msg_t         zvf[1];               // Zielverfolgungsdaten         -/
	TAPP_tu_msg_t          sc2;                  // zweiter Scanner              -/
	TAPP_zvf_msg_t         clampZvf[1];          // TU in der Klammer            -/
	SBI_char_t             terminator;           // end of message               -/
} TAPP_stk_3tu_msg_t;

// Telegrammformat Segment Füllgrad
//          tappSegFillGradeVersion_1: <Segment:InCnt:SegCap>
// 18MF4F01_<BRCV006CV1:04:08><BRCV007CV1:05:15><BRCV008CV1:02:08><BRCV009CV5:09:20>
// 
//          tappSegFillGradeVersion_2: <Segment:InCnt:SegCap:NotAvail:NotGenDmyTu>
// 18MF4F01_<BRCV006CV1:04:08:0:0><BRCV007CV1:05:15:1:0><BRCV008CV1:02:08><BRCV009CV5:09:20:0:1>
typedef struct tapp_segFillGrade_msg_73 {
	TAPP_header_msg_t       header;                    // qqzzmmll                     -/
	SBI_char_t              delimiter;                 //  _
	SBI_char_t              segFillGradeStream[486];   // 10 x <Segment:InCnt:SegCap:NotAvail:NotGenDmyTu>
	SBI_char_t              terminator;                // end of message               -/
} TAPP_segFillGrade_msg_t;


// 74 Msg mit Info und Control                              -/
typedef struct tapp_uni_emptEmerg_msg_74 {
	TAPP_header_msg_t      header;               // qqzzmmll                     -/
	TAPP_info_msg_t        info;                 // hhnn@@@@                     -/
	TAPP_ctrl_msg_t        ctrl;                 // s_ddtt                     -/
} TAPP_uni_emptEmerg_msg_t;

typedef struct tapp_conveyorDirSwitchCtl_msg_75 {
	TAPP_header_msg_t       header;                    // qqzzmmll                     -/
	TAPP_info_msg_t         info;                      // hhnn@@@@                     -/
	SBI_char_t              situationMFC;              // m (Situation given by MFC)   -/
	SBI_char_t              situationPLC;              // p (Current Situation PLC)    -/
	SBI_char_t              terminator;                // end of message               -/
} TAPP_convDirSwitchCtl_msg_t;


typedef struct tapp_ats_stackInfo_msg {             // sNN/ttnNN
	SBI_char_t              stackNr;                // s                            -/
	SBI_char_t              posOnPallet[2];         // NN                           -/
	SBI_char_t              delimiter;              // /                            -/
	SBI_char_t              stackHeight[2];         // tt                           -/
	SBI_char_t              delimiterStackTotal;    // n                            -/
	SBI_char_t              stackTotal[2];          // NN                           -/
} TAPP_ats_stackInfo_msg_t;

typedef struct tapp_ats_tutIdent_msg {                // t...                       -/
	SBI_char_t                delimiterTUTIdent;      // t                          -/
	SBI_char_t                tutIdent[3];            // ...                        -/
} TAPP_ats_tutIdent_msg_t;

typedef struct tapp_ats_data_msg {                  // sbocLLC                    -/
	SBI_char_t                singleTray;             // s                          -/
	SBI_char_t                breakDown;              // b                          -/
	SBI_char_t                overHeight;             // o                          -/
	SBI_char_t                singleConfirmation;     // c                          -/
	SBI_char_t                loadType[2];            // LL                         -/
	SBI_char_t                weightLabel;            // C                          -/
} TAPP_ats_data_msg_t;


// Format 80 - ATS Universal message
// .........1.........2.........3.........4.........5.........6.........7.........8.........9.........0.........1.........2.........3...
// 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123
// qqzzmmllhhnn@@@@s_ddttlppppppppppppppppppppoOOOOOOOOOOsNN/ttnNNt...sbocLLCrrrLllllWwwwwHhhhhProddescr tttttttttttttttttttttttttttttt_
typedef struct tapp_ATS_msg_80 {
	TAPP_header_msg_t         header;                 // qqzzmmll                     -/
	TAPP_info_msg_t           info;                   // hhnn@@@@                     -/
	tapp_zvf_tote_msg_t       zvf[1];                 // s_ddttlpppppppppppppppppppp  -/
	TAPP_order_msg_t          order;                  // oOOOOOOOOOO                  -/
	TAPP_ats_stackInfo_msg_t  stackInfo;              // sNN/ttnNN                    -/
	TAPP_ats_tutIdent_msg_t   tutIdent;               // t...                         -/
	TAPP_ats_data_msg_t       atsData;                // sbocLLC                      -/
	SBI_char_t                reserve[3];             // rrr                          -/
	TAPP_ats_dim_t            dimension;              // Length, Width, Height        -/
	SBI_char_t                prodDescr[40];          // Prod Description             -/
	SBI_char_t                terminator;             // _                            -/
} TAPP_ats_msg_80_t;

// Format 81 – ATS PAL message
// .........1.........2.........3.........4.........5.........6.........7.........8.........9.........0.........1.........2.........3.........4.........5.
// 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901
// qqzzmmllhhnn@@@@s_ddttlpppppppppppp_lqqqqqqqqqqqqqqqqqqqqqqqqoOOOOOOOOOOsNN/ttnNNt...sbocLLCrrrLllllWwwwwHhhhhProddescr tttttttttttttttttttttttttttttt_
typedef struct tapp_ATS_msg_81 {
	TAPP_header_msg_t         header;                 // qqzzmmll                                       -/
	TAPP_info_msg_t           info;                   // hhnn@@@@                                       -/
	TAPP_zvf_msg_t            zvf[1];              // s_ddttlpppppppppppp_...      -/
	//TAPP_bc_rfid_msg_t        zvf[1];                 // s_ddttlpppppppppppp_lpppppppppppppppppppppppp_ -/ --> ASKO use rfIds
	TAPP_order_msg_t          order;                  // oOOOOOOOOOO                                    -/
	TAPP_ats_stackInfo_msg_t  stackInfo;              // sNN/ttnNN                                      -/
	TAPP_ats_tutIdent_msg_t   tutIdent;               // t...                                           -/
	TAPP_ats_data_msg_t       atsData;                // sbocLLC                                        -/
	SBI_char_t                reserve[3];             // rrr                                            -/
	TAPP_ats_dim_t            dimension;              // LllllWwwwwHhhhh                                -/
	SBI_char_t                prodDescr[40];          // Proddescr tttttttttttttttttttttttttttttt       -/
	SBI_char_t                terminator;             // _                                              -/
} TAPP_ats_msg_81_t;

// Format 82 - ATS two tote sides message
// .........1.........2.........3.........4.........5.........6.........7.........8.........9.........0.........1.........2.........3.........4.........5.....
// 12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345
// qqzzmmllhhnn@@@@s_ddttlpppppppppppppppppppp_lqqqqqqqqqqqqqqqqqqqqoOOOOOOOOOOsNN/ttnNNt...sbocLLCrrrLllllWwwwwHhhhhProddescr tttttttttttttttttttttttttttttt_
typedef struct tapp_ATS_msg_82 {
	TAPP_header_msg_t         header;              // qqzzmmll                                  -/
	TAPP_info_msg_t           info;                // hhnn@@@@                                  -/
	tapp_zvf_tote_msg_t       zvf[1];              // s_ddttlpppppppppppppppppppp               -/
	SBI_char_t                delimiter;           // _                                         -/
	tapp_toteid_tu_msg_t      SndToteId;           // lqqqqqqqqqqqqqqqqqqqq                     -/
	TAPP_order_msg_t          order;               // oOOOOOOOOOO                               -/
	TAPP_ats_stackInfo_msg_t  stackInfo;           // sNN/ttnNN                                 -/
	TAPP_ats_tutIdent_msg_t   tutIdent;            // t...                                      -/
	TAPP_ats_data_msg_t       atsData;             // sbocLLC                                   -/
	SBI_char_t                reserve[3];          // rrr                                       -/
	TAPP_ats_dim_t            dimension;           // LllllWwwwwHhhhh                           -/
	SBI_char_t                prodDescr[40];       // Proddescr tttttttttttttttttttttttttttttt  -/
	SBI_char_t                terminator;          // _                                         -/
} TAPP_ats_msg_82_t;


//--BEGIN--- Empty Stack Request to DEP destacker ----------------------------/
// tainmx
typedef struct tapp_lane_msg {
	SBI_char_t type;			// t : tray type ’S’mall,’L’arge
	SBI_char_t avail;			// a : 0/1 Availability of lane to destacker
	SBI_char_t inCnt[2];		// in: in  cnt, number of occupied LB (light barrier)
	SBI_char_t cap[2];			// mx: max cnt, number of existing LB (light barrier)
} TAPP_lane_msg_t;


// 45 – Empty Stack Request to DEP destacker
// .........1.........2.........3.........4.........5....
// 123456789012345678901234567890123456789012345678901234
// qqzzmmllhhnn@@@@smtainmxtainmxtainmxtainmxtainmxtainmx
//------------ -----------------------------------------------------------------/
#define TAPP_LANE_CNT  6 
typedef struct tapp_empStackRq_msg_t {
	TAPP_header_msg_t      header;              // qqzzmmll                     
	TAPP_info_msg_t        info;                // hhnn@@@@                     
	SBI_char_t             status;             // s Status (E,O - V.L)         
	SBI_char_t             modus;               // ’N’ normal
												// ’E emergency : supply all lanes
	TAPP_lane_msg_t        lane[TAPP_LANE_CNT]; // tainmx
	SBI_char_t             terminator;          // end of message               -/
} TAPP_empStackRq_msg_t;
//--END  --- Empty Stack Request to DEP destacker -----------------------------/


#if !defined(DAPP_TELE_H)
typedef struct tapp_uni_print_printInfo_msg {
	SBI_char_t             printResponse;      //In case Ringbuffer is used and MFC sends Apply and printer has no data a flag is set by PLC
	SBI_char_t             scStatus;
	SBI_char_t             checkBarCode[TAPP_PRINT_CONTROLLABEL_LEN];
	SBI_char_t             fill_1;
	SBI_char_t             labelSequenceNum[TAPP_PRINT_LABELSEQUENZ_LEN];
	SBI_char_t             fill_2;
	SBI_char_t             checkBarCodeLen[TAPP_PRINT_CHECKBARCODE_LEN];
	SBI_char_t             fill_3;
	SBI_char_t             height[TAPP_PRINT_HEIGHT_LEN];
	SBI_char_t             fill_4;
} TAPP_uni_print_printInfo_msg_t;
#endif

// 70 Msg mit n Drucker               -/
#if !defined(DAPP_TELE_H)
typedef struct tapp_uni_print_msg_70 {
#else 
typedef struct tapp_uni_print_msg_70_inDps {
#endif
#ifdef DLLTAPP_EXPORTS
	TAPP_header_msg_t              header;               // qqzzmmll                     -/
	TAPP_info_msg_t                info;                 // hhnn@@@@                     -/
#ifdef MFCI_RFID
	TAPP_bc_rfid_msg_t             zvf[1];               // s_ddttlpppppppppppp_lpppppppppppppppppppppppp_ -/
#else
	TAPP_zvf_msg_t                 zvf[1];
#endif // MFCI_RFID

#else 
#if DLLDAPP_EXPORTS
	DAPP_header_msg_t     header;

	//Kein uni_msg_t da in diesem struct ein info feld vorhanden ist das die PrintInfoFelder verschiebt
	//DAPP_uni_msg_t                 tu;
	char_typ hvo[DAPP_HVO_LEN - 1];        /* HvO                        */
	char_typ pos[DAPP_POS_LEN - 1];        /* Positionsnummer            */
	char_typ availDest[DAPP_ACCESSIBILITY_LEN - 1];/* Anfahrbarbeit des
													  Meldepunktes (Richtungsk.) */
	char_typ status;                              /* s Status                   */
												   /* V Voll belegt              */
												   /* L Leer                     */
	char_typ filler1;                              /* Filler                     */
	char_typ dest[MFC_TRACK_CODE_LEN - 1];   /* Transportrichtungskennung  */
	char_typ tuTyp[DAPP_TU_TYPE_LEN - 1];     /* TU Typ                     */

	char_typ scStatus;                            /* Scannerstatus              */
												   /* 'P' erfolgr. Scannerlesung */
												   /* '*' Lesefehler             */
	DAPP_tu_id_t tu;       /* TU-Identnummer             */
#if  (MFCI_TU_ORIENT)
	char_typ seite;                                /* orientation TU1            */
#endif

#endif
#endif

	TAPP_uni_print_printInfo_msg_t printInfo[TAPP_NUM_PRINTER_MAX];
	SBI_char_t                     terminator;           // end of message               -/
#if !defined(DAPP_TELE_H)
} TAPP_uni_print_msg_t;
#else
} TAPP_uni_print_msg_inDps_t;
#endif


//--Begin----fuer mtappn der Message

typedef union TAPP_msg_union {

	TAPP_header_msg_t			header;		//qqzzmmll					MSgNR-/
	TAPP_uni_fs_msg_t			fs;			//FS-Message (Standard)		01
	TAPP_uni_state_msg_t		status;		//Status-Message Gruppe		02
	TAPP_uni_ctrl_msg_t			crtl;		//Befehls-Message Gruppe	04
	TAPP_uni_prot_msg_t			prot;		//Protokollierung SPS		05

	TAPP_uni_encoder_msg_t		encoder;		// Encoder Value uplaud;		06
	//										// Status-Fahrzeug   -->RFZML	07
	//										// Command-Fahrzeug	 -->RFZML	08
	//										// Order-Fahrzeug	 -->RFZML	09
	//										// Feedback-Fahrzeug -->RFZML	10

	TAPP_uni_msg_t				tu;				// CRTL + TU Universaltelegramm 11
	TAPP_uni_kk_msg_t			tuKk;			// CRTL + TU + Konturen			12
	TAPP_uni_sscc_msg_t			tuSc;			// CTRL + TU + SSCC				13
	TAPP_uni_sscc2_msg_t		tuSc2;			// CTRL + TU + SSCC_1+ SSCC_2	41
	TAPP_tu_kk_tu_msg_t			tu2Kk;			// CTRL + TU + KK + TU			14
	TAPP_uni_occ_msg_t			tuOcc;			// CTRL (Only occupation)		15
	TAPP_uni_msg_t				tu2;			// CTRL + TU + CTRL + TU		16
	TAPP_SepWrap_msg_t			tuWrap;			// CTRL + TU + CTRL + TU + WRAP	42
	TAPP_tu_kk_sscc_msg_t		tuKkSc;			// CTRL + TU + Konturen + SSCC	43
	TAPP_SepWrapHaloila_msg_t	tuWrapHaloila;	// CTRL + TU + WRAP				44

	TAPP_SepWrapStrewi_msg_t    tuWrapStrewi;   // CTRL + TU + WRAP             47 -/
	TAPP_SepWrapMovitec_msg_t   tuWrapMovitec;  // CTRL + TU + WRAP             48 -/
	TAPP_SepWrapStrewiV2_msg_t	tuWrapstrewiv2;	// CTRL + TU + WRAP				49
	TAPP_empStackRq_msg_t		empStackRq;
	TAPP_uni_ext_msg_t          extEvt;			// CTRL + 3 event-sections		50
	TAPP_SepWrapStrewiV3_msg_t  tuWrapstrewiv3;	// CTRL + TU + WRAP				51
	TAPP_stk_3tu_msg_t			tu3Stck;		// CTRL +  TU + TU + CTRL + TU	55
	TAPP_accessRequest_msg_t	accReq;			// Access Request				71
	TAPP_externalSignal_msg_t	extSignal;		// External Signals				72
	TAPP_segFillGrade_msg_t		segFillGrade;	// Segment Füllgrad				73
	TAPP_uni_emptEmerg_msg_t	tuCtrl;			// CTRL							74
	TAPP_convDirSwitchCtl_msg_t convDirSwitch;	// Wechseln der Förderrichtung	75
	TAPP_uni_kk_sick1_msg_t		tukks1;			// CTRL + TU + Kontuen (Sick n.geeicht) 112
	TAPP_uni_kk_sick2_msg_t		tukks2;			// CTRL + TU + Konturen (Sick geeicht) 212

#if !defined(DAPP_TELE_H)
	TAPP_uni_print_msg_t		tuPrint;
#else
	TAPP_uni_print_msg_inDps_t		tuPrint;
#endif

	TAPP_ats_msg_80_t			atsUniversal;	// ATS universal tote			80
	TAPP_ats_msg_81_t			atsPal;			// ATS universal pallet			81
	TAPP_ats_msg_82_t			ats2Sides;		// ATS two toe sides			82
	TAPP_ats_msg_83_t			atsStackerStatus; //ATS stacker status			83
	TAPP_ats_msg_84_t			atsStackerInput;  //ATS stacker input			84

#if defined MFC_OPM

	TAPP_dep_msg_t				tuDep;			// DEP Depalletizer				17
	TAPP_case_msg_t				tuCase;			// Case Data					18
	TAPP_marry_msg_t			tuMarry;		// Case into tray lightgate     19
	TAPP_marry_msgF1_t			tuMarryF1;		// Case into tray lightgate 2.5mm 19
	TAPP_sort_msg_t				tuSort;			// Sorting after sequencebuffer 20
	TAPP_break_msg_t			tuBreak;		// Break sorting after SB		21
	TAPP_align_msg_t			tuAlign;		// COM aligment before			22
	TAPP_com_order_msg_t		comOrd;			// COM Order message			23
	TAPP_com_st_rq_msg_t		comStRq;		// COM state request			24
	TAPP_com_st_mmsg_t			comSt;			// COM state message			25
	TAPP_com_surf_sc_msg_t		surfSc;			// COM surface scanner message  26
	TAPP_work_order_msg_f		woOrd;			// TU and workorder message     27
	TAPP_tu4_msg_t				tu4;			// CTRL + TU +TU +TU +TU		28
	TAPP_tu2sc_msg_t			tu2sc;			// CTRL + TU + TU				30
	TAPP_tu5_msg_t				tu5;			// CTRL + TIC + TU+ TU+ TU+ TU+ 34
	TAPP_ioBits_msg_t			ioBits;			// Bitaustausch: Lampen, Tasten 36
	TAPP_inbound_msg_t			tuIn;			// Pal. inbound					38

	//Asko Vetby. REMA, Pallet area, base tu has rfid(25-1)

	TAPP_uni_rf_msg

#endif

	SPS_msg_t					sps;
	ABL_sps_msg_t				spsMsg;
	SBI_char_t					raw[SPS_MSG_LEN];

}TAPP_msg_u_t;


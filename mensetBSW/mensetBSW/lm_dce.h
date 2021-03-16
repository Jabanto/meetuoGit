#pragma once
#include "kset_dce.h"
#include "mfc_if.h"

/*------------Felder der action-point-Struktur-------------*/

typedef struct LM_ap_t {

	SBI_bool_t			valid;			/*								*/
	SBI_int32_t		    selfRefIdX;		/* own index of record in SHM   */
	MFC_id_t			id;				/* short identifier             */
	//MFC_name_t			name;			/* cleartext                    */	

}LM_ap_t;

typedef struct LM_seg_t {

	SBI_int32_t			intCnt;

}LM_seg_t;
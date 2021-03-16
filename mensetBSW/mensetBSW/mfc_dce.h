#pragma once
#include "sbi_if.h"

#include "mfci_typ.h"
#include "mfci.h"
#include "mfc_error.h"


/*----------short label for Id's------------*/

typedef MFCI_id_t				MFC_id_t;

#define MFC_MODUL_LEN			MFCI_MODUL_LEN
typedef SBI_char_t				MFC_modul_nr_t[MFC_MODUL_LEN];

/*---------declaration text---------------*/



/*-------------------- date and time type -----------------------------------*/

typedef SBI_timeVal_t			MFC_timeVal_t;
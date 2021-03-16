#pragma once

#if !defined(MFCI_TYP_H)
#define MFCI_TYP_H

#include "SBI_dce.h"
#include "mfci.h"


#if defined (__cplusplus)
extern "C" {
#endif

	typedef SBI_char_t	MFCI_id_t[MFCI_ID_LEN];

	typedef SBI_char_t  MFCI_tu_id_t[MFCI_TU_ID_LEN];

#if defined (__cplusplus)
}
#endif

#endif /* MFCI_TYP_H */
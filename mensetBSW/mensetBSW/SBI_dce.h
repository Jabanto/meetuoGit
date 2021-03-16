#pragma once
#include <string.h>

typedef char SBI_char_t;

//# Represents a 32-bits signd integer. the smalltest possible value is defined in
// #SBI_INT32_MIN and the largest possible value is deined in #
typedef long SBI_int32_t;

// \brief Represents a 32-bit unsigned integer. The smallest possible value is defined in
// #SBI_UINT32_MIN and the largest possible value is defined in #SBI_UINT32_MAX.
typedef unsigned long SBI_uint32_t;



// Represents a boolean value with either the value tur or false storde in 32-bits

typedef SBI_int32_t SBI_bool_t;

//#SBI_UINT8_MIN and the largest possible value is defined in #SBI_UINT8_MAX.
typedef unsigned char SBI_uint8_t;



/*
 * Definitions of older Systems
 * Convert old types to SBI_* by cpp
*/


#define SBI_char_typ        SBI_char_t
//#define SBI_int8_typ        SBI_int8_t
#define SBI_uint8_typ       SBI_uint8_t
//#define SBI_int16_typ       SBI_int16_t
//#define SBI_uint16_typ      SBI_uint16_t
#define SBI_int32_typ       SBI_int32_t
#define SBI_uint32_typ      SBI_uint32_t
//#define SBI_fl32_typ        SBI_fl32_t
//#define SBI_fl64_typ        SBI_fl64_t
#define SBI_bool_typ        SBI_bool_t
//#define SBI_size_typ        SBI_size_t
//#define SBI_unixTime_typ    SBI_unixTime_t
//#define SBI_mldNr_typ       SBI_mldNr_t
#define SBI_timeVal_typ     SBI_timeVal_t
#define SBI_timeVal_typrec  SBI_timeVal_trec

//#define int8_typ            SBI_int8_t
#define uint8_typ           SBI_uint8_t
//#define int16_typ           SBI_int16_t
//#define uint16_typ          SBI_uint16_t
#define int32_typ           SBI_int32_t
#define uint32_typ          SBI_uint32_t
//#define fl32_typ            SBI_fl32_t
//#define fl64_typ            SBI_fl64_t
//#define byte_int_typ        SBI_int8_t
#define unsig_byte_int_typ  SBI_uint8_t
//#define word_int_typ        SBI_int16_t
//#define unsig_word_int_typ  SBI_uint16_t
#define int_typ             SBI_int32_t
#define unsig_int_typ       SBI_uint32_t
#define long_int_typ        SBI_int32_t
#define unsig_long_int_typ  SBI_int32_t
//#define float_typ           SBI_fl32_t
//#define double_float_typ    SBI_fl64_t
#define char_typ            SBI_char_t
#define boolean_typ         SBI_bool_t
#define bool_typ            SBI_bool_t
//#define int64_typ           SBI_int64_t
//#define uint64_typ          SBI_uint64_t
//#define fl128_typ           SBI_fl128_t



typedef struct SBI_timeVal_trec {

	SBI_uint32_t	tv_sec;		/*	seconds	 */
	SBI_int32_t		tv_usec;	/*  and microseconds  */

}SBI_timeVal_t;






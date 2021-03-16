#pragma once


#include "sbi_osid.h"
#include "SBI_dce.h"
#include "sbi_os.h"

//586

/*
 * $Id: sbi_mute.h,v 1.9 1998/02/10 13:23:46 aslsbi Exp aslsbi $
*/
/*
 * COPY-RIGHT (c) W I T R O N - LOGISTIK+INFORMATIK Parkstein
 *
 * DATEI-NAME    :  sbi_mutex.h
 * VERSION       :  1.0
 * ERSTELLT VON  :  Udo Fischer
 * ERSTELL-DATUM :  01.06.1994
 *
 * HISTORY       :  Definition der Header und Schnittstellenfunktionen
 *                  zur Zugriffssynchronisation mit Threads.
 *
*/



//L746
typedef struct SBI_thread_typrec {
	bool_typ            isRunning;
#if defined(SBI_THREAD)
#ifndef SBI_WINNT
	pthread_t           pthread;
	pthread_attr_t      pthreadAttr;
#else
#if defined(SBI_64BIT)
	uintptr_t           pthread;    /* HandleObject from CreateThread */
#else
	unsigned long       pthread;    /* HandleObject from CreateThread */
#endif
	DWORD               stackSize;  /* unused */
	DWORD               pthreadId;  /* thread id from CreateThread */
#endif /* SBI_WINNT */
#endif /* SBI_THREAD */
} SBI_thread_typ;

#define SBImaxOf(a,b) (((a) > (b))? (a) : (b))

#if defined (SBI_WINNT)
 #define SBI_SYSEXCEPTION_BEGIN __try{
#else
 #define SBI_SYSEXCEPTION_BEGIN
#endif
#if defined (SBI_WINNT)
 #define SBI_SYSEXCEPTION_END } __except (){}
#else
 #define SBI_SYSEXCEPTION_END
#endif

//L179
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

typedef enum SBI_shmProt_typenum {
	SBI_SHM_RW = 0,          /* Lesen & Schreiben (default)        */
	SBI_SHM_RDONLY,        /* Readonly                           */
	SBI_SHM_MEMRW,         /* Lesen & Schreiben (nur im Speicher)*/
	SBI_SHM_MEMRDONLY      /* Readonly          (nur im Speicher)*/
} SBI_shmProt_typ;

typedef struct SBI_shmHandleElement_typrec {
	char_typ        *name;   /* Pfad zum File od. Sharedmemoryname*/
	char_typ        *fileName; /* Pfad zum File                   */
	key_t            key;    /* Keyid des Sharedmemory            */
	caddr_t          addr;   /* Speicheradresse                   */
	caddr_t          adrFix; /* Speicheradresse                   */
	size_t           len;    /* geforderte Länge                  */
	long             lenPg;  /* Laenge MemPage nach sysconf()     */
	long             lenMem; /* Laenge MemPage nach sysconf()     */
#ifndef SBI_WINNT
	int              shmId;  /* Idendifikation im System          */
	int              file;   /* Filedescriptor des Datenfiles     */
#else
	HANDLE           hMapFile; /* mapping handle                  */
	HANDLE           hFile;  /* disk file handle                  */
#endif /* SBI_WINNT */
	//SBI_semId_typ    semId;  /* Semaphore fuer Zugriffschutz      */
	//SBI_shmProt_typ  prot;   /* Zugriffsart                       */
	bool_typ         isThreadActiv;
	bool_typ         isThreadRunning;
	bool_typ         isTransActiv;
	size_t           bfCount;    /* count of bitFields of shmPages*/
	size_t           lastBit;    /* lastBit of BitField of Pages  */
	size_t           lenLastPage;/* bytes of last page            */
	uint32_typ      *bfArray;    /* BitField array of shmPages    */
#ifndef SBI_VC
	SBI_thread_typ   recvThread; /* messages from SBI_shmFlush    */
	//SBI_mutex_typ    hndlMutex;  /* Zugriff gemeinsame Daten      */
	//SBI_mutex_typ    runMutex;
#endif /* SBI_VC */
	/* ControlDataSection */
	size_t           cLen;       /* connect length                */
	long             cLenPg;     /* system page                   */
	long             cLenMem;    /* mapping region                */
	size_t           cBfCount;   /* len bitFields                 */
	size_t           cLastBit;   /* end of region by bitfield     */
	size_t           cLenLastPage;
	SBI_uint32_t     cChkSum;    /* checksum of ControlDataSection*/
	//SBI_pointer_typ  threadData; /* thread io data for flush, ... */
} SBI_shmHandleElement_typ, *SBI_shmHandle_typ;
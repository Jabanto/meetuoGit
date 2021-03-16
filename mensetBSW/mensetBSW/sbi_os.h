#pragma once

//L37
#if defined(SBI_WINNT)
#include  <windows.h>
#include  <winsock.h>
#include  "rpc.h"
//#include  "dceport.h"
//#include  "iostream.h"
//#include  "strstrea.h"
#include  <winnetwk.h>
#define   SBIAPI    __stdcall
#define   SBIDLLAPI __declspec(dllexport)
#define   SBIDLLIMP __declspec(dllimport)
#define   SBICXXAPI __cdecl
#define   off_t   _off_t
#ifndef ENOTSUP
#define   ENOTSUP   (-1)
#endif
#define   F_OK       00
#define   getpid    _getpid
#define   strnicmp  _strnicmp
#ifndef strdup
#define   strdup    _strdup
#endif    
#define   putenv    _putenv
#define   access    _access
#define   fileno    _fileno
#define   tzset     _tzset
#define   unlink    _unlink
#define   lseek     _lseek
#define   itoa      _itoa
#define   chdir     _chdir
#ifndef getcwd
#define   getcwd    _getcwd
#endif    
#define   strlwr    _strlwr
#define   strupr    _strupr
/* !!
   do not override open and close because of various member functions
   with the same name that would not longer work!!
#define   open      _open
#define   close     _close
*/
#if !defined(SBI_TIME_OS_INTERFACE)
#define   SBI_TIME_OS_INTERFACE 1
#define   time          SBI_osTimeTime
#define   mktime        SBI_osTimeMktime
#define   localtime     SBI_osTimeLocaltime
#define   localtime_s   SBI_osTimeLocaltime_s
#define   gmtime        SBI_osTimeGmtime
#define   ctime         SBI_osTimeCtime
#endif

typedef   void *caddr_t;
#endif /* SBI_WINNT */

//L128
typedef unsigned long key_t;
typedef short         mode_t;
typedef int           pid_t;
typedef unsigned long uid_t;
typedef unsigned long gid_t;
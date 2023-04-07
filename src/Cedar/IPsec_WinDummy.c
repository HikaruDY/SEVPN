#include <GlobalConst.h>

#ifdef	WIN32

#define	_WIN32_WINNT		0x0600
#define	WINVER				0x0600
#define	INITGUID
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <windows.h>
#include <wincrypt.h>
#include <wininet.h>
#include <shlobj.h>
#include <commctrl.h>
#include <Dbghelp.h>
#include <Fwpmu.h>
#include <Fwpmtypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <stdarg.h>
#include <time.h>
#include <errno.h>
#include <Mayaqua/Mayaqua.h>
#include <Cedar/Cedar.h>
#include "IPsec_Win7Inner.h"

static IPSEC_WIN7_FUNCTIONS *api = NULL;
static HINSTANCE hDll = NULL;

IPSEC_WIN7 *IPsecWin7Init(){
	return NULL;
}

void IPsecWin7UpdateHostIPAddressList(IPSEC_WIN7 *w){}

void IPsecWin7Free(IPSEC_WIN7 *w){}

bool IPsecWin7InitDriver(){
	return false;
}
bool IPsecWin7InitDriverInner(){
	return false;
}

void SetCurrentIPsecWin7DriverBuild(){}

UINT GetCurrentIPsecWin7DriverBuild(){
	return 0;
}

bool IPsecWin7InitApi(){
	return false;
}

#endif	// WIN32



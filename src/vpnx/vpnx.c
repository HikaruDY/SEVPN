
#include <GlobalConst.h>

#define	VPN_EXE

#ifdef	WIN32
#include <winsock2.h>
#include <windows.h>
#include <wincrypt.h>
#include <wininet.h>
#include <shlobj.h>
#include <commctrl.h>
#include <Dbghelp.h>
#include "../PenCore/resource.h"
#endif	// WIN32
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <stdarg.h>
#include <time.h>
#include <Mayaqua/Mayaqua.h>
#include <Cedar/Cedar.h>


void StartServer(){
	InitCedar();
	StInit();
	StStartServer(false);
}
void StartServerBridge(){
	InitCedar();
	StInit();
	StStartServer(true);
}
void StopServer(){
	StStopServer();
	StFree();
	FreeCedar();
}
void StartClient(){
	InitCedar();
	CtStartClient();
}
void StopClient(){
	CtStopClient();
	FreeCedar();
}

int CommandEx(int argc, char *argv[]){
		wchar_t *s;
	UINT ret = 0;

	InitMayaqua(false, false, argc, argv);
	InitCedar();

	s = GetCommandLineUniStr();

	if (s == NULL)
	{
		s = CopyUniStr(L"");
	}

	if (UniStrCmpi(s, L"exit") != 0)
	{
		UINT size = UniStrSize(s) + 64;
		wchar_t *tmp;

		tmp = Malloc(size);
		UniFormat(tmp, size, L"vpncmd %s", s);
		ret = CommandMain(tmp);

		Free(tmp);
	}
}

// WinMain function
int main(int argc, char *argv[]){
	int i = 0;

	VgUseStaticLink();

	printf("I: VPNX: Starting...\n");

	for(i=0; i < argc; i++){
		//printf("DEBUG: %i: %s\n", i, argv[i]);
		if( !StrCmpi(argv[i], "/Server") ){
			printf("I: VPNX: Server mode.\n");
			return MsService(GC_SVC_NAME_VPNSERVER, StartServer, StopServer, ICO_CASCADE, argv[0]);
		}
		if( !StrCmpi(argv[i], "/Bridge") ){
			printf("I: VPNX: Server mode.\n");
			return MsService(GC_SVC_NAME_VPNSERVER, StartServerBridge, StopServer, ICO_CASCADE, argv[0]);
		}
		if( !StrCmpi(argv[i], "/Client") ){
			printf("I: VPNX: Client mode.\n");
			return MsService(GC_SVC_NAME_VPNSERVER, StartClient, StopClient, ICO_CASCADE, argv[0]);
		}
		if( !StrCmpi(argv[i], "/Config") ){
			printf("I: VPNX: Configuration mode.\n");
			return CommandEx(argc, argv);
		}

		if( !StrCmpi(argv[i], "/GUI") ){
			printf("I: VPNX: Configuration GUI mode.\n");
			InitMayaqua(false, false, 0, NULL);
			InitCedar();
			SMExec();
			FreeCedar();
			FreeMayaqua();
			return 0;
		}

	}

	printf("E: VPNX: vpnx [/Server|/Client|/Config|/GUI]\n");

	return 0;
}


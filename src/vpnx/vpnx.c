
#include <GlobalConst.h>

#define	VPN_EXE

#ifdef WIN32
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


int __stdcall CommandEx(int argc, char *argv[]){
	wchar_t *s;
	UINT ret = 0;

	s = GetCommandLineUniStr();

	if (s == 0){
		s = CopyUniStr(L"");
	}

	if (UniStrCmpi(s, L"exit") != 0){
		UINT size = UniStrSize(s) + 64;
		wchar_t *tmp;

		tmp = Malloc(size);
		UniFormat(tmp, size, L"vpncmd %s", s);
		ret = CommandMain(tmp);

		Free(tmp);
	}

	return 0;
}

void __stdcall CtrlHandlerCommon(){
	FreeCedar();
	FreeMayaqua();
	return;
}
int __stdcall CtrlHandlerServer(unsigned int Type){
	printf("I: VPNX: Exiting...");
	StStopServer();
	CtrlHandlerCommon();
	return 0;
}
int __stdcall CtrlHandlerClient(unsigned int Type){
	printf("I: VPNX: Exiting...");
	StStopServer();
	StFree();
	CtrlHandlerCommon();
	return 0;
}

void __stdcall WaitExit(){
#ifdef WIN32
	WaitForSingleObject(CreateEvent(0, TRUE, FALSE, 0), INFINITE); //Infinite pause
#else
	while(1){
		sleep(10);
	}
#endif
}

void __stdcall StartServer(){
	StInit();
	StStartServer(false);
	WaitExit();
}
void __stdcall StartServerBridge(){
	StInit();
	StStartServer(true);
	WaitExit();
}

void __stdcall StartClient(){
	CtStartClient();
	WaitExit();
}


// WinMain function
int main(int argc, char *argv[]){
	int i = 0;


	printf("I: VPNX: Starting...\n");

	InitMayaqua(false, false, 0, 0);
	InitCedar();

	for(i=0; i < argc; i++){
		//printf("DEBUG: %i: %s\n", i, argv[i]);
		if( !StrCmpi(argv[i], "/Server") ){
			printf("I: VPNX: Server mode.\n");
			SetConsoleCtrlHandler((PHANDLER_ROUTINE) CtrlHandlerServer, true);
			StartServer();
			return;
		}
		if( !StrCmpi(argv[i], "/Bridge") ){
			printf("I: VPNX: Bridge mode.\n");
			SetConsoleCtrlHandler((PHANDLER_ROUTINE) CtrlHandlerServer, true);
			StartServerBridge();
			return;	
		}
		if( !StrCmpi(argv[i], "/Client") ){
			printf("I: VPNX: Client mode.\n");
			StartClient();
			return;	
		}
		if( !StrCmpi(argv[i], "/Config") ){
			printf("I: VPNX: Configuration mode.\n");
			return CommandEx(argc, argv);
		}

		if( !StrCmpi(argv[i], "/GUI") ){
			int Client = 0;
			printf("I: VPNX: Configuration GUI mode.\n");

			{
				int n = i;
				for(n; n < argc; n++){
					if(!StrCmpi(argv[n], "/Client")){
						Client = 1;
					}
				}
			}

			if(!Client){
				SMExec();
			} else {
				CMExec();
			}

			FreeCedar();
			FreeMayaqua();
			return 0;
		}

	}

	printf("E: VPNX: Run as Server	: vpnx [/Server|/Client]\n");
	printf("E: VPNX: Config Utility	: vpnx /Config [/Server|Client]\n");
	printf("E: VPNX: GUI Config	: vpnx /GUI [/Server|/Client] [/Remote]\n");

	FreeCedar();
	FreeMayaqua();

	return 0;
}


//vpnx: All in one for embedded systems.
//	(C)2018 Dark Network Systems / Dark Embedded Systems
//	http://dark-x.net/
//	http://git.dark-x.org/SEVPN


//Headers
#define	VPN_EXE
#include <GlobalConst.h>

#if defined(WIN32) || defined(WIN64) || defined(_WIN32) || defined(_WIN64)
	#define DES_ENV_WINDOWS
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


//Multi platform macros
#if defined(DES_ENV_WINDOWS)
	#define DES_CALLBACK(Name) unsigned int Name(unsigned int type)
	#define DES_FUNCTION(RType, Name) RType __stdcall Name
	#define DES_CRETURN(value) return value
	#define DES_REGISTERHANDLER(fptr) SetConsoleCtrlHandler((PHANDLER_ROUTINE) fptr, true);
	#define DES_EXITPROCESS(code) ExitProcess(code)
#else //Not Windows
	#define DES_CALLBACK(Name) void Name(int signal)
	#define DES_CRETURN(value) return
	#define DES_FUNCTION(RType, Name) RType Name
	#define DES_REGISTERHANDLER(fptr) signal(SIGINT, fptr)
	#define DES_EXITPROCESS(code)
#endif

//Common
typedef enum {
	RM_NONE,
	RM_SERVER,
	RM_CLIENT,
	RM_CONFIG,
	RM_GUI,
} RunMode;

typedef enum {
	RT_NONE,
	RT_SERVER,
	RT_BRIDGE,
	RT_CLIENT,
} RunType;

typedef struct {
	RunMode RM;
	RunType RT;
} RunInfo;


//Common
DES_FUNCTION(void, WaitExit)(){
#if defined(DES_ENV_WINDOWS)
	WaitForSingleObject(CreateEvent(0, TRUE, FALSE, 0), INFINITE); //Infinite pause
#else
	while(1){
		sleep(10);
	}
#endif
}

DES_FUNCTION(RunType, GetRunType)(int i, int argc, char *argv[]){
	RunType RT = RT_SERVER;
	for(i; i < argc; i++){
		if(!StrCmpi(argv[i], "/Client")){
			RT = RT_CLIENT;
			break;
		}
	}
	return RT;
}
DES_FUNCTION(RunInfo, GetRunMode)(int argc, char *argv[]){
	int i;
	RunInfo RI = {RM_NONE, RT_NONE};

	for(i=0; i < argc; i++){
		if( !StrCmpi(argv[i], "/Server") ){
			printf("I: VPNX: Server mode.\n");
			RI.RM = RM_SERVER;
			RI.RT = RT_SERVER;
			break;
		}
		if( !StrCmpi(argv[i], "/Bridge") ){
			printf("I: VPNX: Bridge mode.\n");
			RI.RM = RM_SERVER;
			RI.RT = RT_BRIDGE;
			break;
		}
		if( !StrCmpi(argv[i], "/Client") ){
			printf("I: VPNX: Client mode.\n");
			RI.RM = RM_CLIENT;
			RI.RT = RT_CLIENT;
			break;
		}
		if( !StrCmpi(argv[i], "/Config") ){
			RI.RM = RM_CONFIG;
			RI.RT = GetRunType(i, argc, argv);
			if(RI.RT == RT_SERVER){
				printf("I: VPNX: Server Configuration mode.\n");
			} else {
				printf("I: VPNX: Client Configuration mode.\n");
			}
			break;
		}
#if defined(DES_ENV_WINDOWS) && defined(VPNX_GUI)
		if( !StrCmpi(argv[i], "/GUI") ){
			RI.RM = RM_GUI;
			RI.RT = GetRunType(i, argc, argv);
			if(RI.RT == RT_SERVER){
				printf("I: VPNX: Server GUI mode.\n");
			} else {
				printf("I: VPNX: Client GUI mode.\n");
			}
			break;
		}
#endif
	}
	return RI;
}


//Service
DES_FUNCTION(void, StartServerService)(){
	printf("I: VPNX: Server started.\n");
	StInit();
	StStartServer(false);
	WaitExit();
}
DES_FUNCTION(void, StartBridgeService)(){
	printf("I: VPNX: Brdige started.\n");
	StInit();
	StStartServer(true);
	WaitExit();
}
DES_FUNCTION(void, StartClientService)(){
	printf("I: VPNX: Client started.\n");
	CtStartClient();
	WaitExit();
}
DES_FUNCTION(void, FreeLibsForExit)(){
#if !defined(DES_ENV_WINDOWS)
	exit(0); //In low memory embedded linux env, can't free libraries correctly: Out of memory
#endif

	FreeCedar();
	FreeMayaqua();
}
DES_CALLBACK(OnExitServer){
	printf("I: VPNX: Exiting...\n");
	StStopServer();
	FreeLibsForExit();
	DES_EXITPROCESS(0);
	DES_CRETURN(1); //Handler proced (But never reached here...)
}
DES_CALLBACK(OnExitClient){
	printf("I: VPNX: Exiting...\n");
	CtStopClient();
	StFree();
	FreeLibsForExit();
	DES_EXITPROCESS(0);
	DES_CRETURN(1); //Handler proced (But never reached here...)
}

#if defined(DES_ENV_WINDOWS)
DES_FUNCTION(void, StartGUI)(RunType RT){
	if(RT != RT_CLIENT){
		SMExec();
	} else {
		SetCommandLineStr("/Remote"); //Always specify target
		CMExec();
	}
	FreeLibsForExit();
}
#endif //DES_ENV_WINDOWS


DES_FUNCTION(void, CommandEx)(int argc, char *argv[]){
	wchar_t *s;
	UINT ret = 0;

	s = GetCommandLineUniStr();

	if (s == 0){
		s = CopyUniStr(L"");
	}

	if (UniStrCmpi(s, L"exit") != 0){
		UINT size = UniStrSize(s) + 64;
		wchar_t *tmp;

		tmp = (wchar_t*) Malloc(size);
		UniFormat(tmp, size, L"vpncmd %s", s);
		ret = CommandMain(tmp);

		Free(tmp);
	}

	return;
}


//Main
int main(int argc, char *argv[]){
	RunInfo RI;

	RI = GetRunMode(argc, argv);
	if(RI.RM == RM_NONE){
		printf("E: VPNX: Run as Server	: vpnx [/Server|/Client]\n");
		printf("E: VPNX: Config Utility	: vpnx /Config [/Server|Client]\n");
#if defined(DES_ENV_WINDOWS) && defined(VPNX_GUI)
		printf("E: VPNX: GUI Config	: vpnx /GUI [/Server|/Client]\n");
#endif //DES_ENV_WINDOWS
		return 1;
	}

	printf("I: VPNX: Initializing...\n");

	if( (RI.RM == RM_SERVER) || (RI.RM == RM_CLIENT) ){
		MayaquaMinimalMode(); //Reduce memory usage when service (Reduced 3-4 MB in embedded linux env that has only 32MB memory)
	}

	InitMayaqua(false, false, argc, argv); //+1:  /Remote
	InitCedar();

	switch(RI.RM){
		case RM_SERVER: {
			DES_REGISTERHANDLER(OnExitServer);
			if(RI.RT != RT_BRIDGE){
				StartServerService();
			} else {
				StartBridgeService();
			}
			break;
		}
		case RM_CLIENT: {
			DES_REGISTERHANDLER(OnExitClient);
			StartClientService();
			break;
		}
		case RM_CONFIG: {
			CommandEx(argc, argv);
			break;
		}
#if defined(DES_ENV_WINDOWS)
		case RM_GUI: {
			StartGUI(RI.RT);
			break;
		}
#endif //DES_ENV_WINDOWS
	}

	return 0;
}
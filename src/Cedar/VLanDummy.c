#include <GlobalConst.h>

#ifdef	VLAN_C

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <stdarg.h>
#include <time.h>
#include <errno.h>
#include <Mayaqua/Mayaqua.h>
#include <Cedar/Cedar.h>

#ifdef	OS_WIN32

void Win32GetWinVer(RPC_WINVER *v){}


void Win32ReleaseAllDhcp9x(bool wait){}

void RouteTrackingMain(SESSION *s){}

void RouteTrackingStart(SESSION *s){}

void RouteTrackingStop(SESSION *s, ROUTE_TRACKING *t){}

UINT GetInstanceId(char *name){
	return 0;
}

INSTANCE_LIST *GetInstanceList(){
	return NULL;
}

void FreeInstanceList(INSTANCE_LIST *n){}

void VLanPaFree(SESSION *s){}

bool VLanPaPutPacket(SESSION *s, void *data, UINT size){
	return false;
}

UINT VLanPaGetNextPacket(SESSION *s, void **data){
	return 0;
}

CANCEL *VLanPaGetCancel(SESSION *s){
	return NULL;
}

bool VLanPaInit(SESSION *s){
	return false;
}

PACKET_ADAPTER *VLanGetPacketAdapter(){
	return NULL;
}

bool VLanPutPacket(VLAN *v, void *buf, UINT size){
	return false;
}

bool VLanGetNextPacket(VLAN *v, void **buf, UINT *size){
	return false;
}

bool VLanPutPacketsToDriver(VLAN *v){
	return false;
}

bool VLanGetPacketsFromDriver(VLAN *v){
	return false;
}

CANCEL *VLanGetCancel(VLAN *v){
	return NULL;
}

void FreeVLan(VLAN *v){}

VLAN *NewVLan(char *instance_name, VLAN_PARAM *param){
	return NULL;
}

#endif	// OS_WIN32

#endif	//VLAN_C


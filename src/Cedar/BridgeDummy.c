#include <GlobalConst.h>

#ifdef	BRIDGE_C

#include <winsock2.h>
#include <Ws2tcpip.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <stdarg.h>
#include <time.h>
#include <errno.h>
#include <Packet32.h>
#include <Mayaqua/Mayaqua.h>
#include <Cedar/Cedar.h>

static WP *wp = NULL;
static LIST *eth_list = NULL;

static LOCK *eth_list_lock = NULL;
static bool is_see_mode = false;
static bool is_using_selow = false;
static bool enable_selow = true;

static bool g_bridge_win32_show_all_if = false;

void Win32SetEnableSeLow(bool b){}

bool Win32GetEnableSeLow(){
	return false;
}

void Win32EthSetShowAllIf(bool b){}

bool Win32EthGetShowAllIf(){
	return false;
}

int CmpRpcEnumEthVLan(void *p1, void *p2){
	return -1;
}

UINT EthGetMtu(ETH *e){
	return 0;
}

bool EthSetMtu(ETH *e, UINT mtu){
	return false;
}

bool EthIsChangeMtuSupported(ETH *e){
	return false;
}

bool SetVLanEnableStatus(char *title, bool enable){
	return false;
}

RPC_ENUM_ETH_VLAN_ITEM *FindEthVLanItem(RPC_ENUM_ETH_VLAN *t, char *name){
	return NULL;
}

void GetVLanEnableStatus(RPC_ENUM_ETH_VLAN_ITEM *e){}

void GetVLanSupportStatus(RPC_ENUM_ETH_VLAN_ITEM *e){}

char *SearchDeviceInstanceIdFromShortKey(char *short_key){
	return NULL;
}

bool EnumEthVLanWin32(RPC_ENUM_ETH_VLAN *t){
	return false;
}

bool GetClassRegKeyWin32(char *key, UINT key_size, char *short_key, UINT short_key_size, char *guid){
	return false;
}

void EthPutPackets(ETH *e, UINT num, void **datas, UINT *sizes){}

void EthPutPacket(ETH *e, void *data, UINT size){}

UINT EthGetPacket(ETH *e, void **data){
	return 0;
}

CANCEL *EthGetCancel(ETH *e){
	return NULL;
}

void CloseEth(ETH *e){}

struct WP_ADAPTER *Win32EthSearch(char *name){
	return NULL;
}

ETH *OpenEth(char *name, bool local, bool tapmode, char *tapaddr){
	return NULL;
}

ETH *OpenEthInternal(char *name, bool local, bool tapmode, char *tapaddr){
	return NULL;
}

void Win32EthMakeCombinedName(char *dst, UINT dst_size, char *nicname, char *guid){}

UINT Win32EthGetNameAndIdFromCombinedName(char *name, UINT name_size, char *str){
	return 0;
}

UINT Win32EthGenIdFromGuid(char *guid){
	return 0;
}

TOKEN_LIST *GetEthList(){
	return NULL;
}

TOKEN_LIST *GetEthListEx(UINT *total_num_including_hidden, bool enum_normal, bool enum_rawip){
	return NULL;
}

int CompareWpAdapter(void *p1, void *p2){
	return -1;
}

bool Win32IsUsingSeLow(){
	return false;
}

LIST *GetEthAdapterList(){
	return NULL;
}
LIST *GetEthAdapterListInternal(){
	return NULL;
}

void InitEthAdaptersList(){}

void FreeEthAdaptersList(){}

bool Win32EthIsSuSupported(){
	return false;
}

bool IsEthSupported(){
	return false;
}
bool IsEthSupportedInner(){
	return false;
}

bool IsPcdSupported(){
	return false;
}

void SavePcdDriverBuild(UINT build){}

UINT LoadPcdDriverBuild(){
	return 0;
}

HINSTANCE InstallPcdDriver(){
	return NULL;
}
HINSTANCE InstallPcdDriverInternal(){
	return NULL;
}

void InitEth(){}

bool IsWin32BridgeWithSee(){
	return false;
}

bool InitWpWithLoadLibrary(WP *wp, HINSTANCE h){
	return false;
}

void FreeEth(){}

void GetEthNetworkConnectionName(wchar_t *dst, UINT size, char *device_name){}

#endif // BRIDGE_C



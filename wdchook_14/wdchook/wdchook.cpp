// wdchook.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "wdchook.h"
#include <stdio.h>

#pragma warning(disable:4996)

//////////////////////////////////////////////////
int input1 =0, input2=0,input3 = 0, input4 = 0, input5 = 0, input6 = 0, input7 = 0;
char szData[255];

void LoginStep_1() {//Click btn Bat Dau
	__asm {
		push eax;
		mov eax, 0x00444AA0;
		call eax;
		pop eax;
	}
}

void LoginStep_3() {//Click btn Xac Dinh
	__asm {
		push ecx;
		push eax;
		mov ecx, 0x00876FB0;
		mov ecx, [ecx];
		mov eax, 0x00443BD0;
		call eax;
		pop eax;
		pop ecx;
	}
}

void LoginStep_4(int index=0) { //Click Bat Dau (chon nhan vat)
	switch (index){
		case 0://Bat dau
			index = 0x1850;
			break;
		case 1://Tao nhan vat
			index = 0x1BD0;
			break;
		case 2://Page Up
			index = 0x22D0;
			break;
		case 3://Page Down
			index = 0x2110;
			break;
	}
	
	__asm {
		push ecx;
		push eax;
		mov eax, 0x3D4CCCCD;
		push eax;
		push 0;
		mov ecx, 0x00876FA8;
		mov ecx, [ecx];
		push index;
		add dword ptr [esp], ecx;
		mov eax, 0x004400C0;
		call eax;
		pop eax;
		pop ecx;
	}
}

void Move(int xPos, int yPos, int Mode, int idMap) {
	__asm {
		push eax;
		push ecx;
		mov eax, Mode;
		push eax;
		mov eax, yPos;
		push eax;
		mov eax, xPos;
		push eax;
		mov eax, idMap;
		push eax;
		mov ecx, 0x009D8E80;
		mov eax, 0x00648FB0;
		call eax;
		pop ecx;
		pop eax;
	}
}

void Action(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int charAddr) {
	__asm {
		push eax;
		push ecx;
		mov ecx, charAddr; //setup ecx
		push 0;
		mov eax, arg7;
		push eax;
		mov eax, arg6;
		push eax;
		mov eax, arg5;
		push eax;
		mov eax, arg4;
		push eax;
		mov eax, arg3;
		push eax;
		mov eax, arg2;//npc id
		push eax;
		mov eax, arg1; //action type
		push eax;
		mov eax, 0x005EB5E0;
		call eax;
		pop ecx;
		pop eax;
	}
}

void SelectMenu(int i) {
	__asm {
		push eax;
		push ecx;
		mov ecx, 0x00878B3C;
		mov ecx, [ecx];
		cmp ecx,0
		je RETPOINT;
		mov eax, i; // so dong bat dau tu 1
		push eax;
		mov eax, 0x004DEC40;
		call eax;
		RETPOINT:
		pop ecx;
		pop eax;
	}
}

void BuyingItem(int itemPos, int amount = 1, int location = 2, int xBag = 1, int yBag = 1) {
	itemPos += 1;
	__asm {
		push eax;
		push ecx;
		mov eax, yBag; //bag location
		push eax;
		mov eax, xBag; //bag location
		push eax;
		mov eax, amount; // amount
		push eax
		mov eax, location //inv id
		push eax
		mov eax, itemPos //item pos
		push eax
		mov ecx, 0x0092B1EC // const
		mov eax, 0x0064AF00 //func addr
		call eax
		pop ecx
		pop eax
	}
}

void closeInventory() {
	__asm {
		push eax;
		mov eax, 0x004968C0;
		call eax;
		pop eax;
	}
}

void Chat(char* szcmd) {
	if (!szcmd)
		return;
	__asm {
		push eax;
		mov eax, szcmd;
		push eax;
		mov eax, 0x00427E00;
		call eax;
		add esp, 0x04;
		pop eax;
	}
}

void closeChat() {
	__asm {
		push eax;
		push ecx;
		mov ecx, 0x0086E5E4;
		mov ecx, [ecx];
		cmp ecx, 0x0;
		je END;
		mov eax, 0x0041EDB0;
		call eax;
		END:
		pop ecx;
		pop eax;
	}
}

void Craft(int itemID) {
	__asm {
		push ecx;
		push eax;
		mov eax, 1;//so luong
		push eax;
		mov eax, itemID;//item id
		push eax;
		mov ecx, 0x0092B1EC;
		mov eax, 0x0064A980;
		call eax;
		pop ecx;
		pop eax;
	}
}

void SkipChat() {
	__asm {
		push eax;
		push ecx;
		mov ecx, 0x00871A00;
		mov eax, 0x00432D30;
		call eax;
		pop ecx;
		pop eax;
	}
}

void PickNPut(int SourceInv, int xS, int yS, int DestInv, int xD, int yD) {
	__asm {
		push eax;
		push ecx;
		//ecx = [[[[so2game.exe+46D8C4]+002719B0]+0]+4]
		mov ecx, ds:[0x0086D8C4];//ds:[0x0086D8C4];
		mov ecx, ds:[ecx + 0x002719B0];
		mov ecx, ds:[ecx];
		mov ecx, ds:[ecx + 0x4];//setup ecx

		mov eax, yD; //y
		push eax;
		mov eax, xD; //x
		push eax;
		mov eax, DestInv; //dest inv
		push eax;
		mov eax, yS; //y
		push eax;
		mov eax, xS; //x
		push eax;
		mov eax, SourceInv; //source inv
		push eax;
		mov eax, 0x005D8250;
		call eax;
		pop ecx;
		pop eax;
	}
}

void useHorse(int charAddr, int state){
	//5		Len ngua
	//6		Xuong ngua
	__asm{
		push eax;
		push ecx;
		push 0;
		push 0;
		push 0;
		push 0;
		push 0;
		push state;
		mov ecx, charAddr;
		mov eax, 0x005E9B90;
		call eax;
		pop ecx;
		pop eax;
	}
}

void SwitchRun(){
	__asm{
		push eax;
		push 0x2;
		mov eax,0x00658A80;
		call eax;
		pop eax;
		add esp,0x4;
	}
}

void ChooseNewChar(int order) {
	if (order == 4)
		order = 0x0DB8;
	else
		order = 0x17A4 + order * 0x01C0;
	__asm {
		push ecx;
		push eax;
		mov ecx, 0x00876FA4;
		mov ecx, [ecx];
		push 0x3D4CCCCD;
		push order;
		add dword ptr[esp], ecx;
		mov eax, 0x0043EE20;
		call eax;
		pop eax;
		pop ecx;
	}
}

void ChooseLoginChar(int order) {
	__asm {
		push ecx;
		push eax;
		mov ecx, 0x00876FA8;
		mov ecx, [ecx];
		push 0x1;
		push order;//slot 0->2
		mov eax, 0x0043FF00;
		call eax;
		pop eax;
		pop ecx;
	}
}

void LevelUp(int repeatTime=1) {
	for (int i=1;i<=repeatTime;i++)
		__asm {
			push ecx;
			push eax;
			mov ecx, 0x0092B1EC;
			mov eax, 0x0064CDD0;
			call eax;
			pop eax;
			pop ecx;
		}
}

void CreateGroup() {
	__asm {
		push ecx;
		push eax;
		mov ecx,ds:[0x0086D8C4];
		push 0x0;
		push 0x0;
		push 0x5;
		mov eax,0x00568F80;
		call eax;
		pop eax;
		pop ecx;
	}
}

void ChooseLoginCharEx(int order=0) {//order = 0 -> 8
	int page = order / 3;
	int slot = order % 3;
	__asm {
		push ecx;
		push eax;
		mov ecx, ds: [0x00876FA8];
		mov eax, page;
		mov dword ptr[ecx + 0x4684], eax;//page number 0-2
		mov eax, 0x00441600;
		call eax;

		mov ecx, ds : [0x00876FA8] ;
		push 0x1;
		mov eax,slot
		push eax;//slot
		mov eax, 0x0043FF00;
		call eax;
		pop eax;
		pop ecx;
	}
}

void nhanCode(){
	__asm{
		push ecx;
		push eax;
		mov ecx,ds:[0x00881CB0];
		cmp ecx,0;
		je END;
		mov eax,0x004FB680;
		call eax;
		END:
		pop eax;
		pop ecx;
	}
}
void useItem(int x, int y, int inv) {
	__asm {
		push ecx;
		push eax
		mov eax, y; //y (start at 0)
		push eax;
		mov eax, x; //x (start at 0)
		push eax;
		mov eax, inv; //inv id
		push eax;
		mov ecx, ds:[0x0086D8C4];
		mov ecx, dword ptr[ecx+0x2719B0];
		mov ecx, dword ptr[ecx+0x0];
		mov ecx, dword ptr[ecx+0x4];
		add ecx, 0x1b4;
		mov eax, 0x00643440;
		call eax;
		pop eax;
		pop ecx;
	}
}

void incStat(short sm, short tp, short nl, short gc, short lh) {
	short aData[5] = { sm,tp,nl,gc,lh};
	__asm {
		push ecx;
		push eax;
		push 0x00;
		lea eax,aData;
		push eax;
		push 0x0F;
		mov ecx, 0x0086D8C4
		mov ecx, [ecx] ;
		mov eax, [ecx];
		mov eax, [eax + 0x30];
		call eax;
		pop eax;
		pop ecx;
	}
}

void chooseServer() {//chua update
	__asm {
		push ecx;
		push eax;
		mov ecx, ds: [0x0087AFAC] ;
		cmp ecx, 0;
		je END;
		push 0x00872110;
		push 0x0;
		push 0x0;
		mov eax,0x00442CB0;
		call eax;
		mov eax,0x00445760;
		call eax;
		push 00;
		mov eax,0x00442BC0;
		call eax;
		add esp,4;
		END:
		pop eax;
		pop ecx;
	}
}

void throwItem(int ItemID) {
	__asm {
		push eax;
		mov eax, ItemID;
		//mov eax, [eax + 0x4]; //Use this if input is an Address
		push eax;
		mov eax, 0x005D8200;
		call eax;
		pop eax;
	}
}

void setItemPrice(int GridX, int GridY, int ItemPrice) {
	int PosNPrice[2];
	PosNPrice[0] = GridX + GridY*5;
	PosNPrice[1] = ItemPrice;
	__asm {
		push eax;
		push ecx;

		mov ecx, 0x80000000;
		mov eax, 0x004B6940;
		call eax; //Open self-Shop to avoid Crash

		mov ecx, [PosNPrice];
		push ecx; //Selling Item's Order
		mov ecx, ds:[0x0086D8C4];
		mov ecx, ds:[ecx+0x2719B0];
		mov ecx, ds:[ecx];
		mov ecx, ds:[ecx+0x4];
		add ecx, 0x1B4;
		mov eax,0x00646F80;
		call eax;//==> eax = ItemPosStructAddress (itemIndex:4bytes inv:4bytes x:4bytes y:4bytes)
		mov eax, [eax]; //=> ItemIndex
		
		push eax;
		mov ecx, ds:[0x0086D8C4];
		mov ecx, ds:[ecx + 0x002719DC];
		mov eax, 0x005523B0; //=> eax = ItemAddr
		call eax;

		mov ecx, eax;
		mov eax, ds:[PosNPrice + 0x4];
		push eax;//Price
		mov eax,0x00557D80; //orgin at 006500AA
		call eax;

		push 0x1;//??
		lea ecx, PosNPrice;
		push ecx;//sellcount:4bytes price:4bytes
		mov ecx, 0x0092B1EC;
		mov eax, 0x0064DB40;//orgin at 00650882
		call eax;

		mov ecx, ds:[PosNPrice + 0x4];
		push ecx;//Price
		push GridY;//Y
		push GridX;//X
		mov eax, 0x004B5E30;//orgin at 0046DAD7
		call eax;
		add esp, 0x0C;
		
		pop ecx;
		pop eax;
	}
}

void Sale(int mode) {
	int funcAddr;
	if (mode == 1)
	{
		// funcAddr = 0x006508A0; //Starting Sale
		_asm{
			push 0x1;
			mov ecx, 0x0092B1EC;
			mov eax, 0x0064DC60
			call eax;//sell anyway ¯\_(ツ)_/¯
		}
		return;
	}
	else
		funcAddr = 0x00650AA0; //Stopping Sale
								
	__asm {
		push eax;
		push 0x1;
		mov eax, funcAddr;
		call eax;
		add esp, 0x4;
		pop eax;
		}
}

void SplitItem(int InvID, int GridX, int GridY, int amount) {
	__asm {
		push eax;
		push ecx;
		mov eax, amount;//amount
		push eax;
		mov eax, GridY;//Y
		push eax;
		mov eax, GridX;//X
		push eax;
		mov eax, InvID;//InvID
		push eax;
		mov ecx, 0x0092B1EC;
		mov eax, 0x0064D2E0;
		call eax;
		pop ecx;
		pop eax;
	}
}

void MyShop(){
	__asm{
		push eax;
		push ecx;
		mov ecx, 0x80000000;
		mov eax, 0x004B6940;
		call eax; //Open self-Shop to avoid Crash
		pop ecx;
		pop eax;
	}
}

void Respawn() {
	__asm {
		push eax;
		push ecx;
		push 0;
		mov ecx, 0x008740D0;
		mov eax, 0x00434110;
		call eax;
		pop ecx;
		pop eax;
	}
}

void POpenShop(int PlayerID) {
	int volatile * const CurrP_ID = (int *)0x009E1150;
	*CurrP_ID = PlayerID;
	__asm {
		push eax;
		push ecx;
		mov eax, 0x00650E00;//Clear old shop
		call eax;
		mov eax, PlayerID;
		push eax;
		mov ecx, 0x0092B1EC;
		mov eax, 0x0064DCC0;
		call eax;
		pop ecx;
		pop eax;
	}
}

void PShopping(int OwnerID, int itemAddrBase) {
	__asm {
		push eax;
		push ecx;
		mov ecx, itemAddrBase;//item addr base
		mov eax, ds:[ecx + 0x9B4];//Price
		push eax;
		mov eax, ds:[ecx + 0x4];   //item id
		push eax;
		mov eax, OwnerID;   //owner id
		push eax;
		mov eax, 0x1;
		push eax;
		mov eax, 0x00650CB0;
		call eax;
		add esp, 10;
		pop ecx;
		pop eax;
	}
}
/////////////////////////////////////////////////
const UINT WM_HOOK_WRITE = RegisterWindowMessage(L"WM_HOOK_WRITE");
const UINT WM_HOOKEX = RegisterWindowMessage(L"WM_HOOKEX_RK");
#define pCW ((CWPSTRUCT*)lParam)

HINSTANCE                       hDll;

WNDPROC                         OldWndProc = NULL;
LRESULT CALLBACK        NewWndProc(HWND, UINT, WPARAM, LPARAM);

BOOL bHooked = 0;

BOOL APIENTRY DllMain(HANDLE hModule, DWORD uReason, LPVOID lpReserved)
{
	if (uReason == DLL_PROCESS_ATTACH)
	{
		hDll = (HINSTANCE)hModule;
		DisableThreadLibraryCalls(hDll);
	}
	return TRUE;
}

///////////////////////
UINT __stdcall GetMsg()
{
	return WM_HOOK_WRITE;
}
///////////////////////////////////////////////////////////////////////////////
LRESULT HookProc(int nCode, WPARAM wParam, LPARAM lParam)
{

	HWND hVLWnd = pCW->hwnd;
	HHOOK hHook = (HHOOK)pCW->wParam;
	if (nCode<0)             goto CALL_NEXTHOOK;
	if ((pCW->message == WM_HOOKEX) && pCW->lParam)
	{
		UnhookWindowsHookEx(hHook);
		if (bHooked)
			goto CALL_NEXTHOOK;
		wchar_t lib_name[MAX_PATH];
		GetModuleFileName(hDll, lib_name, MAX_PATH);
		if (!LoadLibrary(lib_name))
			goto CALL_NEXTHOOK;
		OldWndProc = (WNDPROC)SetWindowLong(hVLWnd, GWL_WNDPROC, (LONG)NewWndProc);
		if (OldWndProc == NULL) {
			FreeLibrary(hDll);
		}
		else
		{
			bHooked = TRUE;
		}
	}
	else if (pCW->message == WM_HOOKEX)
	{
		UnhookWindowsHookEx(hHook);
		if (!bHooked)
			goto CALL_NEXTHOOK;
		if (!SetWindowLong(hVLWnd, GWL_WNDPROC, (LONG)OldWndProc))
			goto CALL_NEXTHOOK;
		FreeLibrary(hDll);
		bHooked = FALSE;
	}
CALL_NEXTHOOK:
	return CallNextHookEx(hHook, nCode, wParam, lParam);
}
/////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK NewWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	if (uMsg == WM_HOOK_WRITE)
	{
		switch (wParam)
		{
		case cmd_setParam1:
			input1 = lParam;
			break;
		case cmd_setParam2:
			input2 = lParam;
			break;
		case cmd_setParam3:
			input3 = lParam;
			break;
		case cmd_setParam4:
			input4 = lParam;
			break;
		case cmd_setParam5:
			input5 = lParam;
			break;
		case cmd_setParam6:
			input6 = lParam;
			break;
		case cmd_setParam7:
			input7 = lParam;
			break;
		case cmd_Move:
			//Move(x,y,mode,idmap)
			Move(input1, input2, input3, lParam);
			break;
		case cmd_LoginS1:
			LoginStep_1();
			break;
		case cmd_LoginS3:
			LoginStep_3();
			break;
		case cmd_LoginS4:
			LoginStep_4(lParam);
			break;
		case cmd_SelectMenu:
			SelectMenu(lParam);
			break;
		case cmd_Shopping:
			BuyingItem(lParam, input1, input2, input3, input4);
			break;
		case cmd_Action:
			Action(input1, input2, input3, input4, input5, input6, input7,lParam);
			break;
		case cmd_closeInv:
			closeInventory();
			break;
		case cmd_closeChat:
			closeChat();
			break;
		case cmd_Craft:
			if (lParam == 0) lParam += 1;
			Craft(lParam);
			break;
		case cmd_SkipChat:
			SkipChat();
			break;
		case cmd_PickNPut:
			PickNPut(input1, input2, input3, input4, input5, input6);
			break;
		case cmd_UseHorse:
			useHorse(input1,lParam);
			break;
		case cmd_SwitchRun:
			SwitchRun();
			break;
		case cmd_ChooseNewChar:
			ChooseNewChar(lParam);
			ChooseNewChar(4);
			break;
		case cmd_ChooseLoginChar:
			ChooseLoginCharEx(lParam);
			break;
		case cmd_LevelUp:
			LevelUp(lParam);
			break;
		case cmd_CreateGroup:
			CreateGroup();
			break;
		case cmd_nhanCode:
			nhanCode();
			break;
		case cmd_useItem:
			useItem(input1,input2,lParam);
			break;
		case cmd_incStat:
			incStat(input1, input2, input3, input4, lParam);
			break;
		case cmd_chooseServer:
			chooseServer();
			break;
		case cmd_throwItem:
			throwItem(lParam);
			break;
		case cmd_setItemPrice:
			setItemPrice(input1, input2, lParam);
			break;
		case cmd_sale:
			Sale(lParam);
			break;
		case cmd_SplitItem:
			SplitItem(input1, input2, input3, lParam);
			break;
		case cmd_MyShop:
			MyShop();
			break;
		case cmd_Respawn:
			Respawn();
			break;
		case cmd_POpenShop:
			POpenShop(lParam);
			break;
		case cmd_PShopping:
			PShopping(input1,lParam);
			break;
		case 80:
			strcpy(szData, "");
			break;
		case 81:
			sprintf(szData, "%s%c", szData, lParam);
			break;
		case 82:
			Chat(szData);
			break;
		}
	}

	return CallWindowProc(OldWndProc, hWnd, uMsg, wParam, lParam);
}
/////////////////////////////////////////////////////////////
int __stdcall InjectDll(HWND hWnd)
{
	if (!IsWindow(hWnd))
		return 0;
	HHOOK hHook = SetWindowsHookEx(WH_CALLWNDPROC, (HOOKPROC)HookProc, hDll, GetWindowThreadProcessId(hWnd, NULL));
	if (hHook == NULL)
		return 0;
	SendMessage(hWnd, WM_HOOKEX, WPARAM(hHook), 1);
	return 1;
}

int __stdcall UnmapDll(HWND hWnd)
{
	if (!IsWindow(hWnd))
		return 0;
	HHOOK hHook = SetWindowsHookEx(WH_CALLWNDPROC, (HOOKPROC)HookProc, hDll, GetWindowThreadProcessId(hWnd, NULL));
	if (hHook == NULL)
		return 0;
	SendMessage(hWnd, WM_HOOKEX, (WPARAM)hHook, 0);
	return 1;
}
/////////////////////////////////////////////////////////
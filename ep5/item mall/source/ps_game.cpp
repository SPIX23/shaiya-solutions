#include "stdafx.h"
#include "ps_game.h"
#include "hook.h"
#include "database.h"

PITEMMALL g_pItemMall;
CDataBase g_DBobj;

//naked one
DWORD dwReturnAddr1 = 0x0047D157;
DWORD dwGetPointCall = 0;
//naked two
DWORD dwReturnAddr2 = 0x00488025;
DWORD dwFalseAddr = 0x00488027;
DWORD dwCheckPoint = 0;
//naked three
DWORD dwCallThree = NULL;
DWORD dwReturnAddr3 = 0x00488D5F;

ITEMMALLFIX_API int Start(void)
{
	return 0;
}

__declspec(naked) void Naked_One()
{
	_asm
	{
		pushad
		lea eax,[ecx+0x5AC0]
		push eax                //point addr
		mov eax,[ecx+0x582C]
		push eax                //uid
		call dwGetPointCall
		add esp,0x8
		popad 
		//orginal code
		xor ebp,ebp
		cmp byte ptr[esi+0xA],0x0
		jmp dwReturnAddr1
	}
}

__declspec(naked) void Naked_Two()
{
	_asm
	{
		pushad
		push ecx                //use point
		mov ecx,[edi+0x582C]
		push ecx                //uid
		call dwCheckPoint
		add esp,0x8
		cmp al,0x1         
		popad
		jne _false
		//orginal code
		cmp ecx,dword ptr[edi+0x5AC0]
		jmp dwReturnAddr2
	_false:
		jmp dwFalseAddr
	}
}

__declspec(naked) void Naked_Three()
{
	_asm
	{
		pushad
		mov eax,dword ptr[edi+0x582C]
		push eax                        //uid
		call dwCallThree            
		add esp,0x4
		popad
		jmp dwReturnAddr3
	}
}

void Clear(DWORD dwUid)
{
	::CreateThread(0, 0, ThreadProc2, (PVOID)dwUid, 0, 0);
}

void  GetPoint(DWORD dwUid, PVOID pAddr)
{
	CString szSql;
	szSql.Format(L"select point from ps_userdata.dbo.users_master where useruid=%d", dwUid);
	*((DWORD*)pAddr)=_tcstoul(g_DBobj.ExeSqlByCommand(szSql, L"point"),0,10);
}

BOOL  CheckPoint(DWORD dwUid, DWORD dwUsePoint)
{
	PDWORD pPoint;
	_asm
	{
		lea eax,[edi+0x5AC0]
		mov pPoint,eax
	}
	CString szSql;
	szSql.Format(L"select point from ps_userdata.dbo.users_master where useruid=%d", dwUid);
	DWORD dwPoint= _tcstoul(g_DBobj.ExeSqlByCommand(szSql, L"point"), 0, 10);
	*pPoint = dwPoint;                           
	if (dwUsePoint > dwPoint) return FALSE;            
	
	return TRUE;
}

DWORD WINAPI ThreadProc1(_In_  LPVOID lpParameter)
{
	//naked three
	dwGetPointCall = (DWORD)GetPoint;
	dwCheckPoint = (DWORD)CheckPoint;
	dwCallThree = (DWORD)Clear;
	//link database
	if (!g_DBobj.LinkDataBase()) return 0;
	//define hooks
	CMyInlineHook HookobjOne;
	CMyInlineHook HookobjTwo;
	CMyInlineHook HookobjThree;
	HookobjOne.Hook ((PVOID)0x0047D151, Naked_One, 6);    
    HookobjTwo.Hook ((PVOID)0x0048801F, Naked_Two, 6);     
	HookobjThree.Hook((PVOID)0x0048876F, Naked_Three);
	return 0;
}

DWORD WINAPI ThreadProc2(_In_  LPVOID lpParameter)
{
	DWORD dwUid = (DWORD)lpParameter;
	char buff[90] = { 0 };
	ZeroMemory(buff, 90);

	*(PDWORD(&buff[4])) = DWORD(&buff[12]);

	*(PDWORD(&buff[12])) = 0x1B02000B;

	*(PDWORD(&buff[16])) = dwUid;

	DWORD dwTempCall = 0x00406960;
	DWORD dwBuffAddr = (DWORD)buff;

	_asm
	{
		push dwBuffAddr
		mov ecx,0x0
		call dwTempCall
	}
	return 0;
}
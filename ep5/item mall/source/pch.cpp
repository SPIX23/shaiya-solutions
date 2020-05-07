#include "pch.h"
#include "mall.h"
#include "database.h"

void* Hook(DWORD address, int length, DWORD target);

PITEMMALL g_pItemMall;
CDataBase g_DBobj;

DWORD dwReturnAddr1 = 0x47D157;
DWORD dwGetPoint = 0;
DWORD dwReturnAddr2 = 0x488025;
DWORD dwFalseAddr = 0x488027;
DWORD dwCheckPoint = 0;
DWORD dwReturnAddr3 = 0x488D5F;
DWORD dwUpdatePoint = 0;

MALL_API int mallStart(void)
{
	return 0;
}

__declspec(naked) void mallHook1()
{
	_asm
	{
		pushad
		lea eax,[ecx+0x5AC0]
		push eax               
		mov eax,[ecx+0x582C]
		push eax               
		call dwGetPoint
		add esp,0x8
		popad
		//orginal code
		xor ebp,ebp
		cmp byte ptr[esi+0xA],0x0
		jmp dwReturnAddr1
	}
}

__declspec(naked) void mallHook2()
{
	_asm
	{
		pushad
		push ecx               
		mov ecx,[edi+0x582C]
		push ecx               
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

__declspec(naked) void mallHook3()
{
	_asm
	{
		pushad
		mov eax,dword ptr[edi+0x582C]
		push eax                        
		call dwUpdatePoint
		add esp,0x4
		popad
		jmp dwReturnAddr3
	}
}

void getPoint(DWORD dwUid, PVOID pAddr)
{
	CString szSql;
	szSql.Format(L"select point from ps_userdata.dbo.users_master where useruid=%d", dwUid);
	*((DWORD*)pAddr) = _tcstoul(g_DBobj.ExeSqlByCommand(szSql, L"point"), 0, 10);
}

BOOL checkPoint(DWORD dwUid, DWORD dwUsePoint)
{
	PDWORD pPoint;
	_asm
	{
		lea eax,[edi+0x5AC0]
		mov pPoint,eax
	}
	CString szSql;
	szSql.Format(L"select point from ps_userdata.dbo.users_master where useruid=%d", dwUid);
	DWORD dwPoint = _tcstoul(g_DBobj.ExeSqlByCommand(szSql, L"point"), 0, 10);
	*pPoint = dwPoint;
	if (dwUsePoint > dwPoint) return FALSE;

	return TRUE;
}

DWORD __stdcall mallThread2(_In_ LPVOID lpParameter)
{
	DWORD dwUid = (DWORD)lpParameter;
	char buff[90] = { 0 };
	ZeroMemory(buff, 90);

	*(PDWORD(&buff[4])) = DWORD(&buff[12]);
	*(PDWORD(&buff[12])) = 0x1B02000B;
	*(PDWORD(&buff[16])) = dwUid;

	DWORD dwTempCall = 0x406960;
	DWORD dwBuffAddr = (DWORD)buff;

	_asm
	{
		push dwBuffAddr
		mov ecx,0x0
		call dwTempCall
	}
	return 0;
}

void updatePoint(DWORD dwUid)
{
	CreateThread(NULL, 0, mallThread2, (PVOID)dwUid, NULL, 0);
}

DWORD __stdcall mallThread1(_In_ LPVOID lpParameter)
{
	dwGetPoint = (DWORD)getPoint;
	dwCheckPoint = (DWORD)checkPoint;
	dwUpdatePoint = (DWORD)updatePoint;

	if (!g_DBobj.LinkDataBase()) return 0;

	Hook(0x47D151, 6, (DWORD)mallHook1);
	Hook(0x48801F, 6, (DWORD)mallHook2);
	Hook(0x48876F, 5, (DWORD)mallHook3);

	return 0;
}

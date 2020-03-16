#include "stdafx.h"
#include "hook.h"

CMyInlineHook::CMyInlineHook(void)
{
	ZeroMemory(m_byOriginalCode,_countof(m_byOriginalCode)*sizeof(BYTE));
}

BOOL CMyInlineHook::Hook(PVOID pOriginalAddr,PVOID pNewAddr,int nSize)
{
	m_nSize=nSize;
	DWORD dwOldProtect;
	::VirtualProtect(pOriginalAddr, m_nSize, PAGE_READWRITE, &dwOldProtect);
	::ReadProcessMemory(GetCurrentProcess(), pOriginalAddr,m_byOriginalCode, m_nSize, NULL);
	::VirtualProtect(pOriginalAddr, m_nSize, dwOldProtect, &dwOldProtect);
	M_pOriginalAddr=pOriginalAddr;

	m_byJmpAsmCode[0]= 0xE9;
	*(PDWORD)&(m_byJmpAsmCode[1]) = (DWORD)pNewAddr - (DWORD)pOriginalAddr - 5;
	for(int i=5;i<nSize;i++)
	{
		m_byJmpAsmCode[i]= 0x90;
	}
	::VirtualProtect(pOriginalAddr, m_nSize, PAGE_READWRITE, &dwOldProtect);
	::WriteProcessMemory(GetCurrentProcess(), pOriginalAddr, m_byJmpAsmCode, m_nSize, NULL);
	::VirtualProtect(pOriginalAddr, m_nSize, dwOldProtect, &dwOldProtect);
	return TRUE;
}

BOOL CMyInlineHook::UnHook()
{
	if((ULONGLONG)m_byOriginalCode==0) return FALSE;
	DWORD dwOldProtect;
	::VirtualProtect(M_pOriginalAddr, m_nSize, PAGE_READWRITE, &dwOldProtect);
	::WriteProcessMemory(GetCurrentProcess(), M_pOriginalAddr, m_byOriginalCode, m_nSize, NULL);
	::VirtualProtect(M_pOriginalAddr, m_nSize, dwOldProtect, &dwOldProtect);
	return TRUE;
};

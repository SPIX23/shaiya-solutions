#include "pch.h"
#include "database.h"

CDataBase::CDataBase(void)
{
	m_vecDATABASE.clear();
	m_dwIndex=0;
}

BOOL CDataBase::LinkDataBase()
{
   CoInitialize(NULL);
   try
   {
	   HRESULT hr1 = m_pConnect.CreateInstance(L"ADODB.Connection");
	   if (FAILED(hr1))
	   {
		   return FALSE;
	   }
   }
	catch (_com_error)
	{
		OutputDebugString(L"");
	}
	OutputDebugString(L"");
	CString szLink;
	szLink.Format(L"Provider=SQLOLEDB;Server=127.0.0.1;Database=PS_UserData;Uid=yourusername1234;Pwd=yourpassword1234;");
	m_pConnect->Open(_bstr_t(szLink), _bstr_t(L""), _bstr_t(L""), adOpenUnspecified);
	return TRUE;
}

BOOL CDataBase::LinkDataBase(CString ip,CString DbName,CString UserName,CString Pw)
{
	try
	{
		m_pConnect.CreateInstance(L"ADODB.Connection");
		CString szLink;
		szLink.Format(L"Provider=SQLOLEDB;Server=127.0.0.1;Database=PS_UserData;Uid=yourusername1234;Pwd=yourpassword1234;", ip, DbName, UserName, Pw);
		m_pConnect->Open(_bstr_t(szLink), _bstr_t(L""), _bstr_t(L""), adModeUnknown);
	}
	catch (_com_error)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CDataBase::ExeSqlByCon(CString szSql)
{
	try{
		m_pConnect->Execute(_bstr_t(szSql),NULL,1);
	}
	catch(_com_error)
	{
		return FALSE;
	}
	return TRUE;
}

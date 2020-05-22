#pragma once
#if defined(ADO2_OLD)
#import "msado20.tlb" no_namespace rename("EOF", "adoEOF") 
#else   
#import "msado15.dll" no_namespace rename("EOF", "adoEOF") 
#endif

#include "pch.h"

using std::vector;

typedef struct _DATABASEINFO
{
	CString szName;        
	vector<CString> vecValue;

}DATABASEINFO,*PDATABASEINFO;

class CDataBase
{
public:
	CDataBase(void);
	BOOL LinkDataBase(CString ip,CString DbName,CString UserName,CString Pw);
	BOOL LinkDataBase();
	BOOL ExeSqlByCon(CString szSql);

	CString ExeSqlByCommand(CString szSql, CString szFieldName)
	{
		_RecordsetPtr  pRecord;
		_CommandPtr pCommand;
		_variant_t  AffectedLines;
		pCommand.CreateInstance(__uuidof(Command));
		pCommand->CommandText = _bstr_t(szSql);
		pCommand->ActiveConnection = m_pConnect;
		pRecord = pCommand->Execute(&AffectedLines, NULL, adCmdText);

		if (pRecord->GetState())
		{
			_variant_t stcSign = pRecord->GetadoEOF();
			while (stcSign.boolVal != -1)
			{
				_variant_t varTemp = pRecord->GetCollect(_bstr_t(szFieldName));
				if (varTemp.vt != VT_NULL)
				{
					CString szTemp = varTemp;
					return szTemp;
				}
				pRecord->MoveNext();
				stcSign = pRecord->GetadoEOF();
			}
			return "0";
		}
		return "0";
	}

	BOOL ExeSqlByCommand(CString szSql)
	{
		try
		{
			_RecordsetPtr  pRecord;
			_CommandPtr pCommand;
			_variant_t  AffectedLines;
			pCommand.CreateInstance(__uuidof(Command));
			pCommand->CommandText = _bstr_t(szSql);
			pCommand->ActiveConnection = m_pConnect;
			pRecord = pCommand->Execute(&AffectedLines, NULL, adCmdText);

			if (pRecord->GetState()) ExpainRecord(pRecord);
		}
		catch (_com_error)
		{
			return FALSE;
		}
		return TRUE;
	}

	BOOL CheckExistBySqlCmd(CString szSql)
	{
		try
		{
			_RecordsetPtr  pRecord;
			_CommandPtr pCommand;
			_variant_t  AffectedLines;
			pCommand.CreateInstance(__uuidof(Command));
			pCommand->CommandText = _bstr_t(szSql);
			pCommand->ActiveConnection = m_pConnect;
			pRecord = pCommand->Execute(&AffectedLines, NULL, adCmdText);

			if (pRecord->GetState())
				return TRUE;
			else
				return FALSE;
		}
		catch (_com_error)
		{
			return FALSE;
		}
		return TRUE;
	}

	BOOL ExpainRecord(_RecordsetPtr &pRecord)
	{
		Fields* pFields; 
		pRecord->get_Fields(&pFields);
		long nCount=pFields->GetCount();
		for(long i=0;i<nCount;i++)
		{
			DATABASEINFO stcTemp;
			BSTR         szName;
			pFields->Item[i]->get_Name(&szName);
			stcTemp.szName=szName;
			m_vecDATABASE.push_back(stcTemp);
		}

		_variant_t stcSign=pRecord->GetadoEOF();

		while(stcSign.boolVal!=-1)
		{
			for(long i=0;i<nCount;i++)
			{	
				_variant_t varTemp=pRecord->GetCollect(_bstr_t(m_vecDATABASE[i].szName));
				if(varTemp.vt!=VT_NULL)
				{
					CString    szTemp=varTemp;
					m_vecDATABASE[i].vecValue.push_back(szTemp);
				}		
			}
			pRecord->MoveNext();
			m_nRecordCount++;
			stcSign=pRecord->GetadoEOF();
		}
		m_nRecordCount--;
		return TRUE;
	}

	CString GetValueByField(CString szField)
	{
		for(DWORD i=0;i<m_vecDATABASE.size();i++)
		{
			if(szField.Compare(m_vecDATABASE[i].szName)==0)
			{
				return m_vecDATABASE[i].vecValue[m_dwIndex];
			}
		}
		return "";
	}

	void SetSeek(DWORD dwSeek)
	{
		m_dwIndex=dwSeek;
	}

	void MoveNext()
	{
		m_dwIndex++;
	}

	BOOL IsEmpty()
	{
		if(m_dwIndex>=m_vecDATABASE[0].vecValue.size()) 
		{
			return TRUE;
		}
		return FALSE;
	}
public:
	_ConnectionPtr        m_pConnect;   
	vector<_DATABASEINFO> m_vecDATABASE;
	DWORD                 m_dwIndex;   
	DWORD                 m_nRecordCount;
};
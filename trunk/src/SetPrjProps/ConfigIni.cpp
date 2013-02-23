#include "StdAfx.h"
#include "ConfigIni.h"


DWORD CConfigIni::GetItemValue( const std::wstring& strSection,const std::wstring& ItemName, std::wstring& ItemValue )
{
	TCHAR szBuff[_MAX_PATH*2];
    memset(szBuff,'\0',_MAX_PATH*2*sizeof(TCHAR));
	DWORD dwRet = GetPrivateProfileString(strSection.c_str(),ItemName.c_str(),NULL,szBuff,_MAX_PATH*2,m_strIniFile.c_str()); //读取ini文件中相应字段的内容
    ItemValue =  szBuff;
	return dwRet;
}

DWORD CConfigIni::SetItemValue( const std::wstring& strSection,const std::wstring& ItemName,const std::wstring& ItemValue )
{
   return WritePrivateProfileString(strSection.c_str(),ItemName.c_str(),ItemValue.c_str(),m_strIniFile.c_str());
}



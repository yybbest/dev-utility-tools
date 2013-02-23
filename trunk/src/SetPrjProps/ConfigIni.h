#pragma once

#include <string>

#define  COMMON_SETTING                       std::wstring(_T("Common"))
#define  OUTPUT_DIR                           std::wstring(_T("OutputDirectory"))
#define  IN_DIR                               std::wstring(_T("IntermediateDirectory"))

#define  PRECOMPILE_HEAD_FILE                 std::wstring(_T("PrecompiledHeaderFile"))

#define  ASM_LIST                             std::wstring(_T("AssemblerListingLocation"))

#define  OBJ_FILE                             std::wstring(_T("ObjectFile"))

#define  PROGRAM_DB_VC_FILE                   std::wstring(_T("ProgramDataBaseVcFile"))

#define  ADDITION_INC                         std::wstring(_T("AdditionalIncludeDirectories"))

#define  ADDITION_LIB                         std::wstring(_T("AdditionalLibraryDirectories"))

#define  BSC_FILE                             std::wstring(_T("OutputFile"))

#define  PROGRAM_DB_FILE                   std::wstring(_T("ProgramDatabaseFile"))


// ini文件读取类
class CConfigIni
{
public:

	CConfigIni(const std::wstring& strIniFile)
	{
        m_strIniFile = strIniFile;
	}

	virtual ~CConfigIni(void)
	{

	}

	DWORD GetItemValue(const std::wstring& strSection,const std::wstring& ItemName, std::wstring& ItemValue);

	DWORD SetItemValue(const std::wstring& strSection,const std::wstring& ItemName,const std::wstring& ItemValue);

protected:

	std::wstring m_strIniFile;

};

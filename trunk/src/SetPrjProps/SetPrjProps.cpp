// SetPrjProps.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "SetPrjProps.h"

#include <ShellAPI.h>
#include <fstream>
#include <vector>
#include <pugixml.hpp>

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

#include "ConfigIni.h"

//	说明：显示用法。目前只能在Windows环境下使用，显示MessageBox。
//	参数：
//		pszTitle	: 标题
//		pszFormat	: 格式化串 (一般是用法串)
//		后面必须是字符串型参数
BOOL AidDisplayUsage(const TCHAR *pszTitle, const TCHAR *pszFormat, ...)
{
	TCHAR buffer[2048] = _T("");
	va_list arg_ptr;

	va_start (arg_ptr, pszFormat);
	vswprintf_s(buffer, pszFormat, arg_ptr);
	va_end (arg_ptr);

	::MessageBox(GetDesktopWindow(), buffer, pszTitle, MB_OK);

	return TRUE;
}

BOOL ModifySlnSetting(std::wstring strIniFile,std::wstring strSlnFile)
{
	::SetCursor(::LoadCursor(NULL,IDC_WAIT));
	// 读取ini配置文件
	CConfigIni ini(strIniFile);

	std::wstring strOutputValue;
	ini.GetItemValue(COMMON_SETTING,OUTPUT_DIR,strOutputValue);

	std::wstring strInDirValue;
	ini.GetItemValue(COMMON_SETTING,IN_DIR,strInDirValue);

	std::wstring strPrecompiledHeaderFile;
	ini.GetItemValue(COMMON_SETTING,PRECOMPILE_HEAD_FILE,strPrecompiledHeaderFile);

	std::wstring strAsmList;
	ini.GetItemValue(COMMON_SETTING,ASM_LIST,strAsmList);

	std::wstring strObjFile;
	ini.GetItemValue(COMMON_SETTING,OBJ_FILE,strObjFile);

	std::wstring strProDBVcFile;
	ini.GetItemValue(COMMON_SETTING,PROGRAM_DB_VC_FILE,strProDBVcFile);

	std::wstring strIncPath;
	ini.GetItemValue(COMMON_SETTING,ADDITION_INC,strIncPath);

	std::wstring strLibPath;
	ini.GetItemValue(COMMON_SETTING,ADDITION_LIB,strLibPath);

	std::wstring strBscPath;
	ini.GetItemValue(COMMON_SETTING,BSC_FILE,strBscPath);

	std::wstring strProDBFile;
	ini.GetItemValue(COMMON_SETTING,PROGRAM_DB_FILE,strProDBFile);

	// 读取解决方案文件

	FILE *stream;
	TCHAR szBuff[3*_MAX_PATH];

	std::vector<std::wstring> vecProject;
	std::wstring strSlnDir = strSlnFile.substr(0,strSlnFile.rfind('\\')+1);

	if( (stream = _tfopen(strSlnFile.c_str(),_T("r"))) != NULL )
	{
		memset(szBuff,'\0',_MAX_PATH*3*sizeof(TCHAR));

		//		while(!infile.fail())
		while(_fgetts( szBuff,_MAX_PATH*3*sizeof(TCHAR), stream ) )
		{
			if(_tcscmp(szBuff,_T("Global"))==0)
				break;
			std::wstring strLine = szBuff;
			std::wstring strSubLine = strLine.substr(0,7);
			if(_tcscmp(strSubLine.c_str(),_T("Project"))!=0)
				continue;

			size_t indexCh1a = strLine.find(',');
			std::wstring strSuffix = _T("vcproj");
			size_t indexCh1b = strLine.find (strSuffix.c_str(),6);
			if ( indexCh1b == std::wstring::npos )
				continue;

			size_t tCount  = indexCh1b-1 - indexCh1a;
			std::wstring strVcProjectFile = strLine.substr(indexCh1a+1,tCount);
			strVcProjectFile = strVcProjectFile.substr(strVcProjectFile.find('"')+1,strVcProjectFile.size());
			strVcProjectFile +=strSuffix;
			// 判断工程文件是否存在，工程文件采用相对路径或绝对路径，先检查相对路径
			std::wstring strVcProjectFullPath = strSlnDir+strVcProjectFile;
			
			std::wstring strRealVcProjectPath; // = strVcProjectPath;
			if(::GetFileAttributes(strVcProjectFullPath.c_str())==-1)
			{
                if(::GetFileAttributes(strVcProjectFile.c_str())!=-1)
                    vecProject.push_back(strVcProjectFile);
			}
			else
			{
			     vecProject.push_back(strVcProjectFullPath);
			}
		}
	}

	if (vecProject.empty())
		return 0;

	for (size_t i = 0;i<vecProject.size();i++)
	{
		// 读取工程文件
		pugi::xml_document vc_proj_file;
		std::wstring strXmlPath = vecProject[i];

	  /*	pugi::xml_parse_result ret = vc_proj_file.load_file(strXmlPath.c_str());
		*/

		std::locale::global(std::locale("chs"));  
//		const std::wstring strFilePath = _T(strXmlPath.c_str());  
		std::wifstream stream(strXmlPath.c_str());  
//		pugi::xml_document doc;  
		pugi::xml_parse_result ret = vc_proj_file.load(stream);  
		if (pugi::status_ok!=ret.status)
			continue;

		pugi::xml_node ConfigurationsNode = vc_proj_file.child(_T("VisualStudioProject")).child(_T("Configurations"));

		for (pugi::xml_node ConfigNode = ConfigurationsNode.first_child(); ConfigNode; ConfigNode = ConfigNode.next_sibling())
		{
			if(_tcscmp(ConfigNode.name(),_T("Configuration"))==0)
			{
				pugi::xml_attribute attOutput = ConfigNode.attribute(_T("OutputDirectory"));
				attOutput.set_value(strOutputValue.c_str());
				pugi::xml_attribute attInDir = ConfigNode.attribute(_T("IntermediateDirectory"));
				attInDir.set_value(strInDirValue.c_str());

				for (pugi::xml_node ToolNode = ConfigNode.first_child(); ToolNode; ToolNode = ToolNode.next_sibling())
				{
					if(_tcscmp(ToolNode.name(),_T("Tool"))==0)
					{
						pugi::xml_attribute attName = ToolNode.attribute(_T("Name"));
						std::wstring strName = attName.value();

						if (strName==std::wstring(_T("VCCLCompilerTool")))
						{
							pugi::xml_attribute attPreCompileHeadFile = ToolNode.attribute(_T("PrecompiledHeaderFile"));
							attPreCompileHeadFile.set_value(strPrecompiledHeaderFile.c_str());
							pugi::xml_attribute attAsm = ToolNode.attribute(_T("AssemblerListingLocation"));
							attAsm.set_value(strAsmList.c_str());
							pugi::xml_attribute attObjFile = ToolNode.attribute(_T("ObjectFile"));
							attObjFile.set_value(strObjFile.c_str());
							pugi::xml_attribute attProDBFile = ToolNode.attribute(_T("ProgramDataBaseFileName"));
							attProDBFile.set_value(strProDBVcFile.c_str());
							pugi::xml_attribute attInc = ToolNode.attribute(_T("AdditionalIncludeDirectories"));
							if (NULL!=attInc)
							{
								attInc.set_value(strIncPath.c_str());
							}
							else
							{
								attInc = ToolNode.append_attribute(_T("AdditionalIncludeDirectories"));
								attInc.set_value(strIncPath.c_str());
							}
						}
						else if (strName==std::wstring(_T("VCLinkerTool")))
						{
							pugi::xml_attribute attLib = ToolNode.attribute(_T("AdditionalLibraryDirectories"));
							if (NULL!=attLib)
							{
								attLib.set_value(strLibPath.c_str());
							}
							else
							{
								attLib = ToolNode.append_attribute(_T("AdditionalLibraryDirectories"));
								attLib.set_value(strLibPath.c_str());
							}
							pugi::xml_attribute attProDB = ToolNode.attribute(_T("ProgramDatabaseFile"));
							if (NULL!=attLib)
							{
								attProDB.set_value(strProDBFile.c_str());
							}
							else
							{
								attProDB = ToolNode.append_attribute(_T("ProgramDatabaseFile"));
								attProDB.set_value(strProDBFile.c_str());
							}
						}
						else if (strName==std::wstring(_T("VCBscMakeTool")))
						{
							pugi::xml_attribute attBsc = ToolNode.attribute(_T("OutputFile"));
							if (NULL!=attBsc)
							{
								attBsc.set_value(strBscPath.c_str());
							}
							else
							{
								attBsc = ToolNode.append_attribute(_T("OutputFile"));
								attBsc.set_value(strBscPath.c_str());
							}
						}
					}
				}
			}
		}
		vc_proj_file.save_file(strXmlPath.c_str());
	}
		
	::SetCursor(::LoadCursor(NULL,IDC_ARROW));
	return TRUE;
}

BOOL ParseCmdLine(LPTSTR lpCmdLine,std::wstring& strIni,std::wstring& strSln)
{
	std::wstring strCmdLine = lpCmdLine;
    std::wstring strSuffix = _T(".ini");
	size_t indexCh1b = strCmdLine.find (strSuffix.c_str(),4);
	if ( indexCh1b == std::wstring::npos )
	{
		::MessageBox(GetDesktopWindow(),_T("缺少ini文件参数"),_T("提示"), MB_OK|MB_ICONINFORMATION);
		return FALSE;
	}
	if ((indexCh1b+4)>=strCmdLine.size())
	{
		::MessageBox(GetDesktopWindow(),_T("缺少ini文件参数"),_T("提示"), MB_OK|MB_ICONINFORMATION);
		return FALSE;
	}
    strIni = strCmdLine.substr(0,indexCh1b+4);

	if ((indexCh1b+5)>=strCmdLine.size())
	{
		::MessageBox(GetDesktopWindow(),_T("缺少sln文件参数"),_T("提示"), MB_OK|MB_ICONINFORMATION);
		return FALSE;
	}
	std::wstring strLeft = strCmdLine.substr(indexCh1b+5,strCmdLine.size());
	strSuffix = _T(".sln");
	indexCh1b = strLeft.find (strSuffix.c_str(),4);
	if ( indexCh1b == std::wstring::npos )
	{
		::MessageBox(GetDesktopWindow(),_T("缺少sln文件参数"),_T("提示"), MB_OK|MB_ICONINFORMATION);
		return FALSE;
	}
    strSln = strLeft.substr(0,indexCh1b+4);
	// 截取多余的空格
	strSln.erase(0,strSln.find_first_not_of(_T(" ")));
	return TRUE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 在此放置代码。

	int argc = 0;
	LPWSTR* lpszArgv = NULL;

    std::wstring strIni;
	std::wstring strSln;

    if(!ParseCmdLine(lpCmdLine,strIni,strSln))
	{
		AidDisplayUsage(_T("Usage"),_T("%s <IniFile> <SlnFile>\n"),_T("批量修改工程属性"));
		return 1;
	}
	if(::GetFileAttributes(strIni.c_str())==-1)
	{
		//文件不存在
		std::wstring strInfo = strIni + std::wstring(_T("不存在"));
		::MessageBox(GetDesktopWindow(),strInfo.c_str(),_T("提示"), MB_OK|MB_ICONINFORMATION);
		return 1;
	}

	if(::GetFileAttributes(strSln.c_str())==-1)
	{
		//文件不存在
		std::wstring strInfo = strSln + std::wstring(_T("不存在"));
		::MessageBox(GetDesktopWindow(),strInfo.c_str(),_T("提示"), MB_OK|MB_ICONINFORMATION);
		return 1;
	}

	if(!ModifySlnSetting(strIni,strSln))
	{
		::MessageBox(GetDesktopWindow(),_T("修改工程属性失败"),_T("提示"), MB_OK|MB_ICONWARNING);
		return 1;
	}
	else
	{
		return 0;
	}

	//lpszArgv = CommandLineToArgvW(lpCmdLine, &argc);
	//if (argc >= 2)
	//{
	//	if(::GetFileAttributes(lpszArgv[0])==-1)
	//	{
	//		//文件不存在
	//		::MessageBox(GetDesktopWindow(),lpszArgv[0],_T("提示"), MB_OK|MB_ICONINFORMATION);
	//		return 1;
	//	}

	//	if(::GetFileAttributes(lpszArgv[1])==-1)
	//	{
	//		//文件不存在
	//		::MessageBox(GetDesktopWindow(),lpszArgv[1],_T("提示"), MB_OK|MB_ICONINFORMATION);
	//		return 1;
	//	}
	//	if(!ModifySlnSetting(lpszArgv[0],lpszArgv[1]))
	//	{
	//		::MessageBox(GetDesktopWindow(),_T("修改工程属性失败"),_T("提示"), MB_OK|MB_ICONWARNING);
	//		return 1;
	//	}
	//	else
	//	{
	//		return 0;
	//	}
	//}
	//else
	//{
	//	AidDisplayUsage(_T("Usage"),_T("%s <IniFile> <SlnFile>\n"),_T("批量修改工程属性"));
	//	return 1;
	//}

	return 0;
}


#include "StdAfx.h"
#include "OutputFilePlugin.h"

#include <iostream>
#include <tchar.h>
#include <boost/format.hpp>

#include "..\DataExchange\stat_info.h"

COutputFilePlugin::COutputFilePlugin(const std::string& strID ):IPluginObj(strID)
{

}

COutputFilePlugin::~COutputFilePlugin(void)
{
}

BOOL COutputFilePlugin::ProcessData( boost::any& anyData )
{
    if(anyData.type() == typeid(stStatInfo))  
	{
        stStatInfo stInfo  = boost::any_cast<stStatInfo>(anyData); 
        
		TCHAR szAppName[MAX_PATH];
		:: GetModuleFileName(NULL,szAppName, MAX_PATH);
		TCHAR szDrive[_MAX_DRIVE];
		TCHAR szDir[_MAX_DIR];
		TCHAR szBinName[_MAX_FNAME];
		TCHAR szExt[_MAX_EXT];
		_tsplitpath(szAppName,szDrive,szDir,szBinName,szExt); 
		std::string strRetFile = std::string(szDrive) + std::string(szDir);
        strRetFile += std::string(_T("result.txt"));

		FILE* fp=fopen(strRetFile.c_str(),"w");
		std::string strInfo = stInfo.m_strPath;
		fputs(strInfo.c_str(),fp);
		fputs("\n",fp);
		strInfo = std::string(_T("文件夹数：")) + boost::str(boost::format("%d\n")%stInfo.m_FolderNum);
		fputs(strInfo.c_str(),fp);
		strInfo = std::string(_T("文件数：")) + boost::str(boost::format("%d\n")%stInfo.m_FileNum);
		fputs(strInfo.c_str(),fp);
		fclose(fp);
		std::cout<<"已经将统计结果写入到文件"<<strRetFile<<std::endl;
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

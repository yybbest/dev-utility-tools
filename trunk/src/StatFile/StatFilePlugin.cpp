#include "StdAfx.h"
#include "StatFilePlugin.h"

#include <iostream>
#include <tchar.h>

CStatFilePlugin::CStatFilePlugin(const std::string& strID ):IPluginObj(strID)
{

}

CStatFilePlugin::~CStatFilePlugin(void)
{
}

void CStatFilePlugin::StatAllFileInFolder(const std::string strDirPath)
{
	WIN32_FIND_DATA ffd;
	std::string strTmpDir = strDirPath;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	DWORD dwError=0;
	std::string strNewFileName;
	std::string strOldFileName;

	strTmpDir = strTmpDir + TEXT("*");
	hFind = FindFirstFile(strTmpDir.c_str(), &ffd);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		return;
	}
	::SetCursor(LoadCursor(NULL,IDC_WAIT));
	do
	{
		// if the file isnot folder,file number increase 1
		if ((ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)==0)
		{
            m_info.m_FileNum++;
		}
		else
		{
			// if the file is folder,build the sub folder name and continue call this function           
            std::string strSubFolder = strDirPath + ffd.cFileName; 
			strSubFolder = strSubFolder + _T("\\");
			if(strSubFolder.rfind('.')==std::string::npos)
			{
			   m_info.m_FolderNum++;
			   StatAllFileInFolder(strSubFolder);
			}
		}
	}
	while (FindNextFile(hFind, &ffd) != 0);
	::SetCursor(LoadCursor(NULL,IDC_ARROW));
	FindClose(hFind);
}

BOOL CStatFilePlugin::ProcessData( boost::any& anyData )
{
	if(anyData.type() == typeid(std::string))  
	{
		std::string strPath  = boost::any_cast<std::string>(anyData); 
		if(::GetFileAttributes(strPath.c_str())==-1)
		{
			std::cout<<"目录不存在"<<std::endl;
			return FALSE;
		}
        m_info.m_strPath = strPath;
		std::cout<<"现在正在统计的是："<<m_info.m_strPath<<std::endl;
        std::cout<<"请等待！！！"<<std::endl;
        
		std::string	strTmpDir = m_info.m_strPath + TEXT("\\");
		StatAllFileInFolder(strTmpDir);

        std::cout<<"文件夹数："<<m_info.m_FolderNum<<std::endl;
		std::cout<<"文件数："<<m_info.m_FileNum<<std::endl;

		CPluginFactory* pPluginFactory = CPluginFactory::Instance();
		IPluginObjPtr ptrOuttoFile = pPluginFactory->GetPlugin(_T("OutputFile.dll"));
		boost::any anyInfo = m_info;
		ptrOuttoFile->ProcessData(anyInfo);

		return TRUE;
	}
	return FALSE;
}


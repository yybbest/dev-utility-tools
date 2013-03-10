// CmdApp.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <assert.h>
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
    // ��ȡbin·��
	TCHAR szAppName[MAX_PATH];
	:: GetModuleFileName(NULL,szAppName, MAX_PATH);
	TCHAR szDrive[_MAX_DRIVE];
	TCHAR szDir[_MAX_DIR];
	TCHAR szBinName[_MAX_FNAME];
	TCHAR szExt[_MAX_EXT];
	_tsplitpath(szAppName,szDrive,szDir,szBinName,szExt); 

	std::string strBinPath = std::string(szDrive) + std::string(szDir);
	CPluginFactory* pPluginFactory = CPluginFactory::Instance();
	assert(NULL!=pPluginFactory);
    pPluginFactory->SetBinPath(strBinPath);
    if(!pPluginFactory->AddPluginLib(_T("StatFile.dll")))
		std::cout<<"���StatFile.dllʧ��"<<std::endl;

    if(!pPluginFactory->AddPluginLib(_T("OutputFile.dll")))
        std::cout<<"���OutputFile.dllʧ��"<<std::endl;
  
	IPluginObjPtr ptrStatFile = pPluginFactory->GetPlugin(_T("StatFile.dll"));
	std::string strFolder = _T("D:\\dev-utility-tools\\doc");
	boost::any anyString = strFolder;
	ptrStatFile->ProcessData(anyString);

	getchar();
	return 0;
}


#pragma once

#include <vector>
#include "IPluginObj.h"

// ��ȡ����ĺ�
#define   GET_LAST_ERROR(hModule,strModuleName);   	\
	if (NULL==hModule) \
	{   \
	std::string strName = strModuleName; \
	LPVOID lpMsgBuf; \
	FormatMessage( \
	FORMAT_MESSAGE_ALLOCATE_BUFFER |  \
	FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,  \
	NULL,  \
	GetLastError(),  \
	MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), \
	(LPTSTR)&lpMsgBuf,   \
	0,   \
	NULL \
	);   \
	::MessageBox( NULL, (LPCTSTR)lpMsgBuf,strName.c_str(), MB_OK | MB_ICONINFORMATION );\
	LocalFree( lpMsgBuf);\
	}\

struct stPluginInfo
{
	std::string m_strLibrary;  // ����Դ��̬���ļ�
	HMODULE m_hModule;    //  ģ����

	stPluginInfo(const std::string& strLibrary)
	{
		m_strLibrary  = strLibrary;
		m_hModule = NULL;
	}
};

class BASEOBJLIB_API CPluginFactory
{

public:

	CPluginFactory(void);

	virtual ~CPluginFactory(void);

	// ��������		:	Instance
	// ����			:	����ȫ��Ψһ�㷨�������ʵ��
	// ��������		:	CAlgoFactory*
	static CPluginFactory* Instance();

	void SetBinPath(const std::string& strBinPath)
	{
        m_BinPath = strBinPath;
	}

	BOOL AddPluginLib( const std::string& strLibName );

	// strLibName����׺dll�������㷨����
	IPluginObjPtr GetPlugin(const std::string& strLibName);

protected:

	std::vector<stPluginInfo> m_vecPluginInfo; // �㷨��Ϣ
    std::string m_BinPath;
};

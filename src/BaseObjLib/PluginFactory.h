#pragma once

#include <vector>
#include "IPluginObj.h"

// 获取错误的宏
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
	std::string m_strLibrary;  // 数据源动态库文件
	HMODULE m_hModule;    //  模块句柄

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

	// 函数名称		:	Instance
	// 描述			:	返回全局唯一算法管理对象实例
	// 返回类型		:	CAlgoFactory*
	static CPluginFactory* Instance();

	void SetBinPath(const std::string& strBinPath)
	{
        m_BinPath = strBinPath;
	}

	BOOL AddPluginLib( const std::string& strLibName );

	// strLibName带后缀dll，创建算法对象
	IPluginObjPtr GetPlugin(const std::string& strLibName);

protected:

	std::vector<stPluginInfo> m_vecPluginInfo; // 算法信息
    std::string m_BinPath;
};

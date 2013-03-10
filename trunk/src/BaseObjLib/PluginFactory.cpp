#include "StdAfx.h"
#include "PluginFactory.h"

typedef IPluginObj* (__stdcall *GetPluginObj)(const std::string &strID);

CPluginFactory::CPluginFactory(void)
{
}

CPluginFactory::~CPluginFactory(void)
{
}

BOOL CPluginFactory::AddPluginLib( const std::string& strLibName )
{
    // 判断动态库是否存在
	std::string FullPath = m_BinPath+strLibName;
	if(::GetFileAttributes(FullPath.c_str())==-1)
		return FALSE;

	stPluginInfo info(strLibName);
	m_vecPluginInfo.push_back(info);
	return TRUE;
}

IPluginObjPtr CPluginFactory::GetPlugin( const std::string& strLibName )
{
	if(m_vecPluginInfo.empty())
		return NULL;
	for (size_t i = 0;i<m_vecPluginInfo.size();i++)
	{
		if(m_vecPluginInfo[i].m_strLibrary==strLibName)
		{
			if(NULL!=m_vecPluginInfo[i].m_hModule)
			{
				// 找到函数地址创建
				GetPluginObj get_plugin;
				get_plugin = (GetPluginObj)::GetProcAddress(m_vecPluginInfo[i].m_hModule,("GetPluginObj"));
				IPluginObj* pSysAlgo = get_plugin(m_vecPluginInfo[i].m_strLibrary);

				if(pSysAlgo == NULL)
				{
					::FreeLibrary(m_vecPluginInfo[i].m_hModule);
					m_vecPluginInfo[i].m_hModule = NULL;
					return NULL;
				}
				else
				{
					return pSysAlgo;
				}
			}
			else
			{
				// 加载库，找到函数地址创建
				std::string dll_path = m_BinPath + strLibName;
				try
				{
					m_vecPluginInfo[i].m_hModule = ::LoadLibrary(dll_path.c_str());
					GET_LAST_ERROR(m_vecPluginInfo[i].m_hModule,dll_path);
					if(m_vecPluginInfo[i].m_hModule == NULL)
					{
						return NULL;
					}
					else
					{
						GetPluginObj get_plugin;
						get_plugin = (GetPluginObj)::GetProcAddress(m_vecPluginInfo[i].m_hModule,("GetPluginObj"));
						GET_LAST_ERROR(get_plugin,dll_path);
						if (NULL==get_plugin)
						{
							return NULL;
						}
						IPluginObj* pSysAlgo = get_plugin(m_vecPluginInfo[i].m_strLibrary);

						if(pSysAlgo == NULL)
						{
							::FreeLibrary(m_vecPluginInfo[i].m_hModule);
							m_vecPluginInfo[i].m_hModule = NULL;
							return NULL;
						}
						else
						{
							return pSysAlgo;
						}
					}
				}
				catch(std::exception& ex)
				{
					::MessageBox(NULL,ex.what(),_T("错误"), MB_OK|MB_ICONSTOP);
					return FALSE;
				}
			}
		}
	}
	return NULL;
}

CPluginFactory* CPluginFactory::Instance()
{
	static CPluginFactory PluginFactory;
	return &PluginFactory;
}

#pragma once

#include "..\DataExchange\stat_info.h"

class CStatFilePlugin : public IPluginObj
{
public:

	CStatFilePlugin(const std::string& strID);

	~CStatFilePlugin(void);

	BOOL ProcessData(boost::any& anyData);

protected:

	void StatAllFileInFolder(const std::string strDirPath);

protected:

	stStatInfo m_info;

};

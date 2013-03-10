#pragma once

class COutputFilePlugin : public IPluginObj
{
public:

	COutputFilePlugin(const std::string& strID);

	~COutputFilePlugin(void);

	BOOL ProcessData(boost::any& anyData);

};

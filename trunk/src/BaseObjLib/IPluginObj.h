#pragma once

#include <boost/any.hpp>

#include "IBaseObj.h" 

class BASEOBJLIB_API IPluginObj : public IBaseObj
{
public:

	IPluginObj(const std::string& strID);

	virtual ~IPluginObj(void);

	virtual BOOL ProcessData(boost::any& anyData){ return FALSE;}

protected:

	std::string m_strID;			/**插件的标示符，即动态库名*/
};

typedef _ptr_t<IPluginObj> IPluginObjPtr;		/**扩展接口类的智能指针对象*/
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

	std::string m_strID;			/**����ı�ʾ��������̬����*/
};

typedef _ptr_t<IPluginObj> IPluginObjPtr;		/**��չ�ӿ��������ָ�����*/
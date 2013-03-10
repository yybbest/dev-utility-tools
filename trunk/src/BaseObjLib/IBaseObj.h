#pragma once

#include <string>
#include <map>

#include "Ref.h"

class BASEOBJLIB_API IBaseObj : public CRef 
{
public:
	
	IBaseObj(const std::string& strAssName);

	virtual ~IBaseObj(void);

	/**
	* 获得名称
	*/
	const std::string& GetName();

   	/**
	* 设置名称
	*/

	/*该函数不支持多线程*/
	/**
	* 通过名称获得用户界面对象
	* @param Name 控件名称
	* @return 若存在则返回该对象指针，否则返回为NULL
	*/
	static _ptr_t<IBaseObj> GetUIObjectByName(const std::string& Name);

	/**
	* 获得第一个用户界面对象
	* @return 若存在则返回该对象指针，否则返回为NULL
	*/
	static _ptr_t<IBaseObj> GetFirstObject();

	/**
	* 获得第一个用户界面对象
	* @return 若存在则返回该对象指针，否则返回为NULL
	*/
	static _ptr_t<IBaseObj> GetNextObject();

	/**
	* 清除一个界面对象
	*/
	static void RemoveObject(const std::string& name);

	/**
	* 清除所有用户界面对象
	*/
	static void ClearObjects();

protected:

	virtual BOOL CreateAss(const std::string& Name);/**< 创建关联对象*/

	virtual BOOL DestroyAss();/**< 删除关联对象*/

	std::string m_Name;  // 用户界面对象名
};

typedef _ptr_t<IBaseObj> IBaseObjPtr;/**< 用户界面底层智能指针对象*/

static std::map<std::string,IBaseObjPtr> mapObjs; // 界面

static std::map<std::string,IBaseObjPtr>::iterator find_item;
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
	* �������
	*/
	const std::string& GetName();

   	/**
	* ��������
	*/

	/*�ú�����֧�ֶ��߳�*/
	/**
	* ͨ�����ƻ���û��������
	* @param Name �ؼ�����
	* @return �������򷵻ظö���ָ�룬���򷵻�ΪNULL
	*/
	static _ptr_t<IBaseObj> GetUIObjectByName(const std::string& Name);

	/**
	* ��õ�һ���û��������
	* @return �������򷵻ظö���ָ�룬���򷵻�ΪNULL
	*/
	static _ptr_t<IBaseObj> GetFirstObject();

	/**
	* ��õ�һ���û��������
	* @return �������򷵻ظö���ָ�룬���򷵻�ΪNULL
	*/
	static _ptr_t<IBaseObj> GetNextObject();

	/**
	* ���һ���������
	*/
	static void RemoveObject(const std::string& name);

	/**
	* ��������û��������
	*/
	static void ClearObjects();

protected:

	virtual BOOL CreateAss(const std::string& Name);/**< ������������*/

	virtual BOOL DestroyAss();/**< ɾ����������*/

	std::string m_Name;  // �û����������
};

typedef _ptr_t<IBaseObj> IBaseObjPtr;/**< �û�����ײ�����ָ�����*/

static std::map<std::string,IBaseObjPtr> mapObjs; // ����

static std::map<std::string,IBaseObjPtr>::iterator find_item;
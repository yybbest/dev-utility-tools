#include "StdAfx.h"
#include "IBaseObj.h"

IBaseObj::IBaseObj(const std::string& strAssName)
{
	// ������������ 
	CreateAss(strAssName);
}

IBaseObj::~IBaseObj(void)
{
	DestroyAss();
}

const std::string& IBaseObj::GetName()
{
    return m_Name;
}

_ptr_t<IBaseObj> IBaseObj::GetUIObjectByName( const std::string& Name )
{
	std::map<std::string,IBaseObjPtr>::iterator item;
	item = mapObjs.find( Name );
	if( item == mapObjs.end() )
		return NULL;
	else
		return item->second;
}

_ptr_t<IBaseObj> IBaseObj::GetFirstObject()
{
	find_item = mapObjs.begin();
	if( find_item == mapObjs.end())
		return NULL;
	else
		return find_item->second;
}

_ptr_t<IBaseObj> IBaseObj::GetNextObject()
{
	find_item++;
	if( find_item == mapObjs.end() )
		return NULL;
	else
		return find_item->second;
}

void IBaseObj::RemoveObject( const std::string& name )
{
	std::map<std::string,IBaseObjPtr>::iterator item;
	if(name.length() == 0 )
		return;
	item = mapObjs.find(name);
	if( item != mapObjs.end() )
	{
		item->second.Detach();// ����ټ�һ�����û�����ֱ�ӳ�ȥ����
		mapObjs.erase( item );
	}
}

void IBaseObj::ClearObjects()
{
	std::map<std::string,IBaseObjPtr>::iterator item;
	for ( item = mapObjs.begin() ; item != mapObjs.end() ; item++ )
	{
		item->second.Detach();// ����ټ�һ�����û�����ֱ�ӳ�ȥ����
	}
	mapObjs.clear();
}

BOOL IBaseObj::CreateAss( const std::string& Name )
{
	std::map<std::string,IBaseObjPtr>::iterator item;
	IBaseObjPtr pobject;
	pobject.Attach( this ); // �ټ�һ�����û���

	item = mapObjs.find( Name );
	if( item == mapObjs.end() )
		mapObjs.insert( std::map<std::string,IBaseObjPtr>::value_type(Name, pobject ));
	else
	{
		mapObjs[ Name ].Detach();
		mapObjs[ Name ] = this;
		return FALSE;
	}
	m_Name = Name;
	return TRUE;
}

BOOL IBaseObj::DestroyAss()
{
	std::map<std::string,IBaseObjPtr>::iterator item;
	if( m_Name.length() == 0 )
		return FALSE;

	item = mapObjs.find( m_Name );
	if( item != mapObjs.end() )
	{
		item->second.Detach();// ����ټ�һ�����û�����ֱ�ӳ�ȥ����
		mapObjs.erase(item);
		return TRUE;
	}
	else
		return FALSE;
}

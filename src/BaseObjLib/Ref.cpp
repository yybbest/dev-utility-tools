#include "StdAfx.h"
#include "Ref.h"

CRef::CRef(void)
{
}

CRef::~CRef(void)
{
}

unsigned long CRef::AddRef()
{
	// 给指针记录独占地自增
	InterlockedIncrement(reinterpret_cast<long*>(&m_Ref));
	return m_Ref;	
}

unsigned long CRef::Release()
{
	// 给指针记录独占地自减
	if (!InterlockedDecrement(reinterpret_cast<long*>(&m_Ref))) {
		delete this;
		return 0;
	}
	return m_Ref;
}

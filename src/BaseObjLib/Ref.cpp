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
	// ��ָ���¼��ռ������
	InterlockedIncrement(reinterpret_cast<long*>(&m_Ref));
	return m_Ref;	
}

unsigned long CRef::Release()
{
	// ��ָ���¼��ռ���Լ�
	if (!InterlockedDecrement(reinterpret_cast<long*>(&m_Ref))) {
		delete this;
		return 0;
	}
	return m_Ref;
}

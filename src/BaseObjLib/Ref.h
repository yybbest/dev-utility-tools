#pragma once

class BASEOBJLIB_API CRef
{
public:
	CRef(void);
	virtual ~CRef(void);

	unsigned long AddRef();

	unsigned long Release();

private:

	unsigned long m_Ref;

};


/*! \class _ptr_t 
*  \brief 
*
*	����ָ��ģ����
*  \author ����.
*  \version 0.1
*  \date    2010.03.28.
*/
template<typename T>
class _ptr_t
{
public:

	typedef T _PtrClass; 

	_ptr_t()
	{
		p=NULL;
	}
	_ptr_t(T* lp)
	{
		if ((p = lp) != NULL)
			p->AddRef();
	}

	template<typename _OtherT>
	_ptr_t(_OtherT* lp)
	{
		T *p1 = dynamic_cast<T*>(lp);

		if ((p = p1) != NULL)
			p->AddRef();
	}
	_ptr_t(const _ptr_t<T>& lp)
	{
		if ((p = lp.p) != NULL)
			p->AddRef();
	}
	template<typename _OtherT>
	_ptr_t(const _ptr_t<_OtherT>& lp)
	{
		T *p1 = dynamic_cast<T*>(lp.p);
		if ((p = p1) != NULL)
			p->AddRef();
	}
	_ptr_t(T *t, bool addRef)
	{
		p=NULL;
		if(  t != NULL )
		{
			Attach( t );
			if( addRef ) 
				p->AddRef();
		}
	}


	~_ptr_t()
	{
		if (p)
			p->Release();
	}
	// ???
	void Release()
	{
		T* pTemp = p;
		if (pTemp)
		{
			p = NULL; 
			pTemp->Release();
		}
	}
	// ָ��ת��
	operator T*() const
	{
		return (T*)p;
	}
	T& operator*() const
	{
		return *p;
	}

	T* operator->() const
	{
		return p;
	}
	T* operator=(T* lp)
	{
		Release();

		if( lp != NULL )
		{
			p = lp;
			p->AddRef();
			return p;
		}
		else 
			return NULL;
	}
	T* operator=(const _ptr_t<T>& lp)
	{
		Release();
		if( lp.p != NULL )
		{
			p = lp;
			p->AddRef();
			return p;
		}
		else 
			return NULL;
	}
	template<typename _OtherT>
	T* operator=(const _ptr_t<_OtherT>& lp)
	{
		Release();
		if( lp.p != NULL )
		{
			p = dynamic_cast<T*>(lp.p);
			if( p != NULL )
				p->AddRef();
			return p;
		}
		else 
			return NULL;
	}
	template<typename _OtherT>
	T* operator=(const _OtherT* lp)
	{
		Release();
		if( lp != NULL )
		{
			p = dynamic_cast<T*>(lp);
			if( p != NULL )
				p->AddRef();
			return p;
		}
		else 
			return NULL;
	}
	template<typename _OtherT>
	bool operator==(const _ptr_t<_OtherT>& lp)
	{
		T *p1 = dynamic_cast<T*>(lp.p);
		if( p != p1 )
			return FALSE;
		else 
			return TRUE;
	}
	// �ж�ָ���Ƿ����
	bool operator==(T* pT) const
	{
		return p == pT;
	}
	// �ж�ָ���Ƿ�Ϊ��
	bool IsEmpty() const
	{
		return p == NULL;
	}
	bool operator!=(T* pT) const
	{
		return p != pT;
	}
	// ��������Ĳ����������
	bool operator!=(int lNULL) const
	{
		return p != NULL;
	}
	//�ͷ�ӵ�е��ڴ棬ָ���µĶ���
	void Attach(T* p2)
	{
		if (p)
			p->Release();
		p = p2;
	}
	// ����ԭ����ָ�Ķ���
	T* Detach()
	{
		T* pt = p;
		p = NULL;
		return pt;
	}
	T* p;
};


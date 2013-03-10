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
*	智能指针模板类
*  \author 朱金灿.
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
	// 指针转换
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
	// 判断指针是否相等
	bool operator==(T* pT) const
	{
		return p == pT;
	}
	// 判断指针是否为空
	bool IsEmpty() const
	{
		return p == NULL;
	}
	bool operator!=(T* pT) const
	{
		return p != pT;
	}
	// 这个函数的参数意义何在
	bool operator!=(int lNULL) const
	{
		return p != NULL;
	}
	//释放拥有的内存，指向新的对象
	void Attach(T* p2)
	{
		if (p)
			p->Release();
		p = p2;
	}
	// 返回原来所指的对象
	T* Detach()
	{
		T* pt = p;
		p = NULL;
		return pt;
	}
	T* p;
};


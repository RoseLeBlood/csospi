#ifndef _STD_AUTO_PTR_H
#define _STD_AUTO_PTR_H

namespace std
{
	class __ptr_base 
	{
	public:
		void* _M_p;
		void  __set(const volatile void* p) 
		{ 
			_M_p = __CONST_CAST(void*,p); 
		}
		void  __set(void* p) 
		{ 
			_M_p = p; 
	  	}
	};

	template <class _Tp> class auto_ptr_ref 
	{
	public:
		__ptr_base& _M_r;
		_Tp* const _M_p;

	auto_ptr_ref(__ptr_base& __r, _Tp* __p) 
		: _M_r(__r), _M_p(__p) 
	{  
	}

	_Tp* release() const 
	{ 
		_M_r.__set(__STATIC_CAST(void*, 0)); 
		return _M_p;
	}

	private:
		typedef auto_ptr_ref<_Tp> _Self;
		_Self& operator = (_Self const&);
	};

	template<class _Tp>	class auto_ptr :  public __ptr_base 
	{
	public:
		typedef _Tp element_type;
		typedef auto_ptr<_Tp> _Self;

		explicit auto_ptr(_Tp* __px = 0) 
		{ 
			this->__set(__px); 
		}
		template<class _Tp1> auto_ptr(auto_ptr<_Tp1>& __r)  
		{
			_Tp* __conversionCheck = __r.release();
			this->__set(__conversionCheck);
		}
		auto_ptr(_Self& __r)  
		{ 
			this->__set(__r.release()); 
		}
		auto_ptr(auto_ptr_ref<_Tp> __r) 
		{
		 	this->__set(__r.release()); 
		}
		~auto_ptr()  
		{ 
			delete this->get(); 
		}
		_Tp* release()  
		{
			_Tp* __px = this->get();
			this->_M_p = 0;
			return __px;
		}
		void reset(_Tp* __px = 0)  
		{
			_Tp* __pt = this->get();
			if (__px != __pt)
				delete __pt;
			this->__set(__px);
		}

		_Tp* get() const 
		{ 
			return __STATIC_CAST(_Tp*, _M_p); 
		}

		_Tp* operator->() const  
		{
			assert(get() != 0)
			return get();
		}
		_Tp& operator*() const  
		{
			assert(get() != 0)
			return *get();
		}
		_Self& operator=(auto_ptr_ref<_Tp> __r)  
		{
			reset(__r.release());
			return *this;
		}
		_Self& operator=(_Self& __r)  
		{
			reset(__r.release());
			return *this;
		}
		template<class _Tp1> operator auto_ptr_ref<_Tp1>() 
		{ 
			return auto_ptr_ref<_Tp1>(*this, this->get()); 
		}
		template<class _Tp1> operator auto_ptr<_Tp1>() 
		{ 
			return auto_ptr<_Tp1>(release()); 
		}	
	};
}

#endif 
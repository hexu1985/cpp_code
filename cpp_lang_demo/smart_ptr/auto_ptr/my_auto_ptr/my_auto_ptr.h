#ifndef	MY_AUTO_PTR_H
#define	MY_AUTO_PTR_H

//auxiliary type to enable copies and assignments
template <class T>
struct Auto_ptr_ref {
	T *m_ptr;
	explicit Auto_ptr_ref(T *ptr): m_ptr(ptr) {}
};

template<class T>
class Auto_ptr {
private:
	T *m_ptr;

public:
	//type names for the value
	typedef T element_type;

	//constructor
	explicit Auto_ptr(T *ptr = 0) throw(): m_ptr(ptr) {}

	//copy constructors (with implicit conversion)
	//- note: nonconstant parameter
	Auto_ptr(Auto_ptr& a) throw(): m_ptr(a.release()) {}

	template<class U> Auto_ptr(Auto_ptr<U>& a) throw(): m_ptr(a.release()) {}

	//assignments (with implicit conversion)
	//- note: nonconstant parameter
	Auto_ptr& operator= (Auto_ptr &a) throw()
	{
		reset(a.release());
		return *this;
	}

	template<class U>
	Auto_ptr& operator= (Auto_ptr<U> &a) throw()
	{
		reset(a.release());
		return *this;
	}

	//destructor
	~Auto_ptr() throw()
	{
		delete m_ptr;
	}

	//value access
	T *get() const throw()
	{
		return m_ptr;
	}

	T &operator *() const throw()
	{
		return *m_ptr;
	}

	T *operator ->() const throw()
	{
		return m_ptr;
	}

	//release ownership
	T *release() throw()
	{
		element_type *tmp = m_ptr;
		m_ptr = 0;
		return tmp;
	}

	//reset value
	void reset(T *ptr = 0) throw()
	{
		if (ptr != m_ptr) {
			delete m_ptr;
			m_ptr = ptr;
		}
	}

	//special conversions to enable copies and assignments
public:
	Auto_ptr(Auto_ptr_ref<T> r) throw(): m_ptr(r.m_ptr) {}

	Auto_ptr &operator =(Auto_ptr_ref<T> r) throw()
	{
		if (r.m_ptr != this->get()) {
			delete m_ptr;
			m_ptr = r.m_ptr;
		}
		return *this;
	}

	template<class U> operator Auto_ptr_ref<U>() throw()
	{
		return Auto_ptr_ref<U>(this->release());
	}

	template<class U> operator Auto_ptr<U>() throw()
	{
		return Auto_ptr<U>(this->release());
	}
};

#endif

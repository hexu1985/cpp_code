#ifndef	MY_AUTO_PTR_ARRAY_H
#define	MY_AUTO_PTR_ARRAY_H

template <typename T>
struct Default_delete<T[]> {
	void operator ()(T *p) const
	{
		delete [] p;
	}
};

template<typename T, typename D>
class Auto_ptr<T[], D> {
private:
	T *m_ptr;
	D m_del;

public:
	//type names for the value
	typedef T element_type;

	//type names for the deleter
	typedef D deleter_type;

	//constructor
	explicit Auto_ptr(T *ptr = 0, D del = D()) throw(): m_ptr(ptr), m_del(del) 
	{}

	//destructor
	~Auto_ptr() throw()
	{
		if (m_ptr != 0) {
			this->get_deleter()(m_ptr);
		}
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

	//get a reference to the stored deleter.
	deleter_type &get_deleter() throw()
	{
		return m_del;
	}

	//reset value
	void reset(T *ptr = 0) throw()
	{
		if (ptr != m_ptr) {
			m_del(m_ptr);
			m_ptr = ptr;
		}
	}

	//exchange the pointer and deleter with another object.
	void swap(Auto_ptr &a) throw()
	{
		using std::swap;
		swap(m_ptr, a.m_ptr);
		swap(m_del, a.m_del);
	}

	//explicit operator bool() const nexcept
private:
	struct boolean { int i; };
public:
	operator int boolean::*() const throw()
	{
		return m_ptr? &boolean::i : 0;
	}

	//access an element of owned array.
	T &operator [](int i) const throw()
	{
		return m_ptr[i];
	}

private:
	//delete copy and assign op
	Auto_ptr(Auto_ptr&);
	Auto_ptr& operator= (Auto_ptr &);
};

#endif

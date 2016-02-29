
namespace std {

//auxiliary type to enable copies and assignments
template <class Y> struct Auto_ptr_ref {};

template<class T>
class Auto_ptr {
public:
	//type names for the value
	typedef T element_type;

	//constructor
	explicit Auto_ptr(T* ptr = 0) throw();

	//copy constructors (with implicit conversion)
	//- note: nonconstant parameter
	Auto_ptr(Auto_ptr&) throw();
	template<class U> Auto_ptr(Auto_ptr<U>&) throw();

	//assignments (with implicit conversion)
	//- note: nonconstant parameter
	Auto_ptr& operator= (Auto_ptr&) throw();
	template<class U>
		Auto_ptr& operator= (Auto_ptr<U>&) throw();

	//destructor
	~Auto_ptr() throw();

	//value access
	T* get() const throw();
	T& operator*() const throw();
	T* operator->() const throw();

	//release ownership
	T* release() throw();

	//reset value
	void reset(T* ptr = 0) throw();

	//special conversions to enable copies and assignments
public:
	Auto_ptr(Auto_ptr_ref<T>) throw();
	Auto_ptr& operator= (Auto_ptr_ref<T> rhs) throw();
	template<class U> operator Auto_ptr_ref<U>() throw();
	template<class U> operator Auto_ptr<U>() throw();
};

}


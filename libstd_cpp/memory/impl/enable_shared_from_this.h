// -*- C++ -*-
// HeXu's
// 2014 May

#ifndef HX_ENABLE_SHARED_FROM_THIS_H
#define HX_ENABLE_SHARED_FROM_THIS_H

namespace Hx {

template <typename T>
class enable_shared_from_this {
protected:
	enable_shared_from_this() noexcept {}

	enable_shared_from_this(const enable_shared_from_this &) noexcept {}

	enable_shared_from_this &operator =(const enable_shared_from_this &) noexcept
	{
		return *this;
	}

	~enable_shared_from_this() noexcept {}

public:
	shared_ptr<T> shared_from_this()
	{
		shared_ptr<T> p(weak_this_);
		assert(p.get() == this);
		return p;
	}

	shared_ptr<const T> shared_from_this() const
	{
		shared_ptr<const T> p(weak_this_);
		assert(p.get() == this);
		return p;
	}

private:
	template <typename T2, typename U, typename V>
	friend inline void detail::sp_enable_shared_from_this(
		const Hx::shared_ptr<T2> *sp, const U *p, 
		const Hx::enable_shared_from_this<V> *pe);

	template <typename U, typename V>
	void internal_accept_owner(const shared_ptr<U> *sp, V *p) const
	{
		if (weak_this_.expired()) {
			weak_this_ = shared_ptr<T>(*sp, p);
		}
	}

	mutable weak_ptr<T> weak_this_;
};

}	// namespace Hx

#endif	// HX_ENABLE_SHARED_FROM_THIS_H

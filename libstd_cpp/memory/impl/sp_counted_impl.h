// -*- C++ -*-
// HeXu's
// 2014 May

#ifndef HX_SP_COUNTED_IMPL_H
#define HX_SP_COUNTED_IMPL_H

namespace Hx {

namespace detail {

template <typename T>
class sp_counted_impl_p: public sp_counted_base {
private:
	T *p_;	// pointer

#if __cplusplus >= 201103L
	sp_counted_impl_p(const sp_counted_impl_p &) = delete;
	sp_counted_impl_p &operator =(const sp_counted_impl_p &) = delete;
#else
	sp_counted_impl_p(const sp_counted_impl_p &);
	sp_counted_impl_p &operator =(const sp_counted_impl_p &);
#endif

public:
	explicit sp_counted_impl_p(T *p): p_(p) {}

	virtual void dispose() noexcept { delete p_; }

	virtual void *get_deleter() { return NULL; }
};

template <typename P, typename D>
class sp_counted_impl_pd: public sp_counted_base {
private:
	P p_;	// copy constructor must not throw
	D del_;	// copy constructor must not throw

#if __cplusplus >= 201103L
	sp_counted_impl_pd(const sp_counted_impl_pd &) = delete;
	sp_counted_impl_pd &operator =(const sp_counted_impl_pd &) = delete;
#else
	sp_counted_impl_pd(const sp_counted_impl_pd &);
	sp_counted_impl_pd &operator =(const sp_counted_impl_pd &);
#endif

public:
	sp_counted_impl_pd(P p, D &d): p_(p), del_(d) {}

	sp_counted_impl_pd(P p): p_(p), del_() {}

	virtual void dispose() noexcept { del_(p_); }
	
	virtual void *get_deleter() { return &reinterpret_cast<char &>(del_); }
};

template <typename P, typename D, typename A>
class sp_counted_impl_pda: public sp_counted_base {
private:
	P p_;	// copy constructor must not throw
	D del_;	// copy constructor must not throw
	A alloc_;	// copy constructor must not throw

#if __cplusplus >= 201103L
	sp_counted_impl_pda(const sp_counted_impl_pda &) = delete;
	sp_counted_impl_pda &operator =(const sp_counted_impl_pda &) = delete;
#else
	sp_counted_impl_pda(const sp_counted_impl_pda &);
	sp_counted_impl_pda &operator =(const sp_counted_impl_pda &);
#endif

	typedef sp_counted_impl_pda<P, D, A> this_type;

public:
	sp_counted_impl_pda(P p, D &d, A a): p_(p), del_(d), alloc_(a) {}

	sp_counted_impl_pda(P p, A a): p_(p), del_(), alloc_(a) {}

	virtual void dispose() noexcept { del_(p_); }

	virtual void destroy() noexcept
	{
		typedef typename A::template rebind<this_type>::other alloc_type;
		alloc_type alloc(alloc_);
		this->~this_type();
		alloc.deallocate(this, 1);
	}
	
	virtual void *get_deleter() { return &reinterpret_cast<char &>(del_); }
};

}	// namespace detail

}	// namespace Hx

#endif

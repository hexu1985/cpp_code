// -*- C++ -*-
// HeXu's
// 2014 May

#ifndef HX_SHARED_COUNT_H
#define HX_SHARED_COUNT_H

#include "sp_counted_base.h"
#include "sp_counted_impl.h"
#include "bad_weak_ptr.h"

namespace Hx {

namespace detail {

class weak_count;

class shared_count {
private:
	sp_counted_base *pi_;

	friend class weak_count;

public:
	shared_count(): pi_(NULL) {}

	template <typename T>
	explicit shared_count(T *p): pi_(NULL)
	{
		try 
		{
			pi_ = new sp_counted_impl_p<T>(p);
		}
		catch (...) 
		{
			delete p;
			throw;
		}
	}

	template <typename P, typename D>
	shared_count(P p, D d): pi_(NULL)
	{
		try 
		{
			pi_ = new sp_counted_impl_pd<P, D>(p, d);
		}
		catch (...)
		{
			d(p);	// delete p
			throw;
		}
	}

	template <typename P, typename D, typename A>
	shared_count(P p, D d, A a): pi_(NULL)
	{
		typedef sp_counted_impl_pda<P, D, A> impl_type;
		typedef typename A::template rebind<impl_type>::other alloc_type;

		alloc_type alloc(a);

		try
		{
#if __cplusplus >= 201103L
			pi_ = std::allocator_traits<alloc_type>::allocate(alloc, 1,
				static_cast<impl_type *>(NULL));
#else
			pi_ = alloc.allocate(1, static_cast<impl_type *>(NULL));
#endif
			::new (static_cast<void *>(pi_)) impl_type(p, d, a);
		}
		catch (...)
		{
			d(p);
			if (pi_ != NULL) {
#if __cplusplus >= 201103L
				std::allocator_traits<alloc_type>::deallocate(alloc, 
					static_cast<impl_type *>(pi_), 1);
#else
				alloc.deallocate(static_cast<impl_type *>(pi_), 1);
#endif
			}
			throw;
		}
	}

	template <typename U>
	explicit shared_count(std::auto_ptr<U> &r): 
		pi_(new sp_counted_impl_p<U>(r.get()))
	{
		r.release();
	}

#if __cplusplus >= 201103L
	template <typename U, typename D>
	explicit shared_count(std::unique_ptr<U, D> &&r): pi_(NULL)
	{
		typedef typename std::unique_type<U, D>::deleter_type deleter_type;
		deleter_type &d = r.get_deleter();

		typedef typename std::unique_type<U, D>::pointer_type pointer_type;
		typedef sp_counted_impl_pd<pointer_type, deleter_type> impl_type;
		pi_ = new impl_type(r.get(), d);

		r.release();
	}
#endif

	~shared_count() noexcept
	{
		if (pi_ != NULL) pi_->release();
	}

	shared_count(const shared_count &r) noexcept: pi_(r.pi_)
	{
		if (pi_ != NULL) pi_->add_ref_copy();
	}

#if __cplusplus >= 201103L
	shared_count(shared_count &&r) noexcept: pi_(r.pi_)
	{
		r.pi_ = 0; 
	}
#endif

	// throws bad_weak_ptr when r.use_count() == 0
	shared_count(const weak_count &r);

	shared_count &operator =(const shared_count &r) noexcept
	{
		sp_counted_base *tmp = r.pi_;

		if (tmp != pi_) {
			if (tmp != NULL) tmp->add_ref_copy();
			if (pi_ != NULL) pi_->release();
			pi_ = tmp;
		}

		return *this;
	}

	void swap(shared_count &r) noexcept
	{
		std::swap(pi_, r.pi_);
	}

	long use_count() const noexcept
	{
		return pi_ != NULL ? pi_->use_count() : 0;
	}

	bool unique() const noexcept
	{
		return use_count() == 1;
	}

	bool empty() const noexcept
	{
		return pi_ == NULL;
	}

	friend inline bool operator ==(const shared_count &a, const shared_count &b)
	{
		return a.pi_ == b.pi_;
	}

	friend inline bool operator <(const shared_count &a, const shared_count &b)
	{
		return std::less<sp_counted_base *>()(a.pi_, b.pi_);
	}

	void *get_deleter() const
	{
		return pi_ != NULL ? pi_->get_deleter() : 0;
	}
};

class weak_count {
private:
	sp_counted_base *pi_;

	friend class shared_count;

public:
	weak_count() noexcept: pi_(NULL) {}
	
	weak_count(const shared_count &r) noexcept: pi_(r.pi_)
	{
		if (pi_ != NULL) pi_->weak_add_ref();
	}

	weak_count(const weak_count &r) noexcept: pi_(r.pi_)
	{
		if (pi_ != NULL) pi_->weak_add_ref();
	}

#if __cplusplus >= 201103L
	weak_count(weak_count &&r) noexcept: pi_(r.pi_)
	{
		r.pi_ = NULL;
	}
#endif

	~weak_count() noexcept
	{
		if (pi_ != NULL) pi_->weak_release();
	}

	weak_count &operator =(const shared_count &r) noexcept
	{
		sp_counted_base *tmp = r.pi_;

		if (tmp != pi_) {
			if (tmp != NULL) tmp->weak_add_ref();
			if (pi_ != NULL) pi_->weak_release();
			pi_ = tmp;
		}

		return *this;
	}

	weak_count &operator =(const weak_count &r) noexcept
	{
		sp_counted_base *tmp = r.pi_;

		if (tmp != pi_) {
			if (tmp != NULL) tmp->weak_add_ref();
			if (pi_ != NULL) pi_->weak_release();
			pi_ = tmp;
		}

		return *this;
	}

	void swap(weak_count &r) noexcept
	{
		std::swap(pi_, r.pi_);
	}

	long use_count() const noexcept
	{
		return pi_ != NULL ? pi_->use_count() : 0;
	}

	bool empty() const noexcept
	{
		return pi_ == NULL;
	}

	friend inline bool operator ==(const weak_count &a, const weak_count &b)
	{
		return a.pi_ == b.pi_;
	}

	friend inline bool operator <(const weak_count &a, const weak_count &b)
	{
		return std::less<sp_counted_base *>()(a.pi_, b.pi_);
	}
};

inline shared_count::shared_count(weak_count const &r): pi_(r.pi_)
{
	if (pi_ == 0 || !pi_->add_ref_lock()) {
		throw bad_weak_ptr();
	}
}

}	// namespace detail

}	// namespace Hx

#endif

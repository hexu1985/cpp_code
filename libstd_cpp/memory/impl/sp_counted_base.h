// -*- C++ -*-
// HeXu's
// 2014 May

#ifndef HX_SP_COUNTED_BASE_H
#define HX_SP_COUNTED_BASE_H

namespace Hx {

namespace detail {

class sp_counted_base {
private:
    long use_count_;        // #shared
    long weak_count_;       // #weak + (#shared != 0)

#if __cplusplus >= 201103L
    sp_counted_base(const sp_counted_base &) = delete;
    sp_counted_base &operator =(const sp_counted_base &) = delete;
#else
    sp_counted_base(const sp_counted_base &);
    sp_counted_base &operator =(const sp_counted_base &);
#endif

public:
    sp_counted_base(): use_count_(1), weak_count_(1) {}

    virtual ~sp_counted_base() noexcept {}

    // dispose() is called when use_count_ drops to zero, to release
    // the resources managed by *this.
    virtual void dispose() = 0; // nothrow

    // destroy() is called when weak_count_ drops to zero.
    virtual void destroy() noexcept
    {
        delete this;
    }

    virtual void *get_deleter() = 0;

    void add_ref_copy()
    {
        ++use_count_;
    }

    bool add_ref_lock() // true on success
    {
        if(use_count_ == 0) return false;
        ++use_count_;
        return true;
    }

    void release() noexcept
    {
        if(--use_count_ == 0) {
            dispose();
            weak_release();
        }
    }

    void weak_add_ref() noexcept
    {
        ++weak_count_;
    }

    void weak_release() noexcept
    {
        if(--weak_count_ == 0) {
            destroy();
        }
    }

    long use_count() const noexcept
    {
        return use_count_;
    }
};

}	// namespace detail

}	// namespace Hx

#endif

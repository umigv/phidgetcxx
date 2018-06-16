#ifndef UMIGV_PHIDGETCXX_DETAIL_LOCKED_REF_HPP
#define UMIGV_PHIDGETCXX_DETAIL_LOCKED_REF_HPP

#include <mutex>
#include <utility>

#include <gsl/gsl>

namespace phidgetcxx {
namespace detail {

template <typename T>
class LockedRef {
public:
    LockedRef(T &t, std::mutex &mutex) : t_ptr_{ &t }, mutex_ptr_{ &mutex } {
        mutex.lock();
    }

    LockedRef(LockedRef &&other) : t_ptr_{ other.t_ptr_ },
                                   mutex_ptr_{ other.mutex_ptr_ } {
        other.t_ptr_ = nullptr;
        other.mutex_ptr_ = nullptr;
    }

    ~LockedRef() {
        if (t_ptr_ && mutex_ptr_) {
            mutex_ptr_->unlock();
        }
    }

    LockedRef& operator=(LockedRef &&other) {
        if (this == &other) {
            return *this;
        }

        auto moved = std::move(other);
        std::swap(*this, moved);

        return *this;
    }

    T& get() const {
        return *t_ptr_;
    }

private:
    T *t_ptr_;
    std::mutex *mutex_ptr_;
};

} // namespace detail
} // namespace phidgetcxx

#endif

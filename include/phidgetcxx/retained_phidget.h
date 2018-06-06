#ifndef UMIGV_PHIDGETCXX_RETAINED_PHIDGET_H
#define UMIGV_PHIDGETCXX_RETAINED_PHIDGET_H

#include "phidgetcxx/phidget.h"

#include <boost/optional.hpp>

namespace phidgetcxx {

// class to wrap a Phidget that has been retained
// could be implemented as a unqiue_ptr or something similar, but this allows
// stack usage
class RetainedPhidget {
public:
    friend Phidget;

    RetainedPhidget(RetainedPhidget &&other) noexcept;

    RetainedPhidget(Phidget &phidget);

    RetainedPhidget& operator=(RetainedPhidget &&other) noexcept;

    ~RetainedPhidget();

    constexpr bool has_phidget() const noexcept {
        return static_cast<bool>(phidget_);
    }

    constexpr Phidget& phidget() noexcept {
        return phidget_.value();
    }

    constexpr const Phidget& phidget() const noexcept {
        return phidget_.value();
    }

private:
    RetainedPhidget() = default;

    static RetainedPhidget from_retained(Phidget &phidget) noexcept;

    static RetainedPhidget from_retained(PhidgetHandle handle) noexcept;

    Phidget& retain(Phidget &phidget);

    void release();

    boost::optional<Phidget> phidget_;
};

} // namespace phidgetcxx

#endif

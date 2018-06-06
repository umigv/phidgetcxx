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

    bool has_phidget() const noexcept;
    
    Phidget& phidget() noexcept;

    const Phidget& phidget() const noexcept;

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

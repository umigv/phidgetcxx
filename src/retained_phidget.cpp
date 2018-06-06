#include "phidgetcxx/retained_phidget.h"

#include "phidgetcxx/exception.h"
#include "phidgetcxx/return_code.h"

#include <utility>

namespace phidgetcxx {

RetainedPhidget::RetainedPhidget(RetainedPhidget &&other)
noexcept : phidget_{ std::move(other.phidget_) } {
    other.phidget_ = boost::none;
}

RetainedPhidget::RetainedPhidget(Phidget &phidget)
: phidget_{ retain(phidget) } { }

RetainedPhidget& RetainedPhidget::operator=(RetainedPhidget &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    if (phidget_) {
        release();
    }

    phidget_ = std::move(other.phidget_);
    other.phidget_ = boost::none;

    return *this;
}

RetainedPhidget::~RetainedPhidget() {
    // this is also bad style
    release();
}

bool RetainedPhidget::has_phidget() const noexcept {
    return static_cast<bool>(phidget_);
}

Phidget& RetainedPhidget::phidget() noexcept {
    return phidget_.value();
}

const Phidget& RetainedPhidget::phidget() const noexcept {
    return phidget_.value();
}

RetainedPhidget
RetainedPhidget::from_retained(Phidget &phidget) noexcept {
    return from_retained(phidget.handle_);
}

RetainedPhidget
RetainedPhidget::from_retained(PhidgetHandle handle) noexcept {
    RetainedPhidget retained;
    retained.phidget_ = Phidget{ handle };

    return retained;
}

Phidget& RetainedPhidget::retain(Phidget &phidget) {
    const auto ret = as_cxx(Phidget_retain(phidget.handle_));

    if (!ret) {
        throw Exception{ "phidgetcxx::RetainedPhidget::retain", ret };
    }

    return phidget;
}

void RetainedPhidget::release() {
    if (!phidget_) {
        return;
    }

    const auto ret = as_cxx(Phidget_release(&phidget_.value().handle_));

    if (!ret) {
        throw Exception{ "phidgetcxx::RetainedPhidget::release", ret };
    }
}

} // namespace phidgetcxx

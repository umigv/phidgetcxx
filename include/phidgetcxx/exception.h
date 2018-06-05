#ifndef UMIGV_PHIDGETCXX_EXCEPTION_H
#define UMIGV_PHIDGETCXX_EXCEPTION_H

#include <stdexcept>
#include <string>

#include "phidgetcxx/return_code.h"

namespace phidgetcxx {

class Exception : public std::runtime_error {
public:
    Exception(const std::string &what, ReturnCode code);

    Exception(const char *what, ReturnCode code);

    ~Exception() = default;

    ReturnCode code() const noexcept;

private:
    ReturnCode code_;
};

} // namespace phidgetcxx

#endif

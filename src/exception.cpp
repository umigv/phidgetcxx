#include "phidgetcxx/exception.h"

namespace phidgetcxx {

Exception::Exception(const std::string &what, const ReturnCode code)
: std::runtime_error{ what }, code_{ code } { }

Exception::Exception(const char *const what, const ReturnCode code)
: std::runtime_error{ what }, code_{ code } { }

ReturnCode Exception::code() const noexcept {
    return code_;
}

} // namespace phidgetcxx

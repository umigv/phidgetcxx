#ifndef UMIGV_PHIDGETCXX_STATIC_H
#define UMIGV_PHIDGETCXX_STATIC_H

#include "phidgetcxx/exception.h"
#include "phidgetcxx/return_code.h"

#include <cstdint>

#include <gsl/gsl>

namespace phidgetcxx {

gsl::czstring_span<> get_error_description(ReturnCode code);

void finalize(std::int32_t flags = 0);

gsl::czstring_span<> get_library_version();

} // namespace phidgetcxx

#endif

#include "phidgetcxx/static.h"

#include "phidgetcxx/common.h"

#include <cstring>

namespace phidgetcxx {

gsl::czstring_span<> get_error_description(const ReturnCode code) {
    gsl::czstring<> description = nullptr;
    const auto code_c = static_cast<PhidgetReturnCode>(code);

    const auto ret = as_cxx(Phidget_getErrorDescription(code_c, &description));

    if (!ret) {
        throw Exception{ "phidgetcxx::get_error_description", ret };
    }

    return as_span(gsl::not_null<gsl::czstring<>>{ description });
}

void finalize(const std::int32_t flags) {
    const auto ret = as_cxx(Phidget_finalize(flags));

    if (!ret) {
        throw Exception{ "phidgetcxx::finalize", ret };
    }
}

gsl::czstring_span<> get_library_version() {
    gsl::czstring<> version = nullptr;
    const auto ret = as_cxx(Phidget_getLibraryVersion(&version));

    if (!ret) {
        throw Exception{ "phidgetcxx::get_library_version", ret };
    }

    return as_span(gsl::not_null<gsl::czstring<>>{ version });
}

} // namespace phidgetcxx

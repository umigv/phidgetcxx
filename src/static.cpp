#include "phidgetcxx/static.h"

#include <cstring>

namespace phidgetcxx {

gsl::cstring_span<> get_error_description(const ReturnCode code) {
    gsl::czstring<> description = nullptr;
    const auto code_c = static_cast<PhidgetReturnCode>(code);

    const auto ret =
        as_return_code(Phidget_getErrorDescription(code_c, &description));

    if (!ret) {
        throw Exception{ "phidgetcxx::get_error_description", ret };
    }

    const auto length =
        static_cast<gsl::cstring_span<>::index_type>(std::strlen(description));

    return { description, length };
}

void finalize(const std::int32_t flags) {
    const auto ret = as_return_code(Phidget_finalize(flags));

    if (!ret) {
        throw Exception{ "phidgetcxx::finalize", ret };
    }
}

gsl::cstring_span<> get_library_version() {
    gsl::czstring<> version = nullptr;
    const auto ret = as_return_code(Phidget_getLibraryVersion(&version));

    if (!ret) {
        throw Exception{ "phidgetcxx::get_library_version", ret };
    }

    const auto length =
        static_cast<gsl::cstring_span<>::index_type>(std::strlen(version));

    return { version, length };
}

} // namespace phidgetcxx

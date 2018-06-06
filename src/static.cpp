#include "phidgetcxx/static.h"

#include <cstring>

namespace phidgetcxx {
namespace detail {

static inline gsl::czstring_span<> as_span(const gsl::czstring<> string) {
    if (!string) {
        throw std::invalid_argument{ "phidgetcxx::detail::as_span" };
    }

    const auto length =
        static_cast<gsl::cstring_span<>::index_type>(std::strlen(string));
    const gsl::cstring_span<> span{ string, length };

    return { span };
}

} // namespace detail

gsl::czstring_span<> get_error_description(const ReturnCode code) {
    gsl::czstring<> description = nullptr;
    const auto code_c = static_cast<PhidgetReturnCode>(code);

    const auto ret = as_cxx(Phidget_getErrorDescription(code_c, &description));

    if (!ret) {
        throw Exception{ "phidgetcxx::get_error_description", ret };
    }

    return detail::as_span(description);
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

    return detail::as_span(version);
}

} // namespace phidgetcxx

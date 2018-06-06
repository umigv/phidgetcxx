#ifndef UMIGV_PHIDGETCXX_COMMON_H
#define UMIGV_PHIDGETCXX_COMMON_H

#include <stdexcept>
#include <string>

#include <gsl/gsl>

namespace phidgetcxx {

inline gsl::czstring_span<>
as_span(const gsl::not_null<gsl::czstring<>> string) {
    using IndexT = gsl::cstring_span<>::index_type;
    using TraitsT = std::char_traits<char>;

    const auto length = static_cast<IndexT>(TraitsT::length(string));
    const gsl::cstring_span<> span{ string, length + 1 };

    return { span };
}

} // namespace phidgetcxx

#endif

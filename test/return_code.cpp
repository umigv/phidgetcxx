#include "catch.hpp"

#include "phidgetcxx/return_code.h"
#include "phidgetcxx/static.h"

#include <phidget22.h>

TEST_CASE("ReturnCodes convert properly", "[phidgetcxx][ReturnCode]") {
    const auto code_c = EPHIDGET_OK;
    const auto code_cxx = phidgetcxx::as_return_code(code_c);

    REQUIRE(code_cxx == phidgetcxx::ReturnCode::Ok);

    const auto description_cxx = phidgetcxx::get_error_description(code_cxx);

    gsl::czstring<> description_cz = nullptr;
    const auto ret = Phidget_getErrorDescription(code_c, &description_cz);

    REQUIRE(ret == EPHIDGET_OK);

    const std::string description_c = description_cz;

    REQUIRE(description_cxx == description_c);
}

#pragma once

#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/schema.hpp>
#include <ql/termstructures/yield/ratehelpers.hpp>

namespace QuantLibParser {

    template <>
    void Schema<QuantLib::SwapRateHelper>::initSchema();

    template <>
    void Schema<QuantLib::SwapRateHelper>::initDefaultValues();

}  // namespace QuantLibParser

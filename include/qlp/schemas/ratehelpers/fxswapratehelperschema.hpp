#pragma once

#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/schema.hpp>
#include <ql/termstructures/yield/ratehelpers.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::FxSwapRateHelper>::initSchema();

    template <>
    void Schema<QuantLib::FxSwapRateHelper>::initDefaultValues();

}  // namespace QuantLibParser

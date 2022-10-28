#pragma once

#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/schema.hpp>
#include <ql/termstructures/yield/bondhelpers.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::DepositRateHelper>::initSchema();

    template <>
    void Schema<QuantLib::DepositRateHelper>::initDefaultValues();
}  // namespace QuantLibParser

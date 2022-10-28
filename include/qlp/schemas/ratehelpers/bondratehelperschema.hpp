#pragma once

#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/schema.hpp>
#include <ql/termstructures/yield/bondhelpers.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::FixedRateBondHelper>::initSchema();

    template <>
    void Schema<QuantLib::FixedRateBondHelper>::initDefaultValues();
}  // namespace QuantLibParser

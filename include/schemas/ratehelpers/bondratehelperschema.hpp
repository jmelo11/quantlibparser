#pragma once

#include <schemas/commonschemas.hpp>
#include <schemas/schema.hpp>
#include <ql/termstructures/yield/bondhelpers.hpp>

namespace QuantLibParser
{
    template <>
    void Schema <QuantLib::FixedRateBondHelper> ::initSchema();

    template <>
    void Schema<QuantLib::FixedRateBondHelper>::initDefaultValues();
}

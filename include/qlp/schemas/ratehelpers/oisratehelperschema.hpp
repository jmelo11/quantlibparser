#pragma once

#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/schema.hpp>
#include <ql/termstructures/yield/oisratehelper.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::OISRateHelper>::initSchema();

    template <>
    void Schema<QuantLib::OISRateHelper>::initDefaultValues();

}  // namespace QuantLibParser

#pragma once
#pragma once

#include <schemas/commonschemas.hpp>
#include <schemas/schema.hpp>
#include <ql/termstructures/yield/oisratehelper.hpp>

namespace QuantLibParser
{
    template <>
    void Schema <QuantLib::OISRateHelper> ::initSchema();

    template<>
    void Schema<QuantLib::OISRateHelper>::initDefaultValues();
	
}

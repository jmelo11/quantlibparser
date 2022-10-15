#pragma once
#pragma once

#include <schemas/commonschemas.hpp>
#include <schemas/schema.hpp>
#include <ql/termstructures/yield/ratehelpers.hpp>

namespace QuantLibParser
{
    template <>
    void Schema <QuantLib::FxSwapRateHelper> ::initSchema();

    template<>
    void Schema<QuantLib::FxSwapRateHelper>::initDefaultValues();
	
}

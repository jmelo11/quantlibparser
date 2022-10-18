#pragma once

#include <schemas/schema.hpp>
#include <ql/indexes/interestrateindex.hpp>

namespace QuantLibParser
{
	template<>
	void Schema<QuantLib::InterestRateIndex>::initSchema();

	template<>
	void Schema<QuantLib::InterestRateIndex>::initDefaultValues();
}
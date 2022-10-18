#pragma once

#include <schemas/schema.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>


namespace QuantLibParser
{
	template <>
	void Schema<QuantLib::YieldTermStructure>::initSchema();

	template <>
	void Schema<QuantLib::YieldTermStructure>::initDefaultValues();
}


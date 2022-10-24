#pragma once

#include <qlp/schemas/schema.hpp>
#include <ql/termstructures/yield/flatforward.hpp>

namespace QuantLibParser
{
	template <>
	void Schema<QuantLib::FlatForward> ::initSchema();

	template<>
	void Schema<QuantLib::FlatForward>::initDefaultValues();

}
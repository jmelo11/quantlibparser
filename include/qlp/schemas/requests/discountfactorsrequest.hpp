#pragma once

#include <qlp/schemas/schema.hpp>

namespace QuantLibParser
{
	class DiscountFactorsRequest;
	template <>
	void Schema<DiscountFactorsRequest>::initSchema();

	template<>
	void Schema<DiscountFactorsRequest>::initDefaultValues();

}
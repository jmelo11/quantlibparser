#pragma once

#include <qlp/schemas/schema.hpp>

namespace QuantLibParser
{
	class ForwardRatesRequest;
	template <>
	void Schema<ForwardRatesRequest>::initSchema();

	template<>
	void Schema<ForwardRatesRequest>::initDefaultValues();

}
#pragma once

#include <qlp/schemas/schema.hpp>

namespace QuantLibParser
{
	class ZeroRatesRequests;
	template <>
	void Schema<ZeroRatesRequests>::initSchema();

	template<>
	void Schema<ZeroRatesRequests>::initDefaultValues();

}
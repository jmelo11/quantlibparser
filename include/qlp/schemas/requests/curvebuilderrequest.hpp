#pragma once

#include <qlp/schemas/schema.hpp>

namespace QuantLibParser
{
	class CurveBuilderRequest;
	template <>
	void Schema<CurveBuilderRequest>::initSchema();

	template<>
	void Schema<CurveBuilderRequest>::initDefaultValues();

}
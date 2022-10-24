#pragma once

#include <qlp/schemas/schema.hpp>
#include <ql/termstructures/yield/piecewiseyieldcurve.hpp>

namespace QuantLibParser
{
	template <>
	void Schema<QuantLib::PiecewiseYieldCurve<QuantLib::LogLinear, QuantLib::Discount>> ::initSchema();

	template<>
	void Schema<QuantLib::PiecewiseYieldCurve<QuantLib::LogLinear, QuantLib::Discount>>::initDefaultValues();

}
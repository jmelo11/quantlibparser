#pragma once

#include <qlp/schemas/schema.hpp>
#include <ql/termstructures/yield/piecewiseyieldcurve.hpp>
#include <ql/math/interpolations/loginterpolation.hpp>
#include <ql/termstructures/yield/bootstraptraits.hpp>

namespace QuantLibParser
{
	template <>
	void Schema<QuantLib::PiecewiseYieldCurve<QuantLib::Discount, QuantLib::LogLinear>>::initSchema();

	template<>
	void Schema<QuantLib::PiecewiseYieldCurve<QuantLib::Discount, QuantLib::LogLinear>>::initDefaultValues();

}
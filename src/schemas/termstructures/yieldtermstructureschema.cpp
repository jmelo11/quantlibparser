#pragma once
#include <schemas/termstructures/yieldtermstructureschema.hpp>


namespace QuantLibParser
{
	template <>
	void Schema<QuantLib::YieldTermStructure>::initSchema()
	{
		json base = R"({
            "title": "General Curve Schema",
			"type": "object",
            "anyOf": []
        })"_json;
		
		
		Schema<QuantLib::FlatForward> flatForwardSchema;
		Schema<QuantLib::DiscountCurve> discountCurveSchema;
		Schema<QuantLib::PiecewiseYieldCurve<QuantLib::LogLinear, QuantLib::Discount>> piecewiseCurveSchema;
				
		base["anyOf"].emplace_back(flatForwardSchema.schema());
		base["anyOf"].emplace_back(discountCurveSchema.schema());
		base["anyOf"].emplace_back(piecewiseCurveSchema.schema());
				
		mySchema_ = base;
	}

	template <>
	void Schema<QuantLib::YieldTermStructure>::initDefaultValues()
	{
		
	}

}
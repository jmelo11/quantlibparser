#pragma once

#include <schemas/termstructures/rateindexschema.hpp>

namespace QuantLibParser
{
	template<>
	void Schema<QuantLib::InterestRateIndex>::initSchema()
	{
		json base = R"({
            "title": "Flat Forward Curve Schema",
            "properties": {},			
            "required": ["TYPE", "NAME", "ENABLEEXTRAPOLATION", "RATE"]
        })"_json;
		
		base["properties"] = baseCurveSchema;
		base["properties"]["RATE"] = priceSchema;

		base["properties"]["DAYCOUNTER"] = dayCounterSchema;
		base["properties"]["COMPOUNDING"] = compoundingSchema;
		base["properties"]["FREQUENCY"] = frequencySchema;

		mySchema_ = base;
	}

	template<>
	void Schema<QuantLib::InterestRateIndex>::initDefaultValues()
	{
		myDefaultValues_["ENABLEEXTRAPOLATION"] = true;
		myDefaultValues_["DAYCOUNTER"] = "ACT360";
		myDefaultValues_["COMPOUNDING"] = "SIMPLE";
		myDefaultValues_["FREQUENCY"] = "ANNUAL";
	}
}
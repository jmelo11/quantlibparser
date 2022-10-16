#include <schemas/termstructures/discountcurveschema.hpp>
#include <schemas/commonschemas.hpp>

namespace QuantLibParser
{
	template <>
	void Schema<QuantLib::DiscountCurve> ::initSchema()
	{
		json base = R"({
            "title": "Discount Curve Schema",
            "properties": {},			
            "required": ["NAME", "ENABLEEXTRAPOLATION", "NODES"]
        })"_json;

		json nodes = R"({
			"type": "array",
			"items": {
				"type": "object",
				"properties": {
					"DATE": {},
					"VALUE": {}
				},
				"required":["DATE","VALUE"]
			}
		})"_json;

		base["properties"] = baseCurveSchema;
		
			
		nodes["items"]["properties"]["DATE"] = dateSchema;
		nodes["items"]["properties"]["VALUE"] = priceSchema;
		
		base["properties"]["NODES"] = nodes;

		mySchema_ = base;
	}
	
	template<>
	void Schema<QuantLib::DiscountCurve>::initDefaultValues()
	{
		myDefaultValues_["ENABLEEXTRAPOLATION"] = true;
		myDefaultValues_["DAYCOUNTER"] = "ACT360";
	}

}
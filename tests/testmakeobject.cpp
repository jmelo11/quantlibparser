#include "pch.hpp"
#include <qlp/schemas/termstructures/discountcurveschema.hpp>
#include <qlp/schemas/termstructures/flatforwardcurveschema.hpp>

using namespace QuantLibParser;

TEST(MakeObject, DiscountCurve) {
    json data = R"({   
        "TYPE": "DISCOUNT",    
		"NAME": "USD",
		"DAYCOUNTER": "ACT360",
		"ENABLEEXTRAPOLATION": true,
		"NODES": [
			{
				"DATE": "01012019",
				"VALUE": 1.0
			},
			{
				"DATE": "01022019",
				"VALUE": 0.98
			}
		]
	})"_json;
    Schema<QuantLib::DiscountCurve> curveSchema;
    EXPECT_TRUE(curveSchema.isValid(data));

    std::optional<QuantLib::DiscountCurve> curve = curveSchema.makeObj(data);
    EXPECT_TRUE(curve.has_value());
    EXPECT_TRUE(curve.value().allowsExtrapolation());
}

TEST(MakeObject, FlatForwardCurve) {
    json data = R"({   
		"TYPE": "FLATFORWARD",    
		"NAME": "USD",
		"DAYCOUNTER": "ACT360",
		"ENABLEEXTRAPOLATION": true,
		"REFDATE": "01012019",
		"RATE": 0.01
	})"_json;
    Schema<QuantLib::FlatForward> curveSchema;
    EXPECT_TRUE(curveSchema.isValid(data));

    std::optional<QuantLib::FlatForward> curve = curveSchema.makeObj(data);
    EXPECT_TRUE(curve.has_value());
    EXPECT_TRUE(curve.value().allowsExtrapolation());
}
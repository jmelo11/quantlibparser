#include "pch.hpp"
#include <qlp/schemas/ratehelpers/bondratehelperschema.hpp>
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

TEST(MakeObject, FixedRateBondHelper) {
    json testSchema = R"({
            "TYPE": "BOND",
			"RATE": 0.033518703852712,
            "RATETICKER": "BOND_1D",
            "TENOR": "5M"            
		})"_json;

    PriceGetter f = [](double price, const std::string& ticker) {
        boost::shared_ptr<QuantLib::Quote> quote(new QuantLib::SimpleQuote(0.03));
        QuantLib::Handle<QuantLib::Quote> handle(quote);
        return handle;
    };

    Schema<QuantLib::FixedRateBondHelper> bondSchema;

    EXPECT_NO_THROW(bondSchema.makeObj(testSchema, f));
}
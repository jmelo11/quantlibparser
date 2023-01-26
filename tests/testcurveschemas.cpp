#include "pch.hpp"
#include <qlp/schemas/termstructures/bootstrapcurveschema.hpp>
#include <qlp/schemas/termstructures/discountcurveschema.hpp>
#include <qlp/schemas/termstructures/flatforwardcurveschema.hpp>

using namespace QuantLib;
using namespace QuantLibParser;

TEST(CurveSchemas, DiscountCurve) {
    json data = R"({   
        "curveType":"Discount",			
		"nodes": [
			{
				"date": "2019-01-01",
				"value": 0.99
			},
			{
				"date": "2019-02-01",
				"value": 0.98
			}
		]
	})"_json;

    Schema<DiscountCurve> curveSchema;

    EXPECT_NO_THROW(curveSchema.validate(data));

    data = R"({
        "curveType":"Discount",		
		"dayCounter": "Act360",
		"enableExtrapolation": true,
		"nodes": [
			{
				"date": "2019-02-01",
				"value": 0.99
			},
			{
				"date": "2019-02-02"		
			}
		]
	})"_json;

    EXPECT_ANY_THROW(curveSchema.validate(data));
}

TEST(CurveSchemas, FlatForwardCurve) {
    json data = R"({   
        "curveType":"FlatForward",
        "refDate": "2019-02-01",
		"dayCounter": "Act360",
		"enableExtrapolation": true,
		"rate":0.03
	})"_json;
    Schema<FlatForward> curveSchema;
    EXPECT_NO_THROW(curveSchema.validate(data));
}

TEST(CurveSchemas, BootstrapCurve) {
    json data = R"({
            "curveType": "Piecewise",
            "dayCounter": "Act360",
            "enableExtrapolation": true,
            "rateHelpers": [
                {
                    "helperType": "Bond",
                    "helperConfig": {
                        "tenor": "2Y",
                        "calendar": "NullCalendar"                
                    },
                    "marketConfig": {
                        "rate": {
                            "ticker": "BondTicker",
                            "value": 0.05
                        }
                    }
                },    
                {
                    "helperType": "Bond",
                    "helperConfig": {
                        "tenor": "3Y",
                        "calendar": "NullCalendar"                
                    },
                    "marketConfig": {
                        "rate": {
                            "ticker": "BondTicker",
                            "value": 0.05
                        }
                    }
                }
            ]
        })"_json;

    Schema<PiecewiseYieldCurve<Discount, LogLinear>> curveSchema;
    EXPECT_NO_THROW(curveSchema.validate(data));
}

TEST(CurveSchemas, IborIndex) {
    json data = R"({
            "indexType": "IborIndex",
            "indexName": "LIBOR1M",
            "tenor": "1M",
            "dayCounter": "Act360",
            "currency": "USD",
            "settlementDays": 0,
            "calendar": "UnitedStates"
        })"_json;

    Schema<IborIndex> indexSchema;
    EXPECT_NO_THROW(indexSchema.validate(data));
}

TEST(CurveSchemas, OvernightIndex) {
    json data = R"({
            "indexType": "OvernightIndex",
            "indexName": "LIBOR1M",
            "tenor": "1M",
            "dayCounter": "Act360",
            "currency": "USD",
            "settlementDays": 0,
            "calendar": "UnitedStates"
        })"_json;

    Schema<OvernightIndex> indexSchema;
    EXPECT_NO_THROW(indexSchema.validate(data));
}
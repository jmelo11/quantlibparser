#include "pch.hpp"
#include <ql/indexes/ibor/fedfunds.hpp>
#include <qlp/schemas/ratehelpers/bondratehelperschema.hpp>
#include <qlp/schemas/ratehelpers/depositratehelperschema.hpp>
#include <qlp/schemas/ratehelpers/fixfloatxccyratehelperschema.hpp>
#include <qlp/schemas/ratehelpers/fxswapratehelperschema.hpp>
#include <qlp/schemas/ratehelpers/oisratehelperschema.hpp>
#include <qlp/schemas/ratehelpers/swapratehelperschema.hpp>
#include <qlp/schemas/ratehelpers/tenorbasisratehelperschema.hpp>
#include <qlp/schemas/ratehelpers/xccybasisratehelperschema.hpp>
#include <qlp/schemas/termstructures/discountcurveschema.hpp>
#include <qlp/schemas/termstructures/flatforwardcurveschema.hpp>
#include <qlp/schemas/termstructures/interestrateschema.hpp>

using namespace QuantLibParser;

PriceGetter f = [](double price, const std::string& ticker) {
    boost::shared_ptr<QuantLib::Quote> quote(new QuantLib::SimpleQuote(0.03));
    QuantLib::Handle<QuantLib::Quote> handle(quote);
    return handle;
};

IndexGetter g = [](const std::string& name) {
    if (name == "LIBOR1M") {
        auto flatForwardCurve = QuantLib::Handle<QuantLib::YieldTermStructure>(
            boost::make_shared<QuantLib::FlatForward>(0, QuantLib::NullCalendar(), 0.01, QuantLib::Actual360()));
        auto index = boost::shared_ptr<QuantLib::IborIndex>(
            new QuantLib::IborIndex("LIBOR1M", QuantLib::Period(1, QuantLib::Months), 0, QuantLib::USDCurrency(), QuantLib::NullCalendar(),
                                    QuantLib::BusinessDayConvention::Unadjusted, false, QuantLib::Actual360(), flatForwardCurve));
        return index;
    } else {
        auto index = boost::shared_ptr<QuantLib::IborIndex>(
            new QuantLib::IborIndex("LIBOR1M", QuantLib::Period(1, QuantLib::Months), 0, QuantLib::USDCurrency(), QuantLib::NullCalendar(),
                                    QuantLib::BusinessDayConvention::Unadjusted, false, QuantLib::Actual360()));
        return index;
    }
};

IndexGetter sofrIndex = [](const std::string& name) {
    auto index = boost::make_shared<QuantLib::FedFunds>();
    return index;
};

CurveGetter h = [](const std::string& name) {
    auto curve = boost::make_shared<QuantLib::FlatForward>(0, QuantLib::NullCalendar(), 0.03, QuantLib::Actual360());
    QuantLib::RelinkableHandle<QuantLib::YieldTermStructure> curveHandle(curve);
    return curveHandle;
};

TEST(MakeObject, DiscountCurve) {
    json data = R"({
        "curveType": "Discount",   
        "nodes": [
			{
				"date": "2019-01-01",
				"value": 1.0
			},
			{
				"date": "2019-02-01",
				"value": 0.98
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
        "curveType": "FlatForward",	
		"dayCounter": "Act360",
		"enableExtrapolation": true,
		"refDate": "2019-01-01",
		"rate": 0.01
	})"_json;
    Schema<QuantLib::FlatForward> curveSchema;
    EXPECT_TRUE(curveSchema.isValid(data));

    std::optional<QuantLib::FlatForward> curve = curveSchema.makeObj(data);
    EXPECT_TRUE(curve.has_value());
    EXPECT_TRUE(curve.value().allowsExtrapolation());
}

TEST(MakeObject, FixedRateBondHelper) {
    json testSchema = R"({
            "helperType": "Bond",
            "helperConfig": {
                "tenor": "2Y"
            },
            "marketConfig": {
                "rate": {
                    "ticker": "BondTicker",
                    "value": 0.05
                }
            }
    })"_json;

    Schema<QuantLib::FixedRateBondHelper> schema;
    EXPECT_NO_THROW(schema.makeObj(testSchema, f));
}

TEST(MakeObject, DepositRateHelper) {
    json testSchema = R"({
            "helperType": "Deposit",
            "helperConfig": {
                "tenor": "1Y",
                "calendar": "NullCalendar"                
            },
            "marketConfig": {
                "rate": {
                    "ticker": "DepositTicker",
                    "value": 0.05
                }
            }
    })"_json;

    Schema<QuantLib::DepositRateHelper> schema;
    EXPECT_NO_THROW(schema.makeObj(testSchema, f));
}

TEST(MakeObject, CrossCcyFixFloatSwapHelper) {
    json testSchema = R"({
            "helperType": "Xccy",
            "helperConfig": {
                "tenor": "1Y",
                "fixedLegCurrency": "CLP",
                "index": "ICP"
            },
            "marketConfig": {
                "rate": {
                    "ticker": "XccyTicker",
                    "value": 0.05
                },
                "fxSpot":{
                    "ticker": "fxSpotTicker", "value": 100
                },
                "spread": {
                    "value": 0.0, "ticker": "spreadTicker"
                }
            }                
		})"_json;

    Schema<QuantExt::CrossCcyFixFloatSwapHelper> schema;
    EXPECT_NO_THROW(schema.makeObj(testSchema, f, g, h));
}

TEST(MakeObject, FxSwapRateHelper) {
    json testSchema = R"({
            "helperType": "FxSwap",
            "helperConfig": {
                "tenor": "1Y",
                "baseCurrencyAsCollateral": false
            },
            "marketConfig": {
                "fxPoints": {
                    "ticker": "fxPointsTicker",
                    "value": 5
                },
                "fxSpot":{
                    "value": 100,
                    "ticker": "fxSpotTicker"
                }
            }     
		})"_json;

    Schema<QuantLib::FxSwapRateHelper> schema;
    EXPECT_NO_THROW(schema.makeObj(testSchema, f, h));

    testSchema = R"({
            "helperType": "FxSwap",
            "helperConfig": {
                "endDate": "2025-01-29",
                "baseCurrencyAsCollateral": false
            },
            "marketConfig": {
                "fxPoints": {
                    "ticker": "fxPointsTicker",
                    "value": 5
                },
                "fxSpot":{
                    "value": 100,
                    "ticker": "fxSpotTicker"
                }
            }     
		})"_json;

    EXPECT_NO_THROW(schema.makeObj(testSchema, f, h));

    testSchema = R"( {
                      "helperType": "FxSwap",
                      "helperConfig": {
                          "calendar": "NullCalendar",
                          "fixingDays": 0,
                          "endOfMonth": false,
                          "baseCurrencyAsCollateral": false,
                          "convention": "Following",                          
                          "endDate": "2023-03-09T00:00:00.000Z",
                          "settlementDays": 0
                      },
                      "marketConfig": {
                          "_id": "63ebd519f6f786e1b8409721",
                          "createdAt": "2023-02-14T18:38:09.868Z",
                          "helperId": "63ea64f0d74390dd819e0e3a",
                          "fxSpot": {
                              "value": 35368.49,
                              "ticker": "CLUFUF INDEX"
                          },
                          "fxPoints": {
                              "value": 232.2573,
                              "ticker": ".NDFUF0M INDEX"
                          }
                      }
                  })"_json;

    EXPECT_ANY_THROW(schema.makeObj(testSchema, f, h));
}

TEST(MakeObject, OISRateHelper) {
    json testSchema = R"({
            "helperType": "OIS",
            "helperConfig": {
                "tenor": "1Y",
                "index": "SOFR"
            },
            "marketConfig": {
                "rate": {
                    "ticker": "rateTicker",
                    "value": 0.03
                },
                "spread":{
                    "value": 0.0,
                    "ticker": "spreadTicker"
                }                
            }     
        })"_json;

    Schema<QuantLib::OISRateHelper> schema;
    EXPECT_NO_THROW(schema.makeObj(testSchema, f, sofrIndex, h));
}

TEST(MakeObject, SwapRateHelper) {
    json testSchema = R"({
            "helperType": "Swap",
            "helperConfig": {
                "tenor": "1Y",
                "index": "SOFR"
            },
            "marketConfig": {
                "rate": {
                    "ticker": "rateTicker",
                    "value": 0.03
                },
                "spread":{
                    "value": 0.0,
                    "ticker": "spreadTicker"
                }                
            }     
        })"_json;

    Schema<QuantLib::SwapRateHelper> schema;
    EXPECT_NO_THROW(schema.makeObj(testSchema, f, sofrIndex, h));
}

TEST(MakeObject, TenorBasisSwapHelper) {
    json testSchema = R"({
            "helperType": "TenorBasis",
            "helperConfig": {
                "tenor": "1Y",
                "shortIndex": "LIBOR1M",
                "longIndex": "LIBOR3M",
                "spreadOnShort": true
            },
            "marketConfig": {                
                "spread":{
                    "value": 0.0,
                    "ticker": "spreadTicker"
                }                
            }     
        })"_json;

    Schema<QuantExt::TenorBasisSwapHelper> schema;
    EXPECT_NO_THROW(schema.makeObj(testSchema, f, g, h));
}

TEST(MakeObject, CrossCcyBasisSwapHelper) {
    json testSchema = R"({
            "helperType": "XccyBasis",
            "helperConfig": {
                "tenor": "1Y",
                "flatIndex":"LIBOR1M",
                "spreadIndex": "LIBOR3M",
                "flatDiscountCurve":"LIBOR1M"
            },
            "marketConfig": {                
                "spread":{
                    "value": 0.0,
                    "ticker": "spreadTicker"
                },
                "fxSpot":{
                    "value": 100,
                    "ticker": "fxSpotTicker"
                }                
            }     
        })"_json;

    Schema<QuantExt::CrossCcyBasisSwapHelper> schema;
    EXPECT_NO_THROW(schema.makeObj(testSchema, f, g, h));
}

TEST(MakeObject, IborIndex) {
    json data = R"({
            "indexType":"IborIndex",
            "indexName": "LIBOR1M",
            "tenor": "1M",
            "dayCounter": "Act360",
            "currency": "USD",
            "settlementDays": 0,
            "calendar": "UnitedStates"
        })"_json;

    Schema<QuantLib::IborIndex> schema;
    EXPECT_NO_THROW(schema.makeObj(data, h));
}

TEST(MakeObject, OvernightIndex) {
    json data = R"({
            "indexType":"OvernightIndex",
            "indexName": "LIBOR1M",
            "dayCounter": "Act360",
            "currency": "USD",
            "settlementDays": 0,
            "calendar": "UnitedStates"
        })"_json;

    Schema<QuantLib::OvernightIndex> schema;
    EXPECT_NO_THROW(schema.makeObj(data, h));
}

TEST(MakeObject, InterestRate) {
    json data = R"({
            "value": 0.01,
            "dayCounter": "Act360",
            "compounding": "Compounded",
            "frequency": "Annual"
        })"_json;

    Schema<QuantLib::InterestRate> schema;
    EXPECT_NO_THROW(schema.makeObj(data));
}
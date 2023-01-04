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

    Schema<QuantLib::FixedRateBondHelper> schema;
    EXPECT_NO_THROW(schema.makeObj(testSchema, f));
}

TEST(MakeObject, DepositRateHelper) {
    json testSchema = R"(  {
            "RATE": 0.0227,
            "DAYCOUNTER": "ACT360",
            "TENOR": "1D",
            "CALENDAR": "USA",
            "FIXINGDAYS": 0.0,
            "ENDOFMONTH": true,
            "CONVENTION": "MODIFIEDFOLLOWING",
            "TYPE": "DEPOSIT",
            "RATETICKER": "SOFRRATE CURNCY"
          })"_json;

    Schema<QuantLib::DepositRateHelper> schema;
    EXPECT_NO_THROW(schema.makeObj(testSchema, f));
}

TEST(MakeObject, CrossCcyFixFloatSwapHelper) {
    json testSchema = R"({
            "RATE": 0.0641,
            "TENOR": "5Y",
            "DAYCOUNTER": "ACT360",
            "CALENDAR": "JOINT",
            "CONVENTION": "MODIFIEDFOLLOWING",
            "ENDOFMONTH": false,
            "FREQUENCY": "SEMIANNUAL",
            "SETTLEMENTDAYS": 2.0,
            "DISCOUNTINGCURVE": "SOFR",
            "INDEX": "SOFR",
            "FXSPOT": 897.19,
            "CURRENCY": "CLP",
            "TYPE": "XCCY",
            "RATETICKER": ".BASIS5Y INDEX",
            "FXSPOTTICKER": "CLP CURNCY"        
		})"_json;

    Schema<QuantExt::CrossCcyFixFloatSwapHelper> schema;
    EXPECT_NO_THROW(schema.makeObj(testSchema, f, g, h));
}

TEST(MakeObject, FxSwapRateHelper) {
    json testSchema = R"({
            "FXPOINTS": 17.53,
            "FXSPOT": 897.19,
            "TENOR": "3M",
            "CALENDAR": "NULLCALENDAR",
            "FIXINGDAYS": 0.0,
            "ENDOFMONTH": false,
            "BASECURRENCYCOLLATERAL": true,
            "CONVENTION": "FOLLOWING",
            "COLLATERALCURVE": "SOFR",
            "TYPE": "FXSWAP",
            "FXPOINTSTICKER": "CHN3M ICCH CURNCY",
            "FXSPOTTICKER": "CLP CURNCY"          
		})"_json;

    Schema<QuantLib::FxSwapRateHelper> schema;
    EXPECT_NO_THROW(schema.makeObj(testSchema, f, h));
}

TEST(MakeObject, OISRateHelper) {
    json testSchema = R"({
            "RATE": 0.024620000000000003,
            "TENOR": "30Y",
            "DAYCOUNTER": "ACT360",
            "CALENDAR": "USA",
            "CONVENTION": "FOLLOWING",
            "ENDOFMONTH": true,
            "FREQUENCY": "ANNUAL",
            "SETTLEMENTDAYS": 2.0,
            "PAYMENTLAG": 2.0,
            "TELESCOPICVALUEDATES": true,
            "INDEX": "SOFR",
            "TYPE": "OIS",
            "RATETICKER": "USOSFR40 CURNCY"
        })"_json;

    Schema<QuantLib::OISRateHelper> schema;
    EXPECT_NO_THROW(schema.makeObj(testSchema, f, sofrIndex, h));
}

TEST(MakeObject, SwapRateHelper) {
    json testSchema = R"({
            "RATE": 0.02742,
            "TENOR": "40Y",
            "DAYCOUNTER": "THIRTY360",
            "CALENDAR": "USA",
            "CONVENTION": "MODIFIEDFOLLOWING",
            "FREQUENCY": "SEMIANNUAL",
            "SETTLEMENTDAYS": 2.0,
            "DISCOUNTINGCURVE": "SOFR",
            "INDEX": "LIBOR3M",
            "TYPE": "SWAP",
            "RATETICKER": "USSWAP40 BGN CURNCY"               
		})"_json;

    Schema<QuantLib::OISRateHelper> schema;
    EXPECT_NO_THROW(schema.makeObj(testSchema, f, sofrIndex, h));
}

TEST(MakeObject, TenorBasisSwapHelper) {
    json testSchema = R"({
            "SPREAD": 0.0014,
            "TENOR": "20Y",
            "LONGINDEX": "LIBOR1M",
            "SHORTINDEX": "LIBOR3M",
            "DISCOUNTINGCURVE": "LIBOR1M",
            "SPREADONSHORT": true,
            "TYPE": "TENORBASIS",
            "SPREADTICKER": "USBA20 BGN CURNCY"
        })"_json;

    Schema<QuantExt::TenorBasisSwapHelper> schema;
    EXPECT_NO_THROW(schema.makeObj(testSchema, f, g, h));
}

TEST(MakeObject, CrossCcyBasisSwapHelper) {
    json testSchema = R"({
                    "SPREAD": 0.019,
                    "TENOR": "15Y",
                    "CALENDAR": "NULLCALENDAR",
                    "DAYCOUNTER": "ACT360",
                    "CONVENTION": "UNADJUSTED",
                    "ENDOFMONTH": true,
                    "SETTLEMENTDAYS": 1,
                    "FXSPOT": 800,
                    "FXSPOTTICKER": "CLP CURNCY",
                    "FLATISDOMESTIC": true,
                    "FLATDISCOUNTINGCURVE": "LIBOR1M",
                    "FLATINDEX": "LIBOR1M",
                    "SPREADINDEX": "LIBOR3M",
                    "SPREADTICKER": "LIB6M_MAS_15Y",
                    "COUPONDAYCOUNTER": "THIRTY360",
                    "TYPE": "XCCYBASIS",
                    "RATETICKER": "USD_BOND_15Y"
    })"_json;

    Schema<QuantExt::CrossCcyBasisSwapHelper> schema;
    EXPECT_NO_THROW(schema.makeObj(testSchema, f, g, h));
}

TEST(MakeObject, IborIndex) {
    json data = R"({
            "NAME": "LIBOR1M",
            "TENOR": "1M",
            "DAYCOUNTER": "ACT360",
            "CURRENCY": "USD",
            "SETTLEMENTDAYS": 0.0,
            "CALENDAR": "USA"
        })"_json;

    Schema<QuantLib::IborIndex> schema;
    EXPECT_NO_THROW(schema.makeObj(data, h));
}

TEST(MakeObject, OvernightIndex) {
    json data = R"({
            "NAME": "LIBOR1M",
            "DAYCOUNTER": "ACT360",
            "CURRENCY": "USD",
            "CALENDAR": "USA"
        })"_json;

    Schema<QuantLib::OvernightIndex> schema;
    EXPECT_NO_THROW(schema.makeObj(data, h));
}

TEST(MakeObject, InterestRate) {
    json data = R"({
            "VALUE": 0.01,
            "DAYCOUNTER": "ACT360",
            "COMPOUDING": "COMPUNDED",
            "FREQUENCY": "ANNUAL"
        })"_json;

    Schema<QuantLib::InterestRate> schema;
    EXPECT_NO_THROW(schema.makeObj(data, h));
}
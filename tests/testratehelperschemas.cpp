#include "pch.hpp"
#include <qlp/schemas/ratehelpers/all.hpp>
#include <nlohmann/json-schema.hpp>

using nlohmann::json_schema::json_validator;
using json = nlohmann::json;
using namespace QuantLib;
using namespace QuantExt;
using namespace QuantLibParser;

TEST(RateHelperSchemas, DepositSchema) {
    json testSchema = R"({
            "TYPE": "DEPOSIT",
			"RATE": 0.033518703852712,
            "RATETICKER": "DAP_1D",
            "TENOR": "1D"            
		})"_json;

    Schema<DepositRateHelper> depositSchema;
    EXPECT_NO_THROW(depositSchema.validate(testSchema));

    testSchema = R"(  {
            "RATE": 0.0227,
            "DAYCOUNTER": "ACT360",
            "TENOR": "1D",
            "CALENDAR": "USA",
            "FIXINGDAYS": 0.0,
            "ENDOFMONTH": true,
            "CONVENTION": "MODIFIEDFOLLOWING",
            "TYPE": "DEPOSIT",
            "RATETICKER": "SOFRRATE CURNCY"
          })";

    EXPECT_NO_THROW(depositSchema.validate(testSchema));
}

TEST(RateHelperSchemas, BondSchema) {
    json testSchema = R"({
            "TYPE": "BOND",
			"RATE": 0.033518703852712,
            "RATETICKER": "BOND_1D",
            "TENOR": "5M"            
		})"_json;

    Schema<FixedRateBondHelper> bondSchema;
    EXPECT_NO_THROW(bondSchema.validate(testSchema));
}

TEST(RateHelperSchemas, FXSwapSchema) {
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

    Schema<FxSwapRateHelper> fxSwapSchema;
    EXPECT_NO_THROW(fxSwapSchema.validate(testSchema));
}

TEST(RateHelperSchemas, XccySchema) {
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

    Schema<CrossCcyFixFloatSwapHelper> xccySchema;
    EXPECT_NO_THROW(xccySchema.validate(testSchema));
}

TEST(RateHelperSchemas, SwapSchema) {
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

    Schema<SwapRateHelper> swapSchema;
    EXPECT_NO_THROW(swapSchema.validate(testSchema));
}

TEST(RateHelperSchemas, OISSchema) {
    json testSchema = R"({
            "RATE": 0.024620000000000003,
            "TENOR": "40Y",
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

    Schema<OISRateHelper> swapSchema;
    EXPECT_NO_THROW(swapSchema.validate(testSchema));
}

TEST(RateHelperSchemas, TenorBasischema) {
    json testSchema = R"({
            "SPREAD": 0.0014,
            "TENOR": "20Y",
            "LONGINDEX": "LIBOR3M",
            "SHORTINDEX": "LIBOR1M",
            "DISCOUNTINGCURVE": "SOFR",
            "SPREADONSHORT": true,
            "TYPE": "TENORBASIS",
            "SPREADTICKER": "USBA20 BGN CURNCY"
        })"_json;

    Schema<TenorBasisSwapHelper> swapSchema;
    EXPECT_NO_THROW(swapSchema.validate(testSchema));
}

TEST(RateHelperSchemas, XccyBasischema) {
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
                    "FLATDISCOUNTINGCURVE": "ICP_ICAP",
                    "FLATINDEX": "ICP_ICAP",
                    "SPREADINDEX": "LIBOR6M",
                    "SPREADTICKER": "LIB6M_MAS_15Y",
                    "COUPONDAYCOUNTER": "THIRTY360",
                    "TYPE": "XCCYBASIS",
                    "RATETICKER": "USD_BOND_15Y"
    })"_json;

    Schema<CrossCcyBasisSwapHelper> swapSchema;
    try {
        swapSchema.validate(testSchema);
    } catch (const std::exception& e) { std::cout << e.what() << "\n"; }
    EXPECT_NO_THROW(swapSchema.validate(testSchema));
}
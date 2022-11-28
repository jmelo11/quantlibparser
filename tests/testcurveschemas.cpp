#include "pch.hpp"
#include <qlp/schemas/termstructures/bootstrapcurveschema.hpp>
#include <qlp/schemas/termstructures/discountcurveschema.hpp>
#include <qlp/schemas/termstructures/flatforwardcurveschema.hpp>
#include <qlp/schemas/termstructures/rateindexschema.hpp>
#include <qlp/schemas/termstructures/yieldtermstructureschema.hpp>

using namespace QuantLib;
using namespace QuantLibParser;

TEST(CurveSchemas, DiscountCurve) {
    json data = R"({   
        "TYPE": "DISCOUNT",    
		"NAME": "DISCOUNTCURVE",
		"DAYCOUNTER": "ACT360",
		"ENABLEEXTRAPOLATION": true,
		"NODES": [
			{
				"DATE": "01012019",
				"VALUE": 0.99
			},
			{
				"DATE": "01022019",
				"VALUE": 0.98
			}
		]
	})"_json;

    Schema<DiscountCurve> curveSchema;

    EXPECT_NO_THROW(curveSchema.validate(data));

    data = R"({
		"DAYCOUNTER": "ACT360",
		"ENABLEEXTRAPOLATION": true,
		"NODES": [
			{
				"DATE": "01012019",
				"VALUE": 0.99
			},
			{
				"DATE": "01022019"			
			}
		]
	})"_json;

    EXPECT_ANY_THROW(curveSchema.validate(data));
}

TEST(CurveSchemas, FlatForwardCurve) {
    json data = R"({   
        "NAME":"FLATFORWARDCURVE",
        "REFDATE": "01012019",
        "TYPE": "FLATFORWARD",    
		"DAYCOUNTER": "ACT360",
		"ENABLEEXTRAPOLATION": true,
		"RATE":0.03
	})"_json;
    Schema<FlatForward> curveSchema;
    EXPECT_NO_THROW(curveSchema.validate(data));
}

TEST(CurveSchemas, BootstrapCurve) {
    json data = R"({
            "TYPE": "PIECEWISE",
            "NAME": "CF_USD",
            "DAYCOUNTER": "ACT360",
            "ENABLEEXTRAPOLATION": true,
            "RATEHELPERS": [
                {
                    "RATE": 0.033518703852712,
                    "DAYCOUNTER": "ACT360",
                    "TENOR": "1D",
                    "CALENDAR": "CHILE",
                    "ENDOFMONTH": true,
                    "CONVENTION": "MODIFIEDFOLLOWING",
                    "TYPE": "DEPOSIT",
                    "RATETICKER": "DAP_1D"
                },
                {
                    "RATE": 0.033518703852712,
                    "DAYCOUNTER": "ACT360",
                    "TENOR": "7D",
                    "CALENDAR": "CHILE",
                    "ENDOFMONTH": true,
                    "CONVENTION": "MODIFIEDFOLLOWING",
                    "TYPE": "DEPOSIT",
                    "RATETICKER": "DAP_7D"
                },
                {
                    "RATE": 3.39014632405213E-02,
                    "DAYCOUNTER": "ACT360",
                    "TENOR": "15D",
                    "CALENDAR": "CHILE",
                    "ENDOFMONTH": true,
                    "CONVENTION": "MODIFIEDFOLLOWING",
                    "TYPE": "DEPOSIT",
                    "RATETICKER": "DAP_15D"
                },
                {
                    "RATE": 3.64524955411621E-02,
                    "DAYCOUNTER": "ACT360",
                    "TENOR": "1M",
                    "CALENDAR": "CHILE",
                    "ENDOFMONTH": true,
                    "CONVENTION": "MODIFIEDFOLLOWING",
                    "TYPE": "DEPOSIT",
                    "RATETICKER": "DAP_1M"
                },
                {
                    "RATE": 3.73672794191295E-02,
                    "DAYCOUNTER": "ACT360",
                    "TENOR": "2M",
                    "CALENDAR": "CHILE",
                    "ENDOFMONTH": true,
                    "CONVENTION": "MODIFIEDFOLLOWING",
                    "TYPE": "DEPOSIT",
                    "RATETICKER": "DAP_2M"
                },
                {
                    "RATE": 3.98263273445547E-02,
                    "DAYCOUNTER": "ACT360",
                    "TENOR": "3M",
                    "CALENDAR": "CHILE",
                    "ENDOFMONTH": true,
                    "CONVENTION": "MODIFIEDFOLLOWING",
                    "TYPE": "DEPOSIT",
                    "RATETICKER": "DAP_3M"
                },
                {
                    "RATE": 4.13754869391674E-02,
                    "DAYCOUNTER": "ACT360",
                    "TENOR": "4M",
                    "CALENDAR": "CHILE",
                    "ENDOFMONTH": true,
                    "CONVENTION": "MODIFIEDFOLLOWING",
                    "TYPE": "DEPOSIT",
                    "RATETICKER": "DAP_4M"
                },
                {
                    "RATE": 0.04327377836537,
                    "DAYCOUNTER": "ACT360",
                    "TENOR": "5M",
                    "CALENDAR": "CHILE",
                    "ENDOFMONTH": true,
                    "CONVENTION": "MODIFIEDFOLLOWING",
                    "TYPE": "DEPOSIT",
                    "RATETICKER": "DAP_5M"
                },
                {
                    "RATE": 4.39939531829608E-02,
                    "DAYCOUNTER": "ACT360",
                    "TENOR": "6M",
                    "CALENDAR": "CHILE",
                    "ENDOFMONTH": true,
                    "CONVENTION": "MODIFIEDFOLLOWING",
                    "TYPE": "DEPOSIT",
                    "RATETICKER": "DAP_6M"
                },
                {
                    "RATE": 5.30373048296681E-02,
                    "DAYCOUNTER": "ACT360",
                    "TENOR": "12M",
                    "CALENDAR": "CHILE",
                    "ENDOFMONTH": true,
                    "CONVENTION": "MODIFIEDFOLLOWING",
                    "TYPE": "DEPOSIT",
                    "RATETICKER": "DAP_12M"
                },
                {
                    "SPREAD": 0.013,
                    "TENOR": "2Y",
                    "CALENDAR": "NULLCALENDAR",
                    "DAYCOUNTER": "ACT360",
                    "CONVENTION": "UNADJUSTED",
                    "ENDOFMONTH": true,
                    "SETTLEMENTDAYS": 1,
                    "FXSPOT": "CLP CURNCY",
                    "FXSPOTTICKER": "CLP CURNCY",
                    "FLATISDOMESTIC": true,
                    "FLATDISCOUNTINGCURVE": "ICP_ICAP",
                    "FLATINDEX": "ICP_ICAP",
                    "SPREADINDEX": "LIBOR6M",
                    "SPREADTICKER": "LIB6M_MAS_2Y",
                    "COUPONDAYCOUNTER": "THIRTY360",
                    "TYPE": "XCCYBASIS",
                    "RATETICKER": "USD_BOND_2Y"
                },
                {
                    "SPREAD": 0.014,
                    "TENOR": "3Y",
                    "CALENDAR": "NULLCALENDAR",
                    "DAYCOUNTER": "ACT360",
                    "CONVENTION": "UNADJUSTED",
                    "ENDOFMONTH": true,
                    "SETTLEMENTDAYS": 1,
                    "FXSPOT": "CLP CURNCY",
                    "FXSPOTTICKER": "CLP CURNCY",
                    "FLATISDOMESTIC": true,
                    "FLATDISCOUNTINGCURVE": "ICP_ICAP",
                    "FLATINDEX": "ICP_ICAP",
                    "SPREADINDEX": "LIBOR6M",
                    "SPREADTICKER": "LIB6M_MAS_3Y",
                    "COUPONDAYCOUNTER": "THIRTY360",
                    "TYPE": "XCCYBASIS",
                    "RATETICKER": "USD_BOND_3Y"
                },
                {
                    "SPREAD": 0.015,
                    "TENOR": "4Y",
                    "CALENDAR": "NULLCALENDAR",
                    "DAYCOUNTER": "ACT360",
                    "CONVENTION": "UNADJUSTED",
                    "ENDOFMONTH": true,
                    "SETTLEMENTDAYS": 1,
                    "FXSPOT": "CLP CURNCY",
                    "FXSPOTTICKER": "CLP CURNCY",
                    "FLATISDOMESTIC": true,
                    "FLATDISCOUNTINGCURVE": "ICP_ICAP",
                    "FLATINDEX": "ICP_ICAP",
                    "SPREADINDEX": "LIBOR6M",
                    "SPREADTICKER": "LIB6M_MAS_4Y",
                    "COUPONDAYCOUNTER": "THIRTY360",
                    "TYPE": "XCCYBASIS",
                    "RATETICKER": "USD_BOND_4Y"
                },
                {
                    "SPREAD": 0.015,
                    "TENOR": "5Y",
                    "CALENDAR": "NULLCALENDAR",
                    "DAYCOUNTER": "ACT360",
                    "CONVENTION": "UNADJUSTED",
                    "ENDOFMONTH": true,
                    "SETTLEMENTDAYS": 1,
                    "FXSPOT": "CLP CURNCY",
                    "FXSPOTTICKER": "CLP CURNCY",
                    "FLATISDOMESTIC": true,
                    "FLATDISCOUNTINGCURVE": "ICP_ICAP",
                    "FLATINDEX": "ICP_ICAP",
                    "SPREADINDEX": "LIBOR6M",
                    "SPREADTICKER": "LIB6M_MAS_5Y",
                    "COUPONDAYCOUNTER": "THIRTY360",
                    "TYPE": "XCCYBASIS",
                    "RATETICKER": "USD_BOND_5Y"
                },
                {
                    "SPREAD": 0.015,
                    "TENOR": "7Y",
                    "CALENDAR": "NULLCALENDAR",
                    "DAYCOUNTER": "ACT360",
                    "CONVENTION": "UNADJUSTED",
                    "ENDOFMONTH": true,
                    "SETTLEMENTDAYS": 1,
                    "FXSPOT": "CLP CURNCY",
                    "FXSPOTTICKER": "CLP CURNCY",
                    "FLATISDOMESTIC": true,
                    "FLATDISCOUNTINGCURVE": "ICP_ICAP",
                    "FLATINDEX": "ICP_ICAP",
                    "SPREADINDEX": "LIBOR6M",
                    "SPREADTICKER": "LIB6M_MAS_7Y",
                    "COUPONDAYCOUNTER": "THIRTY360",
                    "TYPE": "XCCYBASIS",
                    "RATETICKER": "USD_BOND_7Y"
                },
                {
                    "SPREAD": 0.016,
                    "TENOR": "10Y",
                    "CALENDAR": "NULLCALENDAR",
                    "DAYCOUNTER": "ACT360",
                    "CONVENTION": "UNADJUSTED",
                    "ENDOFMONTH": true,
                    "SETTLEMENTDAYS": 1,
                    "FXSPOT": "CLP CURNCY",
                    "FXSPOTTICKER": "CLP CURNCY",
                    "FLATISDOMESTIC": true,
                    "FLATDISCOUNTINGCURVE": "ICP_ICAP",
                    "FLATINDEX": "ICP_ICAP",
                    "SPREADINDEX": "LIBOR6M",
                    "SPREADTICKER": "LIB6M_MAS_10Y",
                    "COUPONDAYCOUNTER": "THIRTY360",
                    "TYPE": "XCCYBASIS",
                    "RATETICKER": "USD_BOND_10Y"
                },
                {
                    "SPREAD": 0.019,
                    "TENOR": "15Y",
                    "CALENDAR": "NULLCALENDAR",
                    "DAYCOUNTER": "ACT360",
                    "CONVENTION": "UNADJUSTED",
                    "ENDOFMONTH": true,
                    "SETTLEMENTDAYS": 1,
                    "FXSPOT": "CLP CURNCY",
                    "FXSPOTTICKER": "CLP CURNCY",
                    "FLATISDOMESTIC": true,
                    "FLATDISCOUNTINGCURVE": "ICP_ICAP",
                    "FLATINDEX": "ICP_ICAP",
                    "SPREADINDEX": "LIBOR6M",
                    "SPREADTICKER": "LIB6M_MAS_15Y",
                    "COUPONDAYCOUNTER": "THIRTY360",
                    "TYPE": "XCCYBASIS",
                    "RATETICKER": "USD_BOND_15Y"
                },
                {
                    "SPREAD": 0.023,
                    "TENOR": "20Y",
                    "CALENDAR": "NULLCALENDAR",
                    "DAYCOUNTER": "ACT360",
                    "CONVENTION": "UNADJUSTED",
                    "ENDOFMONTH": true,
                    "SETTLEMENTDAYS": 1,
                    "FXSPOT": "CLP CURNCY",
                    "FXSPOTTICKER": "CLP CURNCY",
                    "FLATISDOMESTIC": true,
                    "FLATDISCOUNTINGCURVE": "ICP_ICAP",
                    "FLATINDEX": "ICP_ICAP",
                    "SPREADINDEX": "LIBOR6M",
                    "SPREADTICKER": "LIB6M_MAS_20Y",
                    "COUPONDAYCOUNTER": "THIRTY360",
                    "TYPE": "XCCYBASIS",
                    "RATETICKER": "USD_BOND_20Y"
                }
            ]
        })"_json;

    Schema<PiecewiseYieldCurve<Discount, LogLinear>> curveSchema;
    try {
        curveSchema.validate(data);
    } catch (const std::exception& e) { std::cout << e.what() << "\n"; }

    EXPECT_NO_THROW(curveSchema.validate(data));

    data = R"(
        {
            "NAME": "SOFR",
            "DAYCOUNTER": "ACT360",
            "ENABLEEXTRAPOLATION": true,
            "RATEHELPERS": [
                {
                    "RATE": 0.0227,
                    "DAYCOUNTER": "ACT360",
                    "TENOR": "1D",
                    "CALENDAR": "USA",
                    "FIXINGDAYS": 0.0,
                    "ENDOFMONTH": true,
                    "CONVENTION": "MODIFIEDFOLLOWING",
                    "TYPE": "DEPOSIT",
                    "RATETICKER": "SOFRRATE CURNCY"
                },
                {
                    "RATE": 0.022930000000000002,
                    "TENOR": "1W",
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
                    "RATETICKER": "USOSFR1Z CURNCY"
                },
                {
                    "RATE": 0.022886000000000004,
                    "TENOR": "2W",
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
                    "RATETICKER": "USOSFR2Z CURNCY"
                },
                {
                    "RATE": 0.022895,
                    "TENOR": "3W",
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
                    "RATETICKER": "USOSFR3Z CURNCY"
                },
                {
                    "RATE": 0.024350999999999998,
                    "TENOR": "1M",
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
                    "RATETICKER": "USOSFRA CURNCY"
                },
                {
                    "RATE": 0.02697,
                    "TENOR": "2M",
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
                    "RATETICKER": "USOSFRB CURNCY"
                },
                {
                    "RATE": 0.028994,
                    "TENOR": "3M",
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
                    "RATETICKER": "USOSFRC CURNCY"
                },
                {
                    "RATE": 0.030594,
                    "TENOR": "4M",
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
                    "RATETICKER": "USOSFRD CURNCY"
                },
                {
                    "RATE": 0.03167,
                    "TENOR": "5M",
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
                    "RATETICKER": "USOSFRE CURNCY"
                },
                {
                    "RATE": 0.03261,
                    "TENOR": "6M",
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
                    "RATETICKER": "USOSFRF CURNCY"
                },
                {
                    "RATE": 0.03323,
                    "TENOR": "7M",
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
                    "RATETICKER": "USOSFRG CURNCY"
                },
                {
                    "RATE": 0.033854999999999996,
                    "TENOR": "8M",
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
                    "RATETICKER": "USOSFRH CURNCY"
                },
                {
                    "RATE": 0.034390000000000004,
                    "TENOR": "9M",
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
                    "RATETICKER": "USOSFRI CURNCY"
                },
                {
                    "RATE": 0.034755,
                    "TENOR": "10M",
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
                    "RATETICKER": "USOSFRJ CURNCY"
                },
                {
                    "RATE": 0.035055,
                    "TENOR": "11M",
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
                    "RATETICKER": "USOSFRK CURNCY"
                },
                {
                    "RATE": 0.035293,
                    "TENOR": "12M",
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
                    "RATETICKER": "USOSFR1 CURNCY"
                },
                {
                    "RATE": 0.03508,
                    "TENOR": "18M",
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
                    "RATETICKER": "USOSFR1F CURNCY"
                },
                {
                    "RATE": 0.034296,
                    "TENOR": "2Y",
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
                    "RATETICKER": "USOSFR2 CURNCY"
                }
            ]
        }
    )"_json;

    EXPECT_ANY_THROW(curveSchema.validate(data));
}

TEST(CurveSchemas, IndexTest) {
    json data = R"({
            "NAME": "SOFR",
            "TYPE": "OVERNIGHT",
            "TENOR": "1D",
            "DAYCOUNTER": "ACT360",
            "CURRENCY": "USD",
            "FIXINGDAYS": 0.0,
            "CALENDAR": "USA"
        })"_json;

    Schema<InterestRateIndex> indexSchema;

    EXPECT_NO_THROW(indexSchema.validate(data));
}

TEST(CurveSchemas, IborIndex) {
    json data = R"({
            "NAME": "LIBOR1M",
            "TENOR": "1M",
            "DAYCOUNTER": "ACT360",
            "CURRENCY": "USD",
            "SETTLEMENTDAYS": 0.0,
            "CALENDAR": "USA"
        })"_json;

    Schema<IborIndex> indexSchema;
    EXPECT_NO_THROW(indexSchema.validate(data));
}

TEST(CurveSchemas, OvernightIndex) {}
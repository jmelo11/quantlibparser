#include "pch.h"
#include <schemas/termstructures/discountcurveschema.hpp>
#include <schemas/termstructures/bootstrapcurveschema.hpp>

using namespace QuantLib;
using namespace QuantLibParser;

TEST(DiscountCurve, CurveSchemas) {
	json data = R"({       
		"NAME": "USD",
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
		"NAME": "USD",
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
TEST(BootstrapCurve, CurveSchemas) {
	json data = R"({
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
	
    
    Schema<PiecewiseYieldCurve<LogLinear, Discount>> curveSchema;
    try
    {
        curveSchema.validate(data);
    }
    catch (const std::exception&e)
    {
        std::cout << e.what() << "\n";
    }
	
    EXPECT_NO_THROW(curveSchema.validate(data));
}
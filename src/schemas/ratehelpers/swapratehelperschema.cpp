#include <qlp/schemas/ratehelpers/swapratehelperschema.hpp>

namespace QuantLibParser
{
    template <>
    void Schema<QuantLib::SwapRateHelper>::initSchema()
    {
        json base = R"({
            "title": "Swap Rate Helper Schema",
            "properties": {},
            "required": ["TYPE", "RATE", "RATETICKER", "TENOR", "INDEX"]
        })"_json;

        base["properties"]["DAYCOUNTER"] = dayCounterSchema;
        base["properties"]["CALENDAR"] = calendarSchema;
        base["properties"]["CONVENTION"] = conventionSchema;
        base["properties"]["ENDOFMONTH"] = eomSchema;
        base["properties"]["FREQUENCY"] = frequencySchema;
        base["properties"]["SPREAD"] = priceSchema;
        base["properties"]["SETTLEMENTDAYS"] = fixingDaysSchema;
        base["properties"]["FWDSTART"] = tenorSchema;
        base["properties"]["DISCOUNTINGCURVE"] = curveNameSchema;
		
        base["properties"]["RATE"] = priceSchema;
        base["properties"]["RATETICKER"] = tickerSchema;
        base["properties"]["INDEX"] = curveNameSchema;
        base["properties"]["TYPE"] = rateHelperTypeSchema;
        base["properties"]["TENOR"] = tenorSchema;
        mySchema_ = base;
    }

    template <>
    void Schema<QuantLib::SwapRateHelper>::initDefaultValues()
    {
        myDefaultValues_["DAYCOUNTER"] = "ACT360";
        myDefaultValues_["CALENDAR"] = "NULLCALENDAR";
        myDefaultValues_["CONVENTION"] = "UNADJUSTED";
        myDefaultValues_["ENDOFMONTH"] = false;
        myDefaultValues_["SPREAD"] = 0.0;
        myDefaultValues_["SETTLEMENTDAYS"] = 0;
        myDefaultValues_["FWDSTART"] = "0D";		
    }

	template class Schema<QuantLib::SwapRateHelper>;

}
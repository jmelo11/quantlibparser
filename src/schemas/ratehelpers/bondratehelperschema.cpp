#pragma once
#include <schemas/ratehelpers/bondratehelperschema.hpp>

namespace QuantLibParser
{
    template <>
    void Schema<QuantLib::FixedRateBondHelper>::initSchema()
    {
        json base = R"({
            "title": "Bond Rate Helper Schema",
            "properties": {},
            "required": ["RATE", "RATETICKER", "TENOR", "TYPE"]
        })"_json;

        base["properties"]["RATETICKER"] = tickerSchema;
        base["properties"]["TENOR"] = tenorSchema;
        base["properties"]["TYPE"] = typeSchema;

        base["properties"]["CALENDAR"] = calendarSchema;
        base["properties"]["COMPOUNDING"] = compoundingSchema;
        base["properties"]["FREQUENCY"] = frequencySchema;
        base["properties"]["SETTLEMENTDAYS"] = fixingDaysSchema;
        base["properties"]["ENDOFMONTH"] = eomSchema;
        base["properties"]["FACEAMOUNT"] = faceAmountSchema;
        base["properties"]["COUPON"] = priceSchema;

        base["properties"]["IRRDAYCOUNTER"] = priceSchema;
        base["properties"]["COUPONDAYCOUNTER"] = dayCounterSchema;

        mySchema_ = base;
    };

    template <>
    void Schema< QuantLib::FixedRateBondHelper>::initDefaultValues()
    {
        myDefaultValues_["CALENDAR"] = "NULLCALENDAR";
        myDefaultValues_["FIXINGDAYS"] = 0;
        myDefaultValues_["SETTLEMENTDAYS"] = 0;
        myDefaultValues_["ENDOFMONTH"] = false;
        myDefaultValues_["FACEAMOUNT"] = 100.0;
        myDefaultValues_["COUPON"] = 0.03;
        myDefaultValues_["IRRDAYCOUNTER"] = "ACT365";
        myDefaultValues_["COUPONDAYCOUNTER"] = "THIRTY360";
        myDefaultValues_["FREQUENCY"] = "SEMIANNUAL";
        myDefaultValues_["CONVENTION"] = "UNADJUSTED";
    };
}

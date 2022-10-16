#pragma once
#include <schemas/ratehelpers/depositratehelperschema.hpp>

namespace QuantLibParser
{
    template <>
    void Schema<QuantLib::DepositRateHelper>::initSchema()
    {
        json base = R"({
            "title": "Deposit Rate Helper Schema",
            "properties": {},
            "required": ["TYPE", "RATE", "RATETICKER", "TENOR"]
        })"_json;

        base["properties"]["RATETICKER"] = tickerSchema;
        base["properties"]["TENOR"] = tenorSchema;
        base["properties"]["TYPE"] = rateHelperTypeSchema;
        base["properties"]["DAYCOUNTER"] = dayCounterSchema;
        base["properties"]["ENDOFMONTH"] = eomSchema;
        base["properties"]["CONVENTION"] = conventionSchema;
        base["properties"]["CALENDAR"] = calendarSchema;
        base["properties"]["FIXINGDATS"] = fixingDaysSchema;

        mySchema_ = base;
    }

    template <>
    void Schema<QuantLib::DepositRateHelper>::initDefaultValues()
    {
        myDefaultValues_["CALENDAR"] = "NULLCALENDAR";
        myDefaultValues_["FIXINGDAYS"] = 0;
        myDefaultValues_["ENDOFMONTH"] = false;
        myDefaultValues_["DAYCOUNTER"] = "ACT360";
        myDefaultValues_["CONVENTION"] = "UNADJUSTED";
    }

}

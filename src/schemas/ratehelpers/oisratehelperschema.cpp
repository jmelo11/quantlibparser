#include <qlp/schemas/ratehelpers/oisratehelperschema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::OISRateHelper>::initSchema() {
        json base = R"({
            "title": "OIS Rate Helper Schema",
            "properties": {},
            "required": ["TYPE", "RATE", "RATETICKER", "TENOR", "INDEX"]
        })"_json;

        base["properties"]["DAYCOUNTER"]           = dayCounterSchema;
        base["properties"]["CALENDAR"]             = calendarSchema;
        base["properties"]["CONVENTION"]           = conventionSchema;
        base["properties"]["ENDOFMONTH"]           = eomSchema;
        base["properties"]["FREQUENCY"]            = frequencySchema;
        base["properties"]["SPREAD"]               = priceSchema;
        base["properties"]["SETTLEMENTDAYS"]       = fixingDaysSchema;
        base["properties"]["FWDSTART"]             = tenorSchema;
        base["properties"]["PAYMENTLAG"]           = fixingDaysSchema;
        base["properties"]["TELESCOPICVALUEDATES"] = eomSchema;
        base["properties"]["DISCOUNTINGCURVE"]     = curveNameSchema;

        base["properties"]["RATE"]       = priceSchema;
        base["properties"]["RATETICKER"] = tickerSchema;
        base["properties"]["INDEX"]      = curveNameSchema;
        base["properties"]["TYPE"]       = rateHelperTypeSchema;
        base["properties"]["TENOR"]      = tenorSchema;

        mySchema_ = base;
    }

    template <>
    void Schema<QuantLib::OISRateHelper>::initDefaultValues() {
        myDefaultValues_["DAYCOUNTER"]           = "ACT360";
        myDefaultValues_["CALENDAR"]             = "NULLCALENDAR";
        myDefaultValues_["CONVENTION"]           = "UNADJUSTED";
        myDefaultValues_["ENDOFMONTH"]           = false;
        myDefaultValues_["SPREAD"]               = 0.0;
        myDefaultValues_["SETTLEMENTDAYS"]       = 0;
        myDefaultValues_["FWDSTART"]             = "0D";
        myDefaultValues_["TELESCOPICVALUEDATES"] = true;
        myDefaultValues_["PAYMENTLAG"]           = 0;
    }

    template class Schema<QuantLib::OISRateHelper>;
}  // namespace QuantLibParser
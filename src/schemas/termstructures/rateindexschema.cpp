
#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/termstructures/rateindexschema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::InterestRateIndex>::initSchema() {
        json base = R"({
            "title": "Index Schema",
            "properties": {},			
            "required": ["TYPE","NAME","TENOR","DAYCOUNTER","CURRENCY","CALENDAR"]
        })"_json;

        base["properties"]["TYPE"]       = indexTypesSchema;
        base["properties"]["NAME"]       = curveNameSchema;
        base["properties"]["TENOR"]      = tenorSchema;
        base["properties"]["DAYCOUNTER"] = dayCounterSchema;
        base["properties"]["CURRENCY"]   = currencySchema;
        base["properties"]["CALENDAR"]   = calendarSchema;

        mySchema_ = base;
    }

    template <>
    void Schema<QuantLib::InterestRateIndex>::initDefaultValues() {
        myDefaultValues_["DAYCOUNTER"] = "ACT360";
    }

    template class Schema<QuantLib::InterestRateIndex>;
}  // namespace QuantLibParser
#include <qlp/parser.hpp>
#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/termstructures/overnightindexschema.hpp>

namespace QuantLibParser {

    template <>
    void Schema<QuantLib::OvernightIndex>::initSchema() {
        json base = R"({
            "title": "Overnight Index Schema",
            "properties": {},			
            "required": ["NAME","DAYCOUNTER","CURRENCY","CALENDAR"]
        })"_json;

        base["properties"]["NAME"]           = curveNameSchema;
        base["properties"]["SETTLEMENTDAYS"] = fixingDaysSchema;
        base["properties"]["DAYCOUNTER"]     = dayCounterSchema;
        base["properties"]["CURRENCY"]       = currencySchema;
        base["properties"]["CALENDAR"]       = calendarSchema;

        mySchema_ = base;
    };

    template <>
    void Schema<QuantLib::OvernightIndex>::initDefaultValues() {
        myDefaultValues_["NAME"]           = "ACT360";
        myDefaultValues_["CALENDAR"]       = "NULLCALENDAR";
        myDefaultValues_["SETTLEMENTDAYS"] = 0;
    };

    template <>
    template <>
    QuantLib::OvernightIndex Schema<QuantLib::OvernightIndex>::makeObj(const json& params, CurveGetter& curveGetter) {
        json data = setDefaultValues(params);
        validate(data);

        QuantLib::Currency currency     = parse<QuantLib::Currency>(data.at("CURRENCY"));
        QuantLib::Calendar calendar     = parse<QuantLib::Calendar>(data.at("CALENDAR"));
        QuantLib::DayCounter dayCounter = parse<QuantLib::DayCounter>(data.at("DAYCOUNTER"));
        int settlementDays              = data.at("SETTLEMENTDAYS");

        auto curve = curveGetter(data.at("NAME"));
        return QuantLib::OvernightIndex(data.at("NAME"), settlementDays, currency, calendar, dayCounter, curve);
    };
}  // namespace QuantLibParser
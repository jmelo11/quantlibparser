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
        base["properties"]["CURVE"]          = curveNameSchema;

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
        validate(params);
        json data                       = setDefaultValues(params);
        QuantLib::Currency currency     = parse<QuantLib::Currency>(data.at("CURRENCY"));
        QuantLib::Calendar calendar     = parse<QuantLib::Calendar>(data.at("CALENDAR"));
        QuantLib::DayCounter dayCounter = parse<QuantLib::DayCounter>(data.at("DAYCOUNTER"));
        int settlementDays              = data.at("SETTLEMENTDAYS");

        if (data.find("CURVE") != data.end()) {
            QuantLib::RelinkableHandle<QuantLib::YieldTermStructure> curve = curveGetter(data.at("CURVE"));
            return QuantLib::OvernightIndex(data.at("NAME"), settlementDays, currency, calendar, dayCounter, curve);
        } else {
            return QuantLib::OvernightIndex(data.at("NAME"), settlementDays, currency, calendar, dayCounter);
        }
    };
}  // namespace QuantLibParser
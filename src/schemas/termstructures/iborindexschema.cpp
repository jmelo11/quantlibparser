#include <qlp/parser.hpp>
#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/termstructures/iborindexschema.hpp>

namespace QuantLibParser {

    template <>
    void Schema<QuantLib::IborIndex>::initSchema() {
        json base = R"({
            "title": "Ibor Index Schema",
            "properties": {},			
            "required": ["NAME","TENOR","DAYCOUNTER","CURRENCY","CALENDAR"]
        })"_json;

        base["properties"]["NAME"]           = curveNameSchema;
        base["properties"]["TENOR"]          = tenorSchema;
        base["properties"]["SETTLEMENTDAYS"] = fixingDaysSchema;
        base["properties"]["DAYCOUNTER"]     = dayCounterSchema;
        base["properties"]["CURRENCY"]       = currencySchema;
        base["properties"]["CONVENTION"]     = conventionSchema;
        base["properties"]["ENDOFMONTH"]     = eomSchema;
        base["properties"]["CALENDAR"]       = calendarSchema;
        base["properties"]["CURVE"]          = curveNameSchema;

        mySchema_ = base;
    };

    template <>
    void Schema<QuantLib::IborIndex>::initDefaultValues() {
        myDefaultValues_["NAME"]           = "ACT360";
        myDefaultValues_["CALENDAR"]       = "NULLCALENDAR";
        myDefaultValues_["CONVENTION"]     = "UNADJUSTED";
        myDefaultValues_["SETTLEMENTDAYS"] = 0;
        myDefaultValues_["ENDOFMONTH"]     = false;
    };

    template <>
    template <>
    QuantLib::IborIndex Schema<QuantLib::IborIndex>::makeObj(const json& params, CurveGetter& curveGetter) {
        validate(params);
        json data                                  = setDefaultValues(params);
        QuantLib::Period tenor                     = parse<QuantLib::Period>(data.at("TENOR"));
        QuantLib::Currency currency                = parse<QuantLib::Currency>(data.at("CURRENCY"));
        QuantLib::Calendar calendar                = parse<QuantLib::Calendar>(data.at("CALENDAR"));
        QuantLib::BusinessDayConvention convention = parse<QuantLib::BusinessDayConvention>(data.at("CONVENTION"));
        QuantLib::DayCounter dayCounter            = parse<QuantLib::DayCounter>(data.at("DAYCOUNTER"));
        int settlementDays                         = data.at("SETTLEMENTDAYS");
        bool endOfMonth                            = data.at("ENDOFMONTH");

        if (data.find("CURVE") != data.end()) {
            QuantLib::RelinkableHandle<QuantLib::YieldTermStructure> curve = curveGetter(data.at("CURVE"));
            return QuantLib::IborIndex(data.at("NAME"), tenor, settlementDays, currency, calendar, convention, endOfMonth, dayCounter, curve);
        } else {
            return QuantLib::IborIndex(data.at("NAME"), tenor, settlementDays, currency, calendar, convention, endOfMonth, dayCounter);
        }
    };
}  // namespace QuantLibParser
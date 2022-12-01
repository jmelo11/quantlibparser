#include <qlp/parser.hpp>
#include <qlp/schemas/ratehelpers/depositratehelperschema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::DepositRateHelper>::initSchema() {
        json base = R"({
            "title": "Deposit Rate Helper Schema",
            "properties": {},
            "required": ["TYPE", "RATE", "RATETICKER", "TENOR"]
        })"_json;

        base["properties"]["RATETICKER"] = tickerSchema;
        base["properties"]["TENOR"]      = tenorSchema;
        base["properties"]["TYPE"]       = rateHelperTypeSchema;
        base["properties"]["DAYCOUNTER"] = dayCounterSchema;
        base["properties"]["ENDOFMONTH"] = eomSchema;
        base["properties"]["CONVENTION"] = conventionSchema;
        base["properties"]["CALENDAR"]   = calendarSchema;
        base["properties"]["FIXINGDAYS"] = fixingDaysSchema;

        mySchema_ = base;
    }

    template <>
    void Schema<QuantLib::DepositRateHelper>::initDefaultValues() {
        myDefaultValues_["CALENDAR"]   = "NULLCALENDAR";
        myDefaultValues_["FIXINGDAYS"] = 0;
        myDefaultValues_["ENDOFMONTH"] = false;
        myDefaultValues_["DAYCOUNTER"] = "ACT360";
        myDefaultValues_["CONVENTION"] = "UNADJUSTED";
    }

    template <>
    template <>
    QuantLib::DepositRateHelper Schema<QuantLib::DepositRateHelper>::makeObj(const json& params, PriceGetter& priceGetter) {
        json data = setDefaultValues(params);
        validate(data);

        QuantLib::DayCounter dayCounter = parse<QuantLib::DayCounter>(data.at("DAYCOUNTER"));
        QuantLib::Calendar calendar     = parse<QuantLib::Calendar>(data.at("CALENDAR"));

        double fixingDays                          = data.at("FIXINGDAYS");
        bool endOfMonth                            = data.at("ENDOFMONTH");
        QuantLib::BusinessDayConvention convention = parse<QuantLib::BusinessDayConvention>(data.at("CONVENTION"));

        // non-defaults
        QuantLib::Period tenor = parse<QuantLib::Period>(data.at("TENOR"));

        auto rate = priceGetter(data.at("RATE"), data.at("RATETICKER"));
        return DepositRateHelper(rate, tenor, fixingDays, calendar, convention, endOfMonth, dayCounter);
    }
}  // namespace QuantLibParser

#include <qlp/parser.hpp>
#include <qlp/schemas/termstructures/iborindexschema.hpp>

namespace QuantLibParser {

    template <>
    void Schema<QuantLib::IborIndex>::initSchema() {
        mySchema_ = readJSONFile("rateindex.schema.json");
    };

    template <>
    void Schema<QuantLib::IborIndex>::initDefaultValues() {
        myDefaultValues_["dayCounter"]     = "Act360";
        myDefaultValues_["calendar"]       = "NullCalendar";
        myDefaultValues_["convention"]     = "Unadjusted";
        myDefaultValues_["settlementDays"] = 0;
        myDefaultValues_["endOfMonth"]     = false;
        myDefaultValues_["indexName"]     = "DummyIndex";
    };

    template <>
    template <>
    QuantLib::IborIndex Schema<QuantLib::IborIndex>::makeObj(const json& params, CurveGetter& curveGetter) {
        json data = setDefaultValues(params);
        validate(data);
        QuantLib::Period tenor                     = parse<QuantLib::Period>(data.at("tenor"));
        QuantLib::Currency currency                = parse<QuantLib::Currency>(data.at("currency"));
        QuantLib::Calendar calendar                = parse<QuantLib::Calendar>(data.at("calendar"));
        QuantLib::BusinessDayConvention convention = parse<QuantLib::BusinessDayConvention>(data.at("convention"));
        QuantLib::DayCounter dayCounter            = parse<QuantLib::DayCounter>(data.at("dayCounter"));
        int settlementDays                         = data.at("settlementDays");
        bool endOfMonth                            = data.at("endOfMonth");

        auto curve = curveGetter(data.at("indexName"));
        return QuantLib::IborIndex(data.at("indexName"), tenor, settlementDays, currency, calendar, convention, endOfMonth, dayCounter, curve);
    };
}  // namespace QuantLibParser
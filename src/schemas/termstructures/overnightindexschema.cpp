#include <qlp/parser.hpp>
#include <qlp/schemas/termstructures/overnightindexschema.hpp>

namespace QuantLibParser {

    template <>
    void Schema<QuantLib::OvernightIndex>::initSchema() {
        mySchema_ = readJSONFile("rateindex.schema.json");
    };

    template <>
    void Schema<QuantLib::OvernightIndex>::initDefaultValues() {
        myDefaultValues_["dayCounter"]     = "Act360";
        myDefaultValues_["calendar"]       = "NullCalendar";
        myDefaultValues_["settlementDays"] = 0;
        myDefaultValues_["indexName"]      = "DummyIndex";
    };

    template <>
    template <>
    QuantLib::OvernightIndex Schema<QuantLib::OvernightIndex>::makeObj(const json& params, CurveGetter& curveGetter) {
        json data = setDefaultValues(params);
        validate(data);

        QuantLib::Currency currency     = parse<QuantLib::Currency>(data.at("currency"));
        QuantLib::Calendar calendar     = parse<QuantLib::Calendar>(data.at("calendar"));
        QuantLib::DayCounter dayCounter = parse<QuantLib::DayCounter>(data.at("dayCounter"));
        int settlementDays              = data.at("settlementDays");

        auto curve = curveGetter(data.at("indexName"));
        return QuantLib::OvernightIndex(data.at("indexName"), settlementDays, currency, calendar, dayCounter, curve);
    };
}  // namespace QuantLibParser
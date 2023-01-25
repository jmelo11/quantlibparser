#include <qlp/schemas/termstructures/discountcurveschema.hpp>

namespace QuantLibParser {

    template <>
    void Schema<QuantLib::DiscountCurve>::initSchema() {
        mySchema_ = readJSONFile("discountcurve.schema.json");
    };

    template <>
    void Schema<QuantLib::DiscountCurve>::initDefaultValues() {
        myDefaultValues_["enableExtrapolation"] = true;
        myDefaultValues_["dayCounter"]          = "Act360";
    };

    template <>
    template <>
    QuantLib::DiscountCurve Schema<QuantLib::DiscountCurve>::makeObj(const json& params) {
        json data = setDefaultValues(params);
        validate(data);

        const json& nodes = data.at("nodes");
        std::vector<QuantLib::Date> dates;
        std::vector<double> dfs;
        for (const auto& node : nodes) {
            dates.push_back(parse<QuantLib::Date>(node.at("date")));
            dfs.push_back(node.at("value"));
        }
        QuantLib::DayCounter dayCounter = parse<QuantLib::DayCounter>(data.at("dayCounter"));

        bool enableExtrapolation = data.at("enableExtrapolation");
        QuantLib::DiscountCurve curve(dates, dfs, dayCounter);

        curve.enableExtrapolation(enableExtrapolation);
        curve.unregisterWith(QuantLib::Settings::instance().evaluationDate());
        return curve;
    }

}  // namespace QuantLibParser
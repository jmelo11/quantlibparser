#include <qlp/parser.hpp>
#include <qlp/schemas/termstructures/flatforwardcurveschema.hpp>

namespace QuantLibParser {

    template <>
    void Schema<QuantLib::FlatForward>::initSchema() {
        mySchema_ = readJSONFile("flatforwardcurve.schema.json");
    };

    template <>
    void Schema<QuantLib::FlatForward>::initDefaultValues() {
        myDefaultValues_["refDate"]             = parseDate(QuantLib::Settings::instance().evaluationDate());
        myDefaultValues_["dayCounter"]          = "Act360";
        myDefaultValues_["compounding"]         = "Simple";
        myDefaultValues_["frequency"]           = "Annual";
        myDefaultValues_["enableExtrapolation"] = true;
    };

    template <>
    template <>
    QuantLib::FlatForward Schema<QuantLib::FlatForward>::makeObj(const json& params) {
        json data = setDefaultValues(params);
        validate(data);

        double rate                       = data.at("rate");
        QuantLib::DayCounter dayCounter   = parse<QuantLib::DayCounter>(data.at("dayCounter"));
        QuantLib::Compounding compounding = parse<QuantLib::Compounding>(data.at("compounding"));
        QuantLib::Frequency frequency     = parse<QuantLib::Frequency>(data.at("frequency"));
        QuantLib::Date refDate            = parse<QuantLib::Date>(data.at("refDate"));
        bool enableExtrapolation          = data.at("enableExtrapolation");
        QuantLib::FlatForward curve(refDate, rate, dayCounter, compounding, frequency);
        curve.enableExtrapolation(enableExtrapolation);
        curve.unregisterWith(QuantLib::Settings::instance().evaluationDate());
        return curve;
    }
}  // namespace QuantLibParser
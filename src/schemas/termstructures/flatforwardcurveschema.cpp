
#include <qlp/parser.hpp>
#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/termstructures/flatforwardcurveschema.hpp>

namespace QuantLibParser {

    template <>
    void Schema<QuantLib::FlatForward>::initSchema() {
        json base = R"({
            "title": "Flat Forward Curve Schema",
            "properties": {},			
            "required": ["TYPE", "REFDATE", "NAME", "ENABLEEXTRAPOLATION", "RATE"]
        })"_json;

        base["properties"]                = baseCurveSchema;
        base["properties"]["REFDATE"]     = dateSchema;
        base["properties"]["RATE"]        = priceSchema;
        base["properties"]["DAYCOUNTER"]  = dayCounterSchema;
        base["properties"]["COMPOUNDING"] = compoundingSchema;
        base["properties"]["FREQUENCY"]   = frequencySchema;

        mySchema_ = base;
    };

    template <>
    void Schema<QuantLib::FlatForward>::initDefaultValues() {
        myDefaultValues_["ENABLEEXTRAPOLATION"] = true;
        myDefaultValues_["DAYCOUNTER"]          = "ACT360";
        myDefaultValues_["COMPOUNDING"]         = "SIMPLE";
        myDefaultValues_["FREQUENCY"]           = "ANNUAL";
    };

    template <>
    template <>
    QuantLib::FlatForward Schema<QuantLib::FlatForward>::makeObj(const json& params) {
        validate(params);
        json data                         = setDefaultValues(params);
        double rate                       = data.at("RATE");
        QuantLib::DayCounter dayCounter   = parse<QuantLib::DayCounter>(data.at("DAYCOUNTER"));
        QuantLib::Compounding compounding = parse<QuantLib::Compounding>(data.at("COMPOUNDING"));
        QuantLib::Frequency frequency     = parse<QuantLib::Frequency>(data.at("FREQUENCY"));
        QuantLib::Date refDate            = parse<QuantLib::Date>(data.at("REFDATE"));
        bool enableExtrapolation          = data.at("ENABLEEXTRAPOLATION");
        QuantLib::FlatForward curve(refDate, rate, dayCounter, compounding, frequency);
        curve.enableExtrapolation(enableExtrapolation);
        curve.unregisterWith(QuantLib::Settings::instance().evaluationDate());
        return curve;
    }
}  // namespace QuantLibParser
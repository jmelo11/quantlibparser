

#include <qlp/parser.hpp>
#include <qlp/schemas/termstructures/interestrateschema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::InterestRate>::initSchema() {
        mySchema_ = readJSONFile("interestrate.schema.json");
    };

    template <>
    void Schema<QuantLib::InterestRate>::initDefaultValues() {
        myDefaultValues_["dayCounter"]  = "Act360";
        myDefaultValues_["compounding"] = "Simple";
        myDefaultValues_["frequency"]   = "Annual";
    };

    template <>
    template <>
    QuantLib::InterestRate Schema<QuantLib::InterestRate>::makeObj(const json& params) {
        json data = setDefaultValues(params);
        validate(data);
        double value                    = data.at("value");
        QuantLib::DayCounter dayCounter = parse<QuantLib::DayCounter>(data.at("dayCounter"));
        QuantLib::Compounding comp      = parse<QuantLib::Compounding>(data.at("compounding"));
        QuantLib::Frequency freq        = parse<QuantLib::Frequency>(data.at("frequency"));

        return QuantLib::InterestRate(value, dayCounter, comp, freq);
    };

}  // namespace QuantLibParser

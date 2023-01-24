#ifndef F8125A90_5A12_4F42_96EF_D95C293D3201
#define F8125A90_5A12_4F42_96EF_D95C293D3201

#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/termstructures/interestrateschema.hpp>
#include <qlp/parser.hpp>

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

#endif /* F8125A90_5A12_4F42_96EF_D95C293D3201 */

#ifndef F8125A90_5A12_4F42_96EF_D95C293D3201
#define F8125A90_5A12_4F42_96EF_D95C293D3201

#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/termstructures/interestrateschema.hpp>
#include <qlp/parser.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::InterestRate>::initSchema() {
        json base = R"({
            "title": "Interest rate Schema",
            "properties": {},			
            "required": ["VALUE","DAYCOUNTER","COMPOUNDING","FREQUENCY"]
        })"_json;

        base["properties"]["VALUE"]       = priceSchema;
        base["properties"]["DAYCOUNTER"]  = dayCounterSchema;
        base["properties"]["COMPOUNDING"] = compoundingSchema;
        base["properties"]["FREQUENCY"]   = frequencySchema;

        mySchema_ = base;
    };

    template <>
    void Schema<QuantLib::InterestRate>::initDefaultValues() {
        myDefaultValues_["DAYCOUNTER"]  = "ACT360";
        myDefaultValues_["COMPOUNDING"] = "SIMPLE";
        myDefaultValues_["FREQUENCY"]   = "ANNUAL";
    };

    template <>
    template <>
    QuantLib::InterestRate Schema<QuantLib::InterestRate>::makeObj(const json& params) {
        json data = setDefaultValues(params);
        validate(data);
        double value                    = data.at("VALUE");
        QuantLib::DayCounter dayCounter = parse<QuantLib::DayCounter>(data.at("DAYCOUNTER"));
        QuantLib::Compounding comp      = parse<QuantLib::Compounding>(data.at("COMPOUNDING"));
        QuantLib::Frequency freq        = parse<QuantLib::Frequency>(data.at("FREQUENCY"));

        return QuantLib::InterestRate(value, dayCounter, comp, freq);
    };

}  // namespace QuantLibParser

#endif /* F8125A90_5A12_4F42_96EF_D95C293D3201 */

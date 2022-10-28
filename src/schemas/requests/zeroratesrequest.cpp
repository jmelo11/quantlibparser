#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/requests/zeroratesrequest.hpp>


namespace QuantLibParser {
    template <>
    void Schema<ZeroRatesRequests>::initSchema() {
        json base = R"({
            "title": "Discounts Request Schema",
            "type": "object",            
            "properties": {
                "CURVE": {
                    "type": "string"
                },
                "DATES": {
                    "type": "array",
                    "items": {}
                }
            },
            "required": ["REFDATE", "CURVE"]              
        })"_json;

        base["properties"]["FREQUENCY"]      = frequencySchema;
        base["properties"]["COMPOUNDING"]    = compoundingSchema;
        base["properties"]["DAYCOUNTER"]     = dayCounterSchema;
        base["properties"]["REFDATE"]        = dateSchema;
        base["properties"]["DATES"]["items"] = dateSchema;

        mySchema_ = base;
    };

    template <>
    void Schema<ZeroRatesRequests>::initDefaultValues() {
        myDefaultValues_["DAYCOUNTER"]  = "ACT360";
        myDefaultValues_["COMPOUNDING"] = "SIMPLE";
        myDefaultValues_["FREQUENCY"]   = "ANNUAL";
    };

    template class Schema<ZeroRatesRequests>;
}  // namespace QuantLibParser

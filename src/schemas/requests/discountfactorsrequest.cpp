#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/requests/discountfactorsrequest.hpp>

namespace QuantLibParser {
    template <>
    void Schema<DiscountFactorsRequest>::initSchema() {
        json base = R"({
            "title": "Discounts Request Schema",
            "type": "object",            
            "properties": {
                "CURVE": {
                    "type": "string"
                },
                "DATES": {
                    "type": "array"                    
                }
            },
            "required": ["REFDATE", "CURVE"]              
        })"_json;

        base["properties"]["REFDATE"]        = dateSchema;
        base["properties"]["DATES"]["items"] = dateSchema;

        mySchema_ = base;
    };

    template <>
    void Schema<DiscountFactorsRequest>::initDefaultValues(){

    };

}  // namespace QuantLibParser

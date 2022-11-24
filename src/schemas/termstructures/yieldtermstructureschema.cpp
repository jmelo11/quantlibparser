
#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/termstructures/yieldtermstructureschema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::YieldTermStructure>::initSchema() {
        json base = R"({
            "title": "General Curve Schema",
			"type": "object",
			"required": ["TYPE", "NAME", "ENABLEEXTRAPOLATION"],
			"properties": {}
        })"_json;

        base["properties"] = baseCurveSchema;

        mySchema_ = base;
    }

    template <>
    void Schema<QuantLib::YieldTermStructure>::initDefaultValues() {}

    
}  // namespace QuantLibParser
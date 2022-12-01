
#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/termstructures/discountcurveschema.hpp>

namespace QuantLibParser {

    template <>
    void Schema<QuantLib::DiscountCurve>::initSchema() {
        json base = R"({
            "title": "Discount Curve Schema",
            "properties": {},			
            "required": ["ENABLEEXTRAPOLATION", "NODES"]
        })"_json;

        json nodes = R"({
			"type": "array",
			"items": {
				"type": "object",
				"properties": {
					"DATE": {},
					"VALUE": {}
				},
				"required":["DATE","VALUE"]
			}
		})"_json;

        nodes["items"]["properties"]["DATE"]  = dateSchema;
        nodes["items"]["properties"]["VALUE"] = priceSchema;
        base["properties"]["NODES"]           = nodes;

        mySchema_ = base;
    };

    template <>
    void Schema<QuantLib::DiscountCurve>::initDefaultValues() {
        myDefaultValues_["ENABLEEXTRAPOLATION"] = true;
        myDefaultValues_["DAYCOUNTER"]          = "ACT360";
    };

    template <>
    template <>
    QuantLib::DiscountCurve Schema<QuantLib::DiscountCurve>::makeObj(const json& params) {
        json data = setDefaultValues(params);
        validate(data);

        const json& nodes = data.at("NODES");
        std::vector<QuantLib::Date> dates;
        std::vector<double> dfs;
        for (const auto& node : nodes) {
            dates.push_back(parse<QuantLib::Date>(node.at("DATE")));
            dfs.push_back(node.at("VALUE"));
        }
        QuantLib::DayCounter dayCounter = parse<QuantLib::DayCounter>(data.at("DAYCOUNTER"));

        bool enableExtrapolation = data.at("ENABLEEXTRAPOLATION");
        QuantLib::DiscountCurve curve(dates, dfs, dayCounter);

        curve.enableExtrapolation(enableExtrapolation);
        curve.unregisterWith(QuantLib::Settings::instance().evaluationDate());
        return curve;
    }

}  // namespace QuantLibParser
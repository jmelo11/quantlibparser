#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/ratehelpers/bondratehelperschema.hpp>
#include <qlp/schemas/ratehelpers/depositratehelperschema.hpp>
#include <qlp/schemas/ratehelpers/fixfloatxccyratehelperschema.hpp>
#include <qlp/schemas/ratehelpers/fxswapratehelperschema.hpp>
#include <qlp/schemas/ratehelpers/oisratehelperschema.hpp>
#include <qlp/schemas/ratehelpers/swapratehelperschema.hpp>
#include <qlp/schemas/ratehelpers/tenorbasisratehelperschema.hpp>
#include <qlp/schemas/ratehelpers/xccybasisratehelperschema.hpp>
#include <qlp/schemas/termstructures/bootstrapcurveschema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::PiecewiseYieldCurve<QuantLib::Discount, QuantLib::LogLinear>>::initSchema() {
        json base = R"({
            "title": "Bootstrap Curve Schema",
            "properties": {},			
            "required": ["RATEHELPERS"]
        })"_json;

        json ratehelpers = R"({
			"type": "array"			
		})"_json;

        base["properties"]["ENABLEEXTRAPOLATION"] = enableExtrapolationSchema;
        base["properties"]["RATEHELPERS"]         = ratehelpers;
        base["properties"]["DAYCOUNTER"]          = dayCounterSchema;
        mySchema_                                 = base;
    }

    template <>
    void Schema<QuantLib::PiecewiseYieldCurve<QuantLib::Discount, QuantLib::LogLinear>>::initDefaultValues() {
        myDefaultValues_["ENABLEEXTRAPOLATION"] = true;
        myDefaultValues_["DAYCOUNTER"]          = "ACT360";
    }

}  // namespace QuantLibParser
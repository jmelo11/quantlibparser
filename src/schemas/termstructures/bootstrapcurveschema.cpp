#include <qlp/schemas/termstructures/bootstrapcurveschema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::PiecewiseYieldCurve<QuantLib::Discount, QuantLib::LogLinear>>::initSchema() {
        mySchema_ = readJSONFile("bootstrapcurve.schema.json");
    }

    template <>
    void Schema<QuantLib::PiecewiseYieldCurve<QuantLib::Discount, QuantLib::LogLinear>>::initDefaultValues() {
        myDefaultValues_["enableExtrapolation"] = true;
        myDefaultValues_["dayCounter"]          = "Act360";
    }

}  // namespace QuantLibParser
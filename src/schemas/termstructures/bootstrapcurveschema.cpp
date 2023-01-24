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
        mySchema_ = readJSONFile("bootstrapcurve.schema.json");
    }

    template <>
    void Schema<QuantLib::PiecewiseYieldCurve<QuantLib::Discount, QuantLib::LogLinear>>::initDefaultValues() {
        myDefaultValues_["enableExtrapolation"] = true;
        myDefaultValues_["dayCounter"]          = "Act360";
    }

}  // namespace QuantLibParser
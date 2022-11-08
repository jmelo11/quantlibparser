#ifndef DA3366E8_01A3_405B_B0B7_42E56D00B2D2
#define DA3366E8_01A3_405B_B0B7_42E56D00B2D2

#include <qlp/schemas/schema.hpp>
#include <ql/math/interpolations/loginterpolation.hpp>
#include <ql/termstructures/yield/bootstraptraits.hpp>
#include <ql/termstructures/yield/piecewiseyieldcurve.hpp>

namespace QuantLibParser {
    template <>
    void
    Schema<QuantLib::PiecewiseYieldCurve<QuantLib::Discount, QuantLib::LogLinear>>::initSchema();

    template <>
    void Schema<QuantLib::PiecewiseYieldCurve<QuantLib::Discount,
                                              QuantLib::LogLinear>>::initDefaultValues();

}  // namespace QuantLibParser

#endif /* DA3366E8_01A3_405B_B0B7_42E56D00B2D2 */

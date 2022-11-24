#ifndef DA3366E8_01A3_405B_B0B7_42E56D00B2D2
#define DA3366E8_01A3_405B_B0B7_42E56D00B2D2

#include <ql/math/interpolations/loginterpolation.hpp>
#include <ql/termstructures/yield/bootstraptraits.hpp>
#include <ql/termstructures/yield/piecewiseyieldcurve.hpp>
#include <qlp/schemas/schema.hpp>

namespace QuantLibParser {
    using BootstrapCurve = QuantLib::PiecewiseYieldCurve<QuantLib::Discount, QuantLib::LogLinear>;

    
    template <>
    void Schema<BootstrapCurve>::initSchema();

    template <>
    void Schema<BootstrapCurve>::initDefaultValues();

}  // namespace QuantLibParser

#endif /* DA3366E8_01A3_405B_B0B7_42E56D00B2D2 */

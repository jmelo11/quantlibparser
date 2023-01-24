#ifndef A419F092_1290_4617_85D0_FD8CDDC17992
#define A419F092_1290_4617_85D0_FD8CDDC17992

#include <ql/termstructures/yield/ratehelpers.hpp>
#include <qlp/schemas/schema.hpp>

namespace QuantLibParser {

    template <>
    void Schema<QuantLib::SwapRateHelper>::initSchema();

    template <>
    void Schema<QuantLib::SwapRateHelper>::initDefaultValues();

    template <>
    template <>
    QuantLib::SwapRateHelper Schema<QuantLib::SwapRateHelper>::makeObj(const json& params, PriceGetter& priceGetter, IndexGetter& indexGetter,
                                                                       CurveGetter& curveGetter);
}  // namespace QuantLibParser

#endif /* A419F092_1290_4617_85D0_FD8CDDC17992 */

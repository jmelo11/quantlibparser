#ifndef B8C18B07_3A7F_4FC3_BE18_DE08D66F9B95
#define B8C18B07_3A7F_4FC3_BE18_DE08D66F9B95

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

#endif /* B8C18B07_3A7F_4FC3_BE18_DE08D66F9B95 */

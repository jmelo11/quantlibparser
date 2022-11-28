#ifndef A8848702_C1F4_4B97_B4AE_1BD0F21B7EFA
#define A8848702_C1F4_4B97_B4AE_1BD0F21B7EFA

#include <ql/termstructures/yield/oisratehelper.hpp>
#include <qlp/schemas/schema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::OISRateHelper>::initSchema();

    template <>
    void Schema<QuantLib::OISRateHelper>::initDefaultValues();

    template <>
    template <>
    QuantLib::OISRateHelper Schema<QuantLib::OISRateHelper>::makeObj(const json& params, PriceGetter& priceGetter, IndexGetter& indexGetter,
                                                                     CurveGetter& curveGetter);
}  // namespace QuantLibParser

#endif /* A8848702_C1F4_4B97_B4AE_1BD0F21B7EFA */

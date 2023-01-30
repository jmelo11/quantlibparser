#ifndef AD3742D4_E50B_4FA0_8341_2C3599919519
#define AD3742D4_E50B_4FA0_8341_2C3599919519

#include <qle/termstructures/crossccyfixfloatswaphelper.hpp>
#include <qlp/schemas/schema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantExt::CrossCcyFixFloatSwapHelper>::initSchema();

    template <>
    void Schema<QuantExt::CrossCcyFixFloatSwapHelper>::initDefaultValues();

    template <>
    template <>
    QuantExt::CrossCcyFixFloatSwapHelper Schema<QuantExt::CrossCcyFixFloatSwapHelper>::makeObj(const json& params, PriceGetter& priceGetter,
                                                                                               IndexGetter& indexGetter, CurveGetter& curveGetter);
}  // namespace QuantLibParser

#endif /* AD3742D4_E50B_4FA0_8341_2C3599919519 */

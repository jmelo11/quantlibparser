#ifndef E338F779_891D_44F5_A42D_06F1C31D3C95
#define E338F779_891D_44F5_A42D_06F1C31D3C95

#include <qle/termstructures/crossccybasisswaphelper.hpp>
#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/schema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantExt::CrossCcyBasisSwapHelper>::initSchema();

    template <>
    void Schema<QuantExt::CrossCcyBasisSwapHelper>::initDefaultValues();

    template <>
    template <>
    QuantExt::CrossCcyBasisSwapHelper Schema<QuantExt::CrossCcyBasisSwapHelper>::makeObj(const json& params, PriceGetter& priceGetter,
                                                                                         IndexGetter& indexGetter, CurveGetter& curveGetter);
}  // namespace QuantLibParser

#endif /* E338F779_891D_44F5_A42D_06F1C31D3C95 */

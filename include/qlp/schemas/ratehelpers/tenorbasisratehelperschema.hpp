#ifndef DEAA0F7B_583C_4859_B4CB_25853040A1AA
#define DEAA0F7B_583C_4859_B4CB_25853040A1AA

#include <qle/termstructures/tenorbasisswaphelper.hpp>
#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/schema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantExt::TenorBasisSwapHelper>::initSchema();

    template <>
    void Schema<QuantExt::TenorBasisSwapHelper>::initDefaultValues();

    template <>
    template <>
    QuantExt::TenorBasisSwapHelper Schema<QuantExt::TenorBasisSwapHelper>::makeObj(const json& params, PriceGetter& priceGetter,
                                                                                   IndexGetter& indexGetter, CurveGetter& curveGetter);

}  // namespace QuantLibParser

#endif /* DEAA0F7B_583C_4859_B4CB_25853040A1AA */

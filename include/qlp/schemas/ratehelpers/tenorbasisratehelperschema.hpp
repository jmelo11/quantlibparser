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

}  // namespace QuantLibParser

#endif /* DEAA0F7B_583C_4859_B4CB_25853040A1AA */

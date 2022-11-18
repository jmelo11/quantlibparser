#ifndef AD3742D4_E50B_4FA0_8341_2C3599919519
#define AD3742D4_E50B_4FA0_8341_2C3599919519

#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/schema.hpp>
#include <qle/termstructures/crossccyfixfloatswaphelper.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantExt::CrossCcyFixFloatSwapHelper>::initSchema();

    template <>
    void Schema<QuantExt::CrossCcyFixFloatSwapHelper>::initDefaultValues();
}  // namespace QuantLibParser

#endif /* AD3742D4_E50B_4FA0_8341_2C3599919519 */

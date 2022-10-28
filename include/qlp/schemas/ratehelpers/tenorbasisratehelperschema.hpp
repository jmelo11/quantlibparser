#pragma once

#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/schema.hpp>
#include <qle/termstructures/tenorbasisswaphelper.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantExt::TenorBasisSwapHelper>::initSchema();

    template <>
    void Schema<QuantExt::TenorBasisSwapHelper>::initDefaultValues();

}  // namespace QuantLibParser

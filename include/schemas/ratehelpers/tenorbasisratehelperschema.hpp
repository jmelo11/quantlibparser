#pragma once
#pragma once

#include <schemas/commonschemas.hpp>
#include <schemas/schema.hpp>
#include <qle/termstructures/tenorbasisswaphelper.hpp>

namespace QuantLibParser
{
    template <>
    void Schema <QuantExt::TenorBasisSwapHelper> ::initSchema();

    template<>
    void Schema<QuantExt::TenorBasisSwapHelper>::initDefaultValues();
	
}

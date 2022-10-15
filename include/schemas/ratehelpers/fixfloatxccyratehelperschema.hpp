#pragma once
#pragma once

#include <schemas/commonschemas.hpp>
#include <schemas/schema.hpp>
#include <qle/termstructures/crossccyfixfloatswaphelper.hpp>

namespace QuantLibParser
{
    template <>
    void Schema <QuantExt::CrossCcyFixFloatSwapHelper> ::initSchema();

    template<>
    void Schema<QuantExt::CrossCcyFixFloatSwapHelper>::initDefaultValues();
	
}

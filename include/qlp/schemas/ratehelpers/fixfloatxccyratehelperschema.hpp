#pragma once
#pragma once

#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/schema.hpp>
#include <qle/termstructures/crossccyfixfloatswaphelper.hpp>

namespace QuantLibParser
{
    template <>
    void Schema <QuantExt::CrossCcyFixFloatSwapHelper> ::initSchema();

    template<>
    void Schema<QuantExt::CrossCcyFixFloatSwapHelper>::initDefaultValues();
	
}

#pragma once
#pragma once

#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/schema.hpp>
#include <qle/termstructures/crossccybasisswaphelper.hpp>

namespace QuantLibParser
{
    template <>
    void Schema<QuantExt::CrossCcyBasisSwapHelper> ::initSchema();

    template<>
    void Schema<QuantExt::CrossCcyBasisSwapHelper>::initDefaultValues();
	
}

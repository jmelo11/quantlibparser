#pragma once
#pragma once

#include <schemas/commonschemas.hpp>
#include <schemas/schema.hpp>
#include <qle/termstructures/crossccybasisswaphelper.hpp>

namespace QuantLibParser
{
    template <>
    void Schema<QuantExt::CrossCcyBasisSwapHelper> ::initSchema();

    template<>
    void Schema<QuantExt::CrossCcyBasisSwapHelper>::initDefaultValues();
	
}

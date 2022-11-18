#ifndef F72A64CF_A426_44A2_8A94_B9B012261F23
#define F72A64CF_A426_44A2_8A94_B9B012261F23

#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/schema.hpp>
#include <ql/termstructures/yield/bondhelpers.hpp>

namespace QuantLibParser {

    
    template <>
    void Schema<QuantLib::FixedRateBondHelper>::initSchema();

    template <>
    void Schema<QuantLib::FixedRateBondHelper>::initDefaultValues();

    
}  // namespace QuantLibParser

#endif /* F72A64CF_A426_44A2_8A94_B9B012261F23 */

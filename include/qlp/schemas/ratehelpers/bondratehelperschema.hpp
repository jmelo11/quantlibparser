#ifndef F72A64CF_A426_44A2_8A94_B9B012261F23
#define F72A64CF_A426_44A2_8A94_B9B012261F23

#include <ql/termstructures/yield/bondhelpers.hpp>
#include <qlp/schemas/schema.hpp>

namespace QuantLibParser {
    
    template <>
    void Schema<QuantLib::FixedRateBondHelper>::initSchema();

    template <>
    void Schema<QuantLib::FixedRateBondHelper>::initDefaultValues();

    template <>
    template <>
    QuantLib::FixedRateBondHelper Schema<QuantLib::FixedRateBondHelper>::makeObj(const json& params, PriceGetter& pricerGetter);

}  // namespace QuantLibParser

#endif /* F72A64CF_A426_44A2_8A94_B9B012261F23 */

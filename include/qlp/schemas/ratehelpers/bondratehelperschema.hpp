#ifndef AD0E0B11_480B_45D6_9BD0_4BD218E4290D
#define AD0E0B11_480B_45D6_9BD0_4BD218E4290D

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

#endif /* AD0E0B11_480B_45D6_9BD0_4BD218E4290D */

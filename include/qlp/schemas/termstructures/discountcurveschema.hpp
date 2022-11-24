#ifndef A218B154_6229_475C_9F38_82AB59474D8C
#define A218B154_6229_475C_9F38_82AB59474D8C

#include <ql/termstructures/yield/discountcurve.hpp>
#include <qlp/parser.hpp>
#include <qlp/schemas/schema.hpp>

namespace QuantLibParser {

    template <>
    void Schema<QuantLib::DiscountCurve>::initSchema();

    template <>
    void Schema<QuantLib::DiscountCurve>::initDefaultValues();

    template <>
    template <>
    QuantLib::DiscountCurve Schema<QuantLib::DiscountCurve>::makeObj(const json& data);

}  // namespace QuantLibParser

#endif /* A218B154_6229_475C_9F38_82AB59474D8C */

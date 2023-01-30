#ifndef FBCE53F7_949D_4709_B6AB_BCF1DE30F4A5
#define FBCE53F7_949D_4709_B6AB_BCF1DE30F4A5

#include <ql/termstructures/yield/bondhelpers.hpp>
#include <qlp/schemas/schema.hpp>

namespace QuantLibParser {

    template <>
    void Schema<QuantLib::DepositRateHelper>::initSchema();

    template <>
    void Schema<QuantLib::DepositRateHelper>::initDefaultValues();

    template <>
    template <>
    QuantLib::DepositRateHelper Schema<QuantLib::DepositRateHelper>::makeObj(const json& params, PriceGetter& priceGetter);
}  // namespace QuantLibParser

#endif /* FBCE53F7_949D_4709_B6AB_BCF1DE30F4A5 */

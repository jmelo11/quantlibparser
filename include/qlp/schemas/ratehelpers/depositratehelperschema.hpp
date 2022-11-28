#ifndef CAD14D85_CBF4_4973_B946_7206E9020489
#define CAD14D85_CBF4_4973_B946_7206E9020489

#include <ql/termstructures/yield/bondhelpers.hpp>
#include <qlp/schemas/commonschemas.hpp>
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

#endif /* CAD14D85_CBF4_4973_B946_7206E9020489 */

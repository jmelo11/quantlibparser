#ifndef CAD14D85_CBF4_4973_B946_7206E9020489
#define CAD14D85_CBF4_4973_B946_7206E9020489

#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/schema.hpp>
#include <ql/termstructures/yield/bondhelpers.hpp>

namespace QuantLibParser {
    
    template <>
    void Schema<QuantLib::DepositRateHelper>::initSchema();

    template <>
    void Schema<QuantLib::DepositRateHelper>::initDefaultValues();

    
}  // namespace QuantLibParser

#endif /* CAD14D85_CBF4_4973_B946_7206E9020489 */

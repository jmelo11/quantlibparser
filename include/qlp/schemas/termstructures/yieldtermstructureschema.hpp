#ifndef A807DF1A_E4DB_4A26_BD82_C0A710059426
#define A807DF1A_E4DB_4A26_BD82_C0A710059426

#include <qlp/schemas/schema.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::YieldTermStructure>::initSchema();

    template <>
    void Schema<QuantLib::YieldTermStructure>::initDefaultValues();

}  // namespace QuantLibParser

#endif /* A807DF1A_E4DB_4A26_BD82_C0A710059426 */

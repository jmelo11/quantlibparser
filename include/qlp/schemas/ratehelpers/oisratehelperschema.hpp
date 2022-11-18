#ifndef A8848702_C1F4_4B97_B4AE_1BD0F21B7EFA
#define A8848702_C1F4_4B97_B4AE_1BD0F21B7EFA

#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/schema.hpp>
#include <ql/termstructures/yield/oisratehelper.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::OISRateHelper>::initSchema();

    template <>
    void Schema<QuantLib::OISRateHelper>::initDefaultValues();

    

}  // namespace QuantLibParser

#endif /* A8848702_C1F4_4B97_B4AE_1BD0F21B7EFA */

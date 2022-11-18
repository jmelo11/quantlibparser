#ifndef B8C18B07_3A7F_4FC3_BE18_DE08D66F9B95
#define B8C18B07_3A7F_4FC3_BE18_DE08D66F9B95

#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/schema.hpp>
#include <ql/termstructures/yield/ratehelpers.hpp>

namespace QuantLibParser {

    template <>
    void Schema<QuantLib::SwapRateHelper>::initSchema();

    template <>
    void Schema<QuantLib::SwapRateHelper>::initDefaultValues();

    

}  // namespace QuantLibParser

#endif /* B8C18B07_3A7F_4FC3_BE18_DE08D66F9B95 */

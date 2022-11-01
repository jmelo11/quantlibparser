#ifndef DCAFE307_2925_4B11_919B_1DB856AAD537
#define DCAFE307_2925_4B11_919B_1DB856AAD537

#include <qlp/schemas/schema.hpp>
#include <ql/indexes/interestrateindex.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::InterestRateIndex>::initSchema();

    template <>
    void Schema<QuantLib::InterestRateIndex>::initDefaultValues();
}  // namespace QuantLibParser

#endif /* DCAFE307_2925_4B11_919B_1DB856AAD537 */

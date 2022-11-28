#ifndef A6A9CC10_4DDC_44B2_AEFD_1263FF047351
#define A6A9CC10_4DDC_44B2_AEFD_1263FF047351
#include <ql/indexes/iborindex.hpp>
#include <qlp/schemas/schema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::OvernightIndex>::initSchema();

    template <>
    void Schema<QuantLib::OvernightIndex>::initDefaultValues();

    template <>
    template <>
    QuantLib::OvernightIndex Schema<QuantLib::OvernightIndex>::makeObj(const json& params, CurveGetter& curveGetter);

}  // namespace QuantLibParser

#endif /* A6A9CC10_4DDC_44B2_AEFD_1263FF047351 */

#ifndef EB3CA36C_356D_4516_B386_BAEE48887559
#define EB3CA36C_356D_4516_B386_BAEE48887559

#include <ql/indexes/iborindex.hpp>
#include <qlp/schemas/schema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::IborIndex>::initSchema();

    template <>
    void Schema<QuantLib::IborIndex>::initDefaultValues();

    template <>
    template <>
    QuantLib::IborIndex Schema<QuantLib::IborIndex>::makeObj(const json& params, CurveGetter& curveGetter);

}  // namespace QuantLibParser

#endif /* EB3CA36C_356D_4516_B386_BAEE48887559 */

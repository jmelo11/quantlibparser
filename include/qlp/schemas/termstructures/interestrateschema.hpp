#ifndef B4F82FA0_DDFB_4A25_8E71_CF7324E0B831
#define B4F82FA0_DDFB_4A25_8E71_CF7324E0B831

#include <ql/interestrate.hpp>
#include <qlp/schemas/schema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::InterestRate>::initSchema();

    template <>
    void Schema<QuantLib::InterestRate>::initDefaultValues();

    template <>
    template <>
    QuantLib::InterestRate Schema<QuantLib::InterestRate>::makeObj(const json& params);

}  // namespace QuantLibParser

#endif /* B4F82FA0_DDFB_4A25_8E71_CF7324E0B831 */

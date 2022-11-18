#ifndef F0AEEE6F_19E6_4423_ACD9_C2472F21036D
#define F0AEEE6F_19E6_4423_ACD9_C2472F21036D

#include <qlp/schemas/schema.hpp>
#include <ql/termstructures/yield/flatforward.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::FlatForward>::initSchema();

    template <>
    void Schema<QuantLib::FlatForward>::initDefaultValues();

    template <>
    std::optional<QuantLib::FlatForward> Schema<QuantLib::FlatForward>::makeObj(const json& params);

}  // namespace QuantLibParser

#endif /* F0AEEE6F_19E6_4423_ACD9_C2472F21036D */

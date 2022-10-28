#pragma once

#include <qlp/schemas/schema.hpp>

namespace QuantLibParser {
    class UpdateQuoteRequest;
    template <>
    void Schema<UpdateQuoteRequest>::initSchema();

    template <>
    void Schema<UpdateQuoteRequest>::initDefaultValues();
}  // namespace QuantLibParser
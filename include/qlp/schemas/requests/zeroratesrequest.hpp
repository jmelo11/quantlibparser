#ifndef D96A5895_A90A_4E74_8384_7D8CDBB81F30
#define D96A5895_A90A_4E74_8384_7D8CDBB81F30

#include <qlp/schemas/schema.hpp>

namespace QuantLibParser {
    class ZeroRatesRequests;
    template <>
    void Schema<ZeroRatesRequests>::initSchema();

    template <>
    void Schema<ZeroRatesRequests>::initDefaultValues();

}  // namespace QuantLibParser

#endif /* D96A5895_A90A_4E74_8384_7D8CDBB81F30 */

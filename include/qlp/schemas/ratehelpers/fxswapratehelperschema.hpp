#ifndef CF4F8D3D_40EC_4633_B9AB_60F0D5438517
#define CF4F8D3D_40EC_4633_B9AB_60F0D5438517

#include <ql/termstructures/yield/ratehelpers.hpp>
#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/schema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::FxSwapRateHelper>::initSchema();

    template <>
    void Schema<QuantLib::FxSwapRateHelper>::initDefaultValues();

}  // namespace QuantLibParser

#endif /* CF4F8D3D_40EC_4633_B9AB_60F0D5438517 */

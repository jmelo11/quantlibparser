#include <qlp/parser.hpp>
#include <qlp/schemas/ratehelpers/xccybasisratehelperschema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantExt::CrossCcyBasisSwapHelper>::initSchema() {
        mySchema_ = readJSONFile("xccybasis.ratehelper.schema.json");
    }

    template <>
    void Schema<QuantExt::CrossCcyBasisSwapHelper>::initDefaultValues() {
        myDefaultValues_["CALENDAR"]       = "NULLCALENDAR";
        myDefaultValues_["CONVENTION"]     = "MODIFIEDFOLLOWING";
        myDefaultValues_["ENDOFMONTH"]     = false;
        myDefaultValues_["FLATISDOMESTIC"] = true;
        myDefaultValues_["SETTLEMENTDAYS"] = 0;
    }

    template <>
    template <>
    QuantExt::CrossCcyBasisSwapHelper Schema<QuantExt::CrossCcyBasisSwapHelper>::makeObj(const json& params, PriceGetter& priceGetter,
                                                                                         IndexGetter& indexGetter, CurveGetter& curveGetter) {
        json data = setDefaultValues(params);
        validate(params);
        const json& helperConfig = data.at("helperConfig");
        const json& marketConfig = data.at("marketConfig");

        QuantLib::Calendar calendar                = parse<QuantLib::Calendar>(helperConfig.at("calendar"));
        QuantLib::BusinessDayConvention convention = parse<QuantLib::BusinessDayConvention>(helperConfig.at("convention"));
        QuantLib::Period tenor                     = parse<QuantLib::Period>(helperConfig.at("tenor"));

        bool endOfMonth     = helperConfig.at("endOfMonth");
        bool flatIsDomestic = helperConfig.at("flatIsDomestic");
        int settlementDays  = helperConfig.at("settlementDays");

        auto spread = priceGetter(marketConfig.at("spread").at("value"), marketConfig.at("spread").at("ticker"));

        auto flatDiscountCurve = helperConfig.find("flatDiscountCurve") != helperConfig.end() ? curveGetter(helperConfig.at("flatDiscountCurve")) :
                                                                                                RelinkableHandle<YieldTermStructure>();

        auto spreadDiscountCurve = helperConfig.find("spreadDiscountCurve") != helperConfig.end() ?
                                       curveGetter(helperConfig.at("spreadDiscountCurve")) :
                                       RelinkableHandle<YieldTermStructure>();
        if (flatDiscountCurve.empty() && spreadDiscountCurve.empty())
            throw std::runtime_error(
                "Either flatDiscountCurve or "
                "spreadDiscountCurve must be specified");

        auto fxSpot      = priceGetter(marketConfig.at("fxSpot").at("value"), marketConfig.at("fxSpot").at("ticker"));
        auto flatIndex   = indexGetter(helperConfig.at("flatIndex"));
        auto spreadIndex = indexGetter(helperConfig.at("spreadIndex"));

        return QuantExt::CrossCcyBasisSwapHelper(spread, fxSpot, settlementDays, calendar, tenor, convention, flatIndex, spreadIndex,
                                                 flatDiscountCurve, spreadDiscountCurve, endOfMonth, flatIsDomestic);
    }

}  // namespace QuantLibParser
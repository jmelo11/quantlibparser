#include <qlp/parser.hpp>
#include <qlp/schemas/ratehelpers/fixfloatxccyratehelperschema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantExt::CrossCcyFixFloatSwapHelper>::initSchema() {
        mySchema_ = readJSONFile("xccy.ratehelper.schema.json");
    }

    template <>
    void Schema<QuantExt::CrossCcyFixFloatSwapHelper>::initDefaultValues() {
        myDefaultValues_["helperConfig"]["dayCounter"]        = "Act360";
        myDefaultValues_["helperConfig"]["calendar"]          = "NullCalendar";
        myDefaultValues_["helperConfig"]["convention"]        = "Unadjusted";
        myDefaultValues_["helperConfig"]["settlementDays"]    = 0;
        myDefaultValues_["helperConfig"]["endOfMonth"]        = false;
        myDefaultValues_["helperConfig"]["fixedLegFrequency"] = "Semiannual";

    }

    template <>
    template <>
    QuantExt::CrossCcyFixFloatSwapHelper Schema<QuantExt::CrossCcyFixFloatSwapHelper>::makeObj(const json& params, PriceGetter& priceGetter,
                                                                                               IndexGetter& indexGetter, CurveGetter& curveGetter) {
        json data = setDefaultValues(params);
        validate(data);
        const json& helperConfig = data.at("helperConfig");
        const json& marketConfig = data.at("marketConfig");

        QuantLib::DayCounter dayCounter            = parse<QuantLib::DayCounter>(helperConfig.at("dayCounter"));
        QuantLib::Calendar calendar                = parse<QuantLib::Calendar>(helperConfig.at("calendar"));
        QuantLib::BusinessDayConvention convention = parse<QuantLib::BusinessDayConvention>(helperConfig.at("convention"));
        bool endOfMonth                            = helperConfig.at("endOfMonth");
        int settlementDays                         = helperConfig.at("settlementDays");
        QuantLib::Period tenor                     = parse<QuantLib::Period>(helperConfig.at("tenor"));
        QuantLib::Frequency frequency              = parse<QuantLib::Frequency>(helperConfig.at("fixedLegFrequency"));
        QuantLib::Currency currency                = parse<QuantLib::Currency>(helperConfig.at("fixedLegCurrency"));

        double spread  = marketConfig.at("spread").at("value");
        auto spreadPtr = ext::make_shared<QuantLib::SimpleQuote>(spread);
        QuantLib::Handle<QuantLib::Quote> spreadQuote(spreadPtr);

        bool hasDiscountCurve = helperConfig.find("discountCurve") != helperConfig.end();
        auto discountCurve =
            hasDiscountCurve ? curveGetter(helperConfig.at("discountCurve")) : QuantLib::RelinkableHandle<QuantLib::YieldTermStructure>();

        auto rate   = priceGetter(marketConfig.at("rate").at("value"), marketConfig.at("rate").at("ticker"));
        auto fxSpot = priceGetter(marketConfig.at("fxSpot").at("value"), marketConfig.at("rate").at("ticker"));
        auto index  = indexGetter(helperConfig.at("index"));

        return QuantExt::CrossCcyFixFloatSwapHelper(rate, fxSpot, settlementDays, calendar, convention, tenor, currency, frequency, convention,
                                                    dayCounter, index, discountCurve, spreadQuote, endOfMonth);
    };
}  // namespace QuantLibParser
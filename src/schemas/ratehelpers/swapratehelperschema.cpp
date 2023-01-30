#include <qlp/parser.hpp>
#include <qlp/schemas/ratehelpers/swapratehelperschema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::SwapRateHelper>::initSchema() {
        mySchema_ = readJSONFile("swap.ratehelper.schema.json");
    }

    template <>
    void Schema<QuantLib::SwapRateHelper>::initDefaultValues() {
        myDefaultValues_["helperConfig"]["calendar"]          = "NullCalendar";
        myDefaultValues_["helperConfig"]["convention"]        = "Unadjusted";
        myDefaultValues_["helperConfig"]["dayCounter"]        = "Act360";
        myDefaultValues_["helperConfig"]["settlementDays"]    = 0;
        myDefaultValues_["helperConfig"]["endOfMonth"]        = false;
        myDefaultValues_["helperConfig"]["fwdStart"]          = "0D";
        myDefaultValues_["helperConfig"]["fixedLegFrequency"] = "Semiannual";
    }

    template <>
    template <>
    QuantLib::SwapRateHelper Schema<QuantLib::SwapRateHelper>::makeObj(const json& params, PriceGetter& priceGetter, IndexGetter& indexGetter,
                                                                       CurveGetter& curveGetter) {
        json data = setDefaultValues(params);
        validate(data);
        const json& helperConfig = data.at("helperConfig");
        const json& marketConfig = data.at("marketConfig");

        QuantLib::DayCounter dayCounter            = parse<QuantLib::DayCounter>(helperConfig.at("dayCounter"));
        QuantLib::Calendar calendar                = parse<QuantLib::Calendar>(helperConfig.at("calendar"));
        QuantLib::BusinessDayConvention convention = parse<QuantLib::BusinessDayConvention>(helperConfig.at("convention"));
        QuantLib::Frequency frequency              = parse<QuantLib::Frequency>(helperConfig.at("fixedLegFrequency"));
        QuantLib::Period tenor                     = parse<QuantLib::Period>(helperConfig.at("tenor"));
        QuantLib::Period fwdStart                  = parse<QuantLib::Period>(helperConfig.at("fwdStart"));
        int settlementDays                         = helperConfig.at("settlementDays");

        double spread = marketConfig.at("spread").at("value");
        boost::shared_ptr<QuantLib::Quote> spreadPtr(new QuantLib::SimpleQuote(spread));
        QuantLib::Handle<QuantLib::Quote> spreadQuote(spreadPtr);

        auto discountCurve = helperConfig.find("discountCurve") != helperConfig.end() ? curveGetter(helperConfig.at("discountCurve")) :
                                                                                        QuantLib::RelinkableHandle<QuantLib::YieldTermStructure>();
        auto index         = indexGetter(helperConfig.at("index"));

        auto rate    = marketConfig.at("rate");
        auto mktRate = priceGetter(rate.at("value"), rate.at("ticker"));

        return QuantLib::SwapRateHelper(mktRate, tenor, calendar, frequency, convention, dayCounter, index, spreadQuote, fwdStart, discountCurve,
                                        settlementDays);
    }

}  // namespace QuantLibParser
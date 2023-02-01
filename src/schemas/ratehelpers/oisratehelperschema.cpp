#include <qlp/parser.hpp>
#include <qlp/schemas/ratehelpers/oisratehelperschema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::OISRateHelper>::initSchema() {
        mySchema_ = readJSONFile("ois.ratehelper.schema.json");
    }

    template <>
    void Schema<QuantLib::OISRateHelper>::initDefaultValues() {
        myDefaultValues_["helperConfig"]["dayCounter"]           = "Act360";
        myDefaultValues_["helperConfig"]["calendar"]             = "NullCalendar";
        myDefaultValues_["helperConfig"]["convention"]           = "Unadjusted";
        myDefaultValues_["helperConfig"]["spread"]               = 0.0;
        myDefaultValues_["helperConfig"]["settlementDays"]       = 0;
        myDefaultValues_["helperConfig"]["fwdStart"]             = "0D";
        myDefaultValues_["helperConfig"]["telescopicValueDates"] = true;
        myDefaultValues_["helperConfig"]["paymentLag"]           = 0;
        myDefaultValues_["helperConfig"]["fixedLegFrequency"]    = "Semiannual";

        myDefaultValues_["marketConfig"]["spread"]["value"] = 0.0;
        myDefaultValues_["marketConfig"]["spread"]["ticker"] = "null";
    }

    template <>
    template <>
    QuantLib::OISRateHelper Schema<QuantLib::OISRateHelper>::makeObj(const json& params, PriceGetter& priceGetter, IndexGetter& indexGetter,
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
        int settlementDays                         = helperConfig.at("settlementDays");
        int paymentLag                             = helperConfig.at("paymentLag");
        bool telescopicValueDates                  = helperConfig.at("telescopicValueDates");

        QuantLib::Period fwdStart = parse<QuantLib::Period>(helperConfig.at("fwdStart"));

        auto discountCurve = helperConfig.find("discountCurve") != helperConfig.end() ? curveGetter(helperConfig.at("discountCurve")) :
                                                                                QuantLib::RelinkableHandle<QuantLib::YieldTermStructure>();

        double spread = marketConfig.at("spread").at("value");
        auto rate     = marketConfig.at("rate");
        auto mktRate  = priceGetter(rate.at("value"), rate.at("ticker"));
        auto index    = indexGetter(helperConfig.at("index"));
        auto indexPtr = boost::dynamic_pointer_cast<QuantLib::OvernightIndex>(index);

        return QuantLib::OISRateHelper(settlementDays, tenor, mktRate, indexPtr, discountCurve, telescopicValueDates, paymentLag, convention,
                                       frequency, calendar, fwdStart, spread);
    }
}  // namespace QuantLibParser
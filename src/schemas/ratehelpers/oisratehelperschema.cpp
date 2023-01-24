#include <qlp/parser.hpp>
#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/ratehelpers/oisratehelperschema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::OISRateHelper>::initSchema() {
        mySchema_ = readJSONFile("oisratehelper.schema.json");
    }

    template <>
    void Schema<QuantLib::OISRateHelper>::initDefaultValues() {
        myDefaultValues_["DAYCOUNTER"]           = "ACT360";
        myDefaultValues_["CALENDAR"]             = "NULLCALENDAR";
        myDefaultValues_["CONVENTION"]           = "UNADJUSTED";
        myDefaultValues_["SPREAD"]               = 0.0;
        myDefaultValues_["SETTLEMENTDAYS"]       = 0;
        myDefaultValues_["FWDSTART"]             = "0D";
        myDefaultValues_["TELESCOPICVALUEDATES"] = true;
        myDefaultValues_["PAYMENTLAG"]           = 0;
    }

    template <>
    template <>
    QuantLib::OISRateHelper Schema<QuantLib::OISRateHelper>::makeObj(const json& params, PriceGetter& priceGetter, IndexGetter& indexGetter,
                                                                     CurveGetter& curveGetter) {
        json data = setDefaultValues(params);
        validate(params);
        const json& helperConfig = data.at("helperConfig");
        const json& marketConfig = data.at("marketConfig");

        QuantLib::DayCounter dayCounter            = parse<QuantLib::DayCounter>(helperConfig.at("dayCounter"));
        QuantLib::Calendar calendar                = parse<QuantLib::Calendar>(helperConfig.at("calendar"));
        QuantLib::BusinessDayConvention convention = parse<QuantLib::BusinessDayConvention>(helperConfig.at("convention"));
        QuantLib::Frequency frequency              = parse<QuantLib::Frequency>(helperConfig.at("paymentFrequency"));
        QuantLib::Period tenor                     = parse<QuantLib::Period>(helperConfig.at("tenor"));
        int settlementDays                         = helperConfig.at("settlementDays");
        int paymentLag                             = helperConfig.at("paymentLag");
        bool telescopicValueDates                  = helperConfig.at("telescopicValueDates");

        QuantLib::Period fwdStart = parse<QuantLib::Period>(helperConfig.at("fwdStart"));

        auto discountCurve = data.find("discountCurve") != helperConfig.end() ? curveGetter(helperConfig.at("discountCurve")) :
                                                                                QuantLib::RelinkableHandle<QuantLib::YieldTermStructure>();

        double spread = marketConfig.at("spread").at("value");
        auto rate     = marketConfig.at("rate");
        auto mktRate  = priceGetter(rate.at("value"), rate.at("ticker"));
        auto index    = indexGetter(helperConfig.at("index"));
        auto indexPtr = boost::dynamic_pointer_cast<QuantLib::OvernightIndex>(index);

        return QuantLib::OISRateHelper(settlementDays, tenor, mktRate, indexPtr, discountCurve, telescopicValueDates, paymentLag, convention, frequency,
                                       calendar, fwdStart, spread);
    }
}  // namespace QuantLibParser
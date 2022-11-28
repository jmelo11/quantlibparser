#include <qlp/parser.hpp>
#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/ratehelpers/oisratehelperschema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::OISRateHelper>::initSchema() {
        json base = R"({
            "title": "OIS Rate Helper Schema",
            "properties": {},
            "required": ["TYPE", "RATE", "RATETICKER", "TENOR", "INDEX"]
        })"_json;

        base["properties"]["DAYCOUNTER"]           = dayCounterSchema;
        base["properties"]["CALENDAR"]             = calendarSchema;
        base["properties"]["CONVENTION"]           = conventionSchema;
        base["properties"]["FREQUENCY"]            = frequencySchema;
        base["properties"]["SPREAD"]               = priceSchema;
        base["properties"]["SETTLEMENTDAYS"]       = fixingDaysSchema;
        base["properties"]["FWDSTART"]             = tenorSchema;
        base["properties"]["PAYMENTLAG"]           = fixingDaysSchema;
        base["properties"]["TELESCOPICVALUEDATES"] = eomSchema;
        base["properties"]["DISCOUNTINGCURVE"]     = curveNameSchema;
        base["properties"]["RATE"]                 = priceSchema;
        base["properties"]["RATETICKER"]           = tickerSchema;
        base["properties"]["INDEX"]                = curveNameSchema;
        base["properties"]["TYPE"]                 = rateHelperTypeSchema;
        base["properties"]["TENOR"]                = tenorSchema;

        mySchema_ = base;
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
        validate(params);
        json data = setDefaultValues(params);

        QuantLib::DayCounter dayCounter            = parse<QuantLib::DayCounter>(data.at("DAYCOUNTER"));
        QuantLib::Calendar calendar                = parse<QuantLib::Calendar>(data.at("CALENDAR"));
        QuantLib::BusinessDayConvention convention = parse<QuantLib::BusinessDayConvention>(data.at("CONVENTION"));
        QuantLib::Frequency frequency              = parse<QuantLib::Frequency>(data.at("FREQUENCY"));
        QuantLib::Period tenor                     = parse<QuantLib::Period>(data.at("TENOR"));
        double spread                              = data.at("SPREAD");
        int settlementDays                         = data.at("SETTLEMENTDAYS");
        int paymentLag                             = data.at("PAYMENTLAG");
        bool telescopicValueDates                  = data.at("TELESCOPICVALUEDATES");

        QuantLib::Period fwdStart = parse<QuantLib::Period>(data.at("FWDSTART"));

        auto discountCurve = data.find("DISCOUNTINGCURVE") != data.end() ? curveGetter(data.at("DISCOUNTINGCURVE")) :
                                                                           QuantLib::RelinkableHandle<QuantLib::YieldTermStructure>();

        auto rate  = priceGetter(data.at("RATE"), data.at("RATETICKER"));
        auto index = boost::dynamic_pointer_cast<QuantLib::OvernightIndex>(indexGetter(params.at("INDEX")));

        return QuantLib::OISRateHelper(settlementDays, tenor, rate, index, discountCurve, telescopicValueDates, paymentLag, convention, frequency,
                                       calendar, fwdStart, spread);
    }
}  // namespace QuantLibParser
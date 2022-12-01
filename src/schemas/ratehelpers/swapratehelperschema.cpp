#include <qlp/parser.hpp>
#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/ratehelpers/swapratehelperschema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::SwapRateHelper>::initSchema() {
        json base = R"({
            "title": "Swap Rate Helper Schema",
            "properties": {},
            "required": ["TYPE", "RATE", "RATETICKER", "TENOR", "INDEX"]
        })"_json;

        base["properties"]["DAYCOUNTER"]       = dayCounterSchema;
        base["properties"]["CALENDAR"]         = calendarSchema;
        base["properties"]["CONVENTION"]       = conventionSchema;
        base["properties"]["FREQUENCY"]        = frequencySchema;
        base["properties"]["SPREAD"]           = priceSchema;
        base["properties"]["SETTLEMENTDAYS"]   = fixingDaysSchema;
        base["properties"]["FWDSTART"]         = tenorSchema;
        base["properties"]["DISCOUNTINGCURVE"] = curveNameSchema;
        base["properties"]["RATE"]             = priceSchema;
        base["properties"]["RATETICKER"]       = tickerSchema;
        base["properties"]["INDEX"]            = curveNameSchema;
        base["properties"]["TYPE"]             = rateHelperTypeSchema;
        base["properties"]["TENOR"]            = tenorSchema;
        mySchema_                              = base;
    }

    template <>
    void Schema<QuantLib::SwapRateHelper>::initDefaultValues() {
        myDefaultValues_["DAYCOUNTER"]     = "ACT360";
        myDefaultValues_["CALENDAR"]       = "NULLCALENDAR";
        myDefaultValues_["CONVENTION"]     = "UNADJUSTED";
        myDefaultValues_["SPREAD"]         = 0.0;
        myDefaultValues_["SETTLEMENTDAYS"] = 0;
        myDefaultValues_["FWDSTART"]       = "0D";
    }

    template <>
    template <>
    QuantLib::SwapRateHelper Schema<QuantLib::SwapRateHelper>::makeObj(const json& params, PriceGetter& priceGetter, IndexGetter& indexGetter,
                                                                       CurveGetter& curveGetter) {
        json data = setDefaultValues(params);
        validate(data);

        QuantLib::DayCounter dayCounter            = parse<QuantLib::DayCounter>(data.at("DAYCOUNTER"));
        QuantLib::Calendar calendar                = parse<QuantLib::Calendar>(data.at("CALENDAR"));
        QuantLib::BusinessDayConvention convention = parse<QuantLib::BusinessDayConvention>(data.at("CONVENTION"));
        QuantLib::Frequency frequency              = parse<QuantLib::Frequency>(data.at("FREQUENCY"));
        QuantLib::Period tenor                     = parse<QuantLib::Period>(data.at("TENOR"));
        QuantLib::Period fwdStart                  = parse<QuantLib::Period>(data.at("FWDSTART"));
        int settlementDays                         = data.at("SETTLEMENTDAYS");

        double spread = data.at("SPREAD");
        boost::shared_ptr<QuantLib::Quote> spreadPtr(new QuantLib::SimpleQuote(spread));
        QuantLib::Handle<QuantLib::Quote> spreadQuote(spreadPtr);

        auto discountCurve = data.find("DISCOUNTINGCURVE") != data.end() ? curveGetter(data.at("DISCOUNTINGCURVE")) :
                                                                           QuantLib::RelinkableHandle<QuantLib::YieldTermStructure>();

        auto rate = priceGetter(data.at("RATE"), data.at("RATETICKER"));

        auto index = indexGetter(data.at("INDEX"));
        return QuantLib::SwapRateHelper(rate, tenor, calendar, frequency, convention, dayCounter, index, spreadQuote, fwdStart, discountCurve,
                                        settlementDays);
    }

}  // namespace QuantLibParser
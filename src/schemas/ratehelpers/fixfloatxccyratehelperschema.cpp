#include <qlp/parser.hpp>
#include <qlp/schemas/ratehelpers/fixfloatxccyratehelperschema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantExt::CrossCcyFixFloatSwapHelper>::initSchema() {
        json base = R"({
            "title": "Xccy Rate Helper Schema",
            "properties": {},
            "required": ["TYPE", "RATE", "RATETICKER", "FXSPOT", "FXSPOTTICKER", "TENOR", "CURRENCY", "INDEX"]
        })"_json;

        base["properties"]["DAYCOUNTER"]       = dayCounterSchema;
        base["properties"]["CALENDAR"]         = calendarSchema;
        base["properties"]["CONVENTION"]       = conventionSchema;
        base["properties"]["ENDOFMONTH"]       = eomSchema;
        base["properties"]["FREQUENCY"]        = frequencySchema;
        base["properties"]["SETTLEMENTDAYS"]   = fixingDaysSchema;
        base["properties"]["SPREAD"]           = priceSchema;
        base["properties"]["DISCOUNTINGCURVE"] = curveNameSchema;
        base["properties"]["RATE"]             = priceSchema;
        base["properties"]["RATETICKER"]       = tickerSchema;
        base["properties"]["FXSPOT"]           = priceSchema;
        base["properties"]["FXSPOTTICKER"]     = tickerSchema;
        base["properties"]["INDEX"]            = curveNameSchema;
        base["properties"]["CURRENCY"]         = currencySchema;
        base["properties"]["TYPE"]             = rateHelperTypeSchema;
        base["properties"]["TENOR"]            = tenorSchema;

        mySchema_ = base;
    }

    template <>
    void Schema<QuantExt::CrossCcyFixFloatSwapHelper>::initDefaultValues() {
        myDefaultValues_["DAYCOUNTER"]     = "ACT360";
        myDefaultValues_["CALENDAR"]       = "NULLCALENDAR";
        myDefaultValues_["CONVENTION"]     = "UNADJUSTED";
        myDefaultValues_["SETTLEMENTDAYS"] = 0;
        myDefaultValues_["ENDOFMONTH"]     = false;
        myDefaultValues_["FREQUENCY"]      = "SEMIANNUAL";
        myDefaultValues_["SPREAD"]         = 0.0;
    }

    template <>
    template <>
    QuantExt::CrossCcyFixFloatSwapHelper Schema<QuantExt::CrossCcyFixFloatSwapHelper>::makeObj(const json& params, PriceGetter& priceGetter,
                                                                                               IndexGetter& indexGetter, CurveGetter& curveGetter) {
        validate(params);
        json data = setDefaultValues(params);

        QuantLib::DayCounter dayCounter            = parse<QuantLib::DayCounter>(data.at("DAYCOUNTER"));
        QuantLib::Calendar calendar                = parse<QuantLib::Calendar>(data.at("CALENDAR"));
        QuantLib::BusinessDayConvention convention = parse<QuantLib::BusinessDayConvention>(data.at("CONVENTION"));
        bool endOfMonth                            = data.at("ENDOFMONTH");
        int settlementDays                         = data.at("SETTLEMENTDAYS");
        QuantLib::Period tenor                     = parse<QuantLib::Period>(data.at("TENOR"));
        QuantLib::Frequency frequency              = parse<QuantLib::Frequency>(data.at("FREQUENCY"));
        QuantLib::Currency currency                = parse<QuantLib::Currency>(data.at("CURRENCY"));

        double spread  = data.at("SPREAD");
        auto spreadPtr = ext::make_shared<QuantLib::SimpleQuote>(spread);
        QuantLib::Handle<QuantLib::Quote> spreadQuote(spreadPtr);

        auto discountCurve = data.find("DISCOUNTINGCURVE") == data.end() ? curveGetter(data.at("DISCOUNTINGCURVE")) :
                                                                           QuantLib::RelinkableHandle<QuantLib::YieldTermStructure>();

        auto rate   = priceGetter(data.at("RATE"), data.at("RATETICKER"));
        auto fxSpot = priceGetter(data.at("FXSPOT"), data.at("FXSPOTTICKER"));
        auto index  = indexGetter(data.at("INDEX"));

        return QuantExt::CrossCcyFixFloatSwapHelper(rate, fxSpot, settlementDays, calendar, convention, tenor, currency, frequency, convention,
                                                    dayCounter, index, discountCurve, spreadQuote, endOfMonth);
    };
}  // namespace QuantLibParser
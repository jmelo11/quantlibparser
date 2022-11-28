#include <qlp/parser.hpp>
#include <qlp/schemas/ratehelpers/fxswapratehelperschema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::FxSwapRateHelper>::initSchema() {
        json base = R"({
            "title": "FX Swap Rate Helper Schema",
            "properties": {},
            "required": ["TYPE", "FXPOINTS", "FXPOINTSTICKER", "FXSPOTTICKER", "FXSPOT"]
        })"_json;

        base["properties"]["FXSPOT"]                 = priceSchema;
        base["properties"]["FXSPOTTICKER"]           = tickerSchema;
        base["properties"]["FXPOINTS"]               = priceSchema;
        base["properties"]["FXPOINTSTICKER"]         = tickerSchema;
        base["properties"]["STARTDATE"]              = dateSchema;
        base["properties"]["ENDDATE"]                = dateSchema;
        base["properties"]["TENOR"]                  = tenorSchema;
        base["properties"]["TYPE"]                   = rateHelperTypeSchema;
        base["properties"]["ENDOFMONTH"]             = eomSchema;
        base["properties"]["CONVENTION"]             = conventionSchema;
        base["properties"]["CALENDAR"]               = calendarSchema;
        base["properties"]["FIXINGDATS"]             = fixingDaysSchema;
        base["properties"]["BASECURRENCYCOLLATERAL"] = isBaseCurrencySchema;
        base["properties"]["COLLATERALCURVE"]        = curveNameSchema;

        mySchema_ = base;
    }

    template <>
    void Schema<QuantLib::FxSwapRateHelper>::initDefaultValues() {
        myDefaultValues_["STARTDATE"]  = parseDate(QuantLib::Settings::instance().evaluationDate());
        myDefaultValues_["CALENDAR"]   = "NULLCALENDAR";
        myDefaultValues_["FIXINGDAYS"] = 0;
        myDefaultValues_["ENDOFMONTH"] = false;
        myDefaultValues_["DAYCOUNTER"] = "ACT360";
        myDefaultValues_["CONVENTION"] = "UNADJUSTED";
    }

    template <>
    template <>
    QuantLib::FxSwapRateHelper Schema<QuantLib::FxSwapRateHelper>::makeObj(const json& params, PriceGetter& priceGetter, CurveGetter& curveGetter) {
        validate(params);
        json data = setDefaultValues(params);

        QuantLib::Calendar calendar                = parse<QuantLib::Calendar>(data.at("CALENDAR"));
        QuantLib::BusinessDayConvention convention = parse<QuantLib::BusinessDayConvention>(data.at("CONVENTION"));
        bool endOfMonth                            = data.at("ENDOFMONTH");
        double fixingDays                          = params.at("FIXINGDAYS");
        bool endOfMont                             = params.at("ENDOFMONTH");
        bool baseCurrencyColateral                 = params.at("BASECURRENCYCOLLATERAL");

        auto collateralCurve =
            data.find("COLLATERALCURVE") != data.end() ? curveGetter(params.at("COLLATERALCURVE")) : RelinkableHandle<YieldTermStructure>();

        // non-defaults
        QuantLib::Period tenor;
        if (data.find("ENDDATE") != data.end()) {
            QuantLib::Date endDate   = parse<QuantLib::Date>(params.at("ENDDATE"));
            QuantLib::Date startDate = parse<QuantLib::Date>(params.at("STARTDATE"));

            int days = endDate - startDate;
            if (days > 0) {
                tenor = QuantLib::Period(days, QuantLib::TimeUnit::Days);
            } else {
                
                throw std::runtime_error("Error processing FXSWAPRATEHELPER: End date must be after today (" + parseDate(startDate) + ").");
            }
        } else {
            tenor = parse<QuantLib::Period>(params.at("TENOR"));
        }

        auto fxPoints = priceGetter(params.at("FXPOINTS"), params.at("FXPOINTSTICKER"));
        auto fxSpot   = priceGetter(params.at("FXSPOT"), params.at("FXSPOTTICKER"));

        return QuantLib::FxSwapRateHelper(fxPoints, fxSpot, tenor, fixingDays, calendar, convention, endOfMonth, baseCurrencyColateral,
                                          collateralCurve);
    }
}  // namespace QuantLibParser
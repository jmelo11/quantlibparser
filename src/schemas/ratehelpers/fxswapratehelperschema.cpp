#include <qlp/parser.hpp>
#include <qlp/schemas/ratehelpers/fxswapratehelperschema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::FxSwapRateHelper>::initSchema() {
        mySchema_ = readJSONFile("fxswap.ratehelper.schema.json");
    }

    template <>
    void Schema<QuantLib::FxSwapRateHelper>::initDefaultValues() {
        myDefaultValues_["helperConfig"]["startDate"]  = parseDate(QuantLib::Settings::instance().evaluationDate());
        myDefaultValues_["helperConfig"]["calendar"]   = "NullCalendar";
        myDefaultValues_["helperConfig"]["fixingDays"] = 0;
        myDefaultValues_["helperConfig"]["endOfMonth"] = false;
        myDefaultValues_["helperConfig"]["dayCounter"] = "Act360";
        myDefaultValues_["helperConfig"]["convention"] = "Unadjusted";
    }

    template <>
    template <>
    QuantLib::FxSwapRateHelper Schema<QuantLib::FxSwapRateHelper>::makeObj(const json& params, PriceGetter& priceGetter, CurveGetter& curveGetter) {
        json data = setDefaultValues(params);
        validate(data);
        const json& helperConfig = data.at("helperConfig");
        const json& marketConfig = data.at("marketConfig");

        QuantLib::Calendar calendar                = parse<QuantLib::Calendar>(helperConfig.at("calendar"));
        QuantLib::BusinessDayConvention convention = parse<QuantLib::BusinessDayConvention>(helperConfig.at("convention"));
        bool endOfMonth                            = helperConfig.at("endOfMonth");
        double fixingDays                          = helperConfig.at("fixingDays");
        bool endOfMont                             = helperConfig.at("endOfMonth");
        bool baseCurrencyColateral                 = helperConfig.at("baseCurrencyAsCollateral");

        auto collateralCurve = helperConfig.find("collateralCurve") != helperConfig.end() ? curveGetter(helperConfig.at("collateralCurve")) :
                                                                                    RelinkableHandle<YieldTermStructure>();

        // non-defaults
        QuantLib::Period tenor;
        if (helperConfig.find("endDate") != helperConfig.end()) {
            QuantLib::Date endDate   = parse<QuantLib::Date>(helperConfig.at("endDate"));
            QuantLib::Date startDate = parse<QuantLib::Date>(helperConfig.at("startDate"));

            int days = endDate - startDate;
            if (days > 0) {
                tenor = QuantLib::Period(days, QuantLib::TimeUnit::Days);
            } else {
                throw std::runtime_error("Error processing FxSwapRateHelper: End date must be after today (" + parseDate(startDate) + ")");
            }
        } else {
            tenor = parse<QuantLib::Period>(helperConfig.at("tenor"));
        }

        auto fxPoints = priceGetter(marketConfig.at("fxPoints").at("value"), marketConfig.at("fxPoints").at("ticker"));
        auto fxSpot   = priceGetter(marketConfig.at("fxSpot").at("value"), marketConfig.at("fxSpot").at("ticker"));

        return QuantLib::FxSwapRateHelper(fxPoints, fxSpot, tenor, fixingDays, calendar, convention, endOfMonth, baseCurrencyColateral,
                                          collateralCurve);
    }
}  // namespace QuantLibParser
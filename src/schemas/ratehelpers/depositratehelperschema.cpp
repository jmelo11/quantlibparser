#include <qlp/parser.hpp>
#include <qlp/schemas/ratehelpers/depositratehelperschema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::DepositRateHelper>::initSchema() {
        mySchema_ = readJSONFile("depositratehelper.schema.json");
    }

    template <>
    void Schema<QuantLib::DepositRateHelper>::initDefaultValues() {
        myDefaultValues_["helperConfig"]["calendar"]       = "NullCalendar";
        myDefaultValues_["helperConfig"]["convention"]     = "Unadjusted";
        myDefaultValues_["helperConfig"]["dayCounter"]     = "Act360";
        myDefaultValues_["helperConfig"]["settlementDays"] = 0;       
        myDefaultValues_["helperConfig"]["endOfMonth"]     = false;
    }

    template <>
    template <>
    QuantLib::DepositRateHelper Schema<QuantLib::DepositRateHelper>::makeObj(const json& params, PriceGetter& priceGetter) {
        json data = setDefaultValues(params);
        validate(params);
        const json& helperConfig = data.at("helperConfig");
        const json& marketConfig = data.at("marketConfig");

        QuantLib::DayCounter dayCounter = parse<QuantLib::DayCounter>(helperConfig.at("dayCounter"));
        QuantLib::Calendar calendar     = parse<QuantLib::Calendar>(helperConfig.at("calendar"));

        double settlementDays                      = helperConfig.at("settlementDays");
        bool endOfMonth                            = helperConfig.at("endOfMonth");
        QuantLib::BusinessDayConvention convention = parse<QuantLib::BusinessDayConvention>(data.at("convention"));

        // non-defaults
        QuantLib::Period tenor = parse<QuantLib::Period>(data.at("tenor"));

        const json& rate = marketConfig.at("rate");
        auto mktRate     = priceGetter(marketConfig.at("value"), marketConfig.at("ticker"));
        return DepositRateHelper(mktRate, tenor, settlementDays, calendar, convention, endOfMonth, dayCounter);
    }
}  // namespace QuantLibParser

#include <qlp/parser.hpp>
#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/ratehelpers/bondratehelperschema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantLib::FixedRateBondHelper>::initSchema() {
        mySchema_ = readJSONFile("bondratehelper.schema.json");
    };

    template <>
    void Schema<QuantLib::FixedRateBondHelper>::initDefaultValues() {
        myDefaultValues_["helperConfig"]["calendar"] = "NullCalendar";
        myDefaultValues_["helperConfig"]["convention"] = "Unadjusted";
        myDefaultValues_["helperConfig"]["paymentFrequency"] = "SemiAnnual";
        myDefaultValues_["helperConfig"]["couponDayCounter"] = "Thirty360";
        myDefaultValues_["helperConfig"]["yieldDayCounter"] = "Act360";
        myDefaultValues_["helperConfig"]["settlementDays"] = 0;        
        myDefaultValues_["helperConfig"]["couponRate"] = 0.03;
    };

    template <>
    template <>
    QuantLib::FixedRateBondHelper Schema<QuantLib::FixedRateBondHelper>::makeObj(const json& params, PriceGetter& priceGetter) {
        json data = setDefaultValues(params);
        validate(params);        
        const json& helperConfig = data.at("helperConfig");
        const json& marketConfig = data.at("marketConfig");

        QuantLib::Calendar calendar                = parse<QuantLib::Calendar>(helperConfig.at("calendar"));
        QuantLib::BusinessDayConvention convention = parse<QuantLib::BusinessDayConvention>(helperConfig.at("convention"));
        QuantLib::Frequency frequency              = parse<QuantLib::Frequency>(helperConfig.at("paymentFrequency"));
        QuantLib::Period tenor                     = parse<QuantLib::Period>(helperConfig.at("tenor"));
        QuantLib::DayCounter couponDayCounter      = parse<QuantLib::DayCounter>(helperConfig.at("couponDayCounter"));
        QuantLib::DayCounter yieldDayCounter       = parse<QuantLib::DayCounter>(helperConfig.at("yieldDayCounter"));

        double settlementDays = helperConfig.at("settlementDays");
        double faceAmount     = 100;
        double coupon         = helperConfig.at("couponRate");

        QuantLib::Date startDate = parse<Date>(helperConfig.at("startDate"));
        QuantLib::Date endDate;
        if (helperConfig.find("endDate") != helperConfig.end()) {
            endDate = parse<Date>(helperConfig.at("endDate"));
        } else {
            endDate = startDate + tenor;
        }

        /* coupon rate */
        QuantLib::InterestRate couponRate(coupon, couponDayCounter, QuantLib::Compounding::Simple, QuantLib::Frequency::Annual);
        std::vector<QuantLib::InterestRate> coupons{couponRate};

        /* price */
        const json& rate = marketConfig.at("rate");
        auto RATE = priceGetter(rate.at("value"), rate.at("ticker"));

        QuantLib::Schedule schedule =
            QuantLib::MakeSchedule().from(startDate).to(endDate).withTenor(tenor).withFrequency(frequency).withCalendar(calendar).withConvention(
                convention);

        QuantLib::FixedRateBond bond(settlementDays, faceAmount, schedule, coupons);
        boost::shared_ptr<QuantLib::SimpleQuote> cleanPrice(boost::make_shared<SimpleQuote>(
            bond.cleanPrice(RATE->value(), yieldDayCounter, QuantLib::Compounding::Compounded, QuantLib::Frequency::Annual)));
        QuantLib::Handle<QuantLib::Quote> handlePrice(cleanPrice);

        return FixedRateBondHelper(handlePrice, settlementDays, faceAmount, schedule, std::vector<double>{coupon}, couponDayCounter);
    }

}  // namespace QuantLibParser

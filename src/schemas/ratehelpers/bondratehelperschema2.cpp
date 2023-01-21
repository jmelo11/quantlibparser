#include <qlp/parser.hpp>
#include <qlp/schemas/commonschemas.hpp>
#include <qlp/schemas/ratehelpers/bondratehelperschema2.hpp>

namespace QuantLibParser {
    template <>
    void Schema2<QuantLib::FixedRateBondHelper>::initSchema() {
        loader("bondratehelper.schema.json", mySchema_);
    };

    template <>
    void Schema2<QuantLib::FixedRateBondHelper>::initDefaultValues(){

    };

    template <>
    template <>
    QuantLib::FixedRateBondHelper Schema2<QuantLib::FixedRateBondHelper>::makeObj(const json& params, PriceGetter& priceGetter) {
        json data = validate(params);

        QuantLib::Calendar calendar                = parse<QuantLib::Calendar>(data.at("CALENDAR"));
        QuantLib::BusinessDayConvention convention = parse<QuantLib::BusinessDayConvention>(data.at("CONVENTION"));
        QuantLib::Frequency frequency              = parse<QuantLib::Frequency>(data.at("FREQUENCY"));
        QuantLib::Period tenor                     = parse<QuantLib::Period>(data.at("TENOR"));
        QuantLib::DayCounter couponDayCounter      = parse<QuantLib::DayCounter>(data.at("COUPONDAYCOUNTER"));
        QuantLib::DayCounter irrDayCounter         = parse<QuantLib::DayCounter>(data.at("IRRDAYCOUNTER"));

        double settlementDays = data.at("SETTLEMENTDAYS");
        double faceAmount     = data.at("FACEAMOUNT");
        double coupon         = data.at("COUPON");

        QuantLib::Date startDate = parse<Date>(data.at("STARTDATE"));
        QuantLib::Date endDate;
        if (data.find("ENDDATE") != data.end()) {
            endDate = parse<Date>(data.at("ENDDATE"));
        } else {
            endDate = startDate + tenor;
        }

        /* coupon rate */
        QuantLib::InterestRate couponRate(coupon, couponDayCounter, QuantLib::Compounding::Simple, QuantLib::Frequency::Annual);
        std::vector<QuantLib::InterestRate> coupons{couponRate};
        auto RATE = priceGetter(params.at("RATE"), params.at("RATETICKER"));

        QuantLib::Schedule schedule =
            QuantLib::MakeSchedule().from(startDate).to(endDate).withTenor(tenor).withFrequency(frequency).withCalendar(calendar).withConvention(
                convention);

        QuantLib::FixedRateBond bond(settlementDays, faceAmount, schedule, coupons);
        boost::shared_ptr<QuantLib::SimpleQuote> cleanPrice(boost::make_shared<SimpleQuote>(
            bond.cleanPrice(RATE->value(), irrDayCounter, QuantLib::Compounding::Compounded, QuantLib::Frequency::Annual)));
        QuantLib::Handle<QuantLib::Quote> handlePrice(cleanPrice);

        return FixedRateBondHelper(handlePrice, settlementDays, faceAmount, schedule, std::vector<double>{coupon}, couponDayCounter);
    }

}  // namespace QuantLibParser

#ifndef E4E9B4BF_865E_4019_95EB_14FB177F2231
#define E4E9B4BF_865E_4019_95EB_14FB177F2231

#include <ql/currencies/all.hpp>
#include <ql/indexes/all.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/time/calendars/all.hpp>
#include <ql/time/date.hpp>
#include <ql/time/daycounters/actual360.hpp>
#include <ql/time/daycounters/actual365fixed.hpp>
#include <ql/time/daycounters/thirty360.hpp>
#include <ql/utilities/dataparsers.hpp>
#include <qlp/detail/macros.hpp>

namespace QuantLibParser {
    using namespace QuantLib;

    SERIALIZE_ENUM_WITH_CONVERSIONS(Currencies, (CLP)(CLF)(USD)(EUR))
    SERIALIZE_ENUM_WITH_CONVERSIONS(Compoundings, (Simple)(Compounded)(Continuous))
    SERIALIZE_ENUM_WITH_CONVERSIONS(DayCounters, (Act360)(Act365)(Thirty360))
    SERIALIZE_ENUM_WITH_CONVERSIONS(Calendars, (Chile)(NullCalendar)(UnitedStates)(Joint))
    SERIALIZE_ENUM_WITH_CONVERSIONS(TimeUnits, (Days)(Weeks)(Months)(Years))
    SERIALIZE_ENUM_WITH_CONVERSIONS(BDConventions, (Following)(Unadjusted)(ModifiedFollowing))
    SERIALIZE_ENUM_WITH_CONVERSIONS(Frequencies, (Once)(Annual)(Semiannual)(Monthly)(Quarterly)(NoFrequency))

    enum DateFormat { MIXED, SLASH, HYPHEN };


    /***
     * @brief Parses a string to a date in ISO format
     * @param date String to parse
     * @return Date
     */    
    inline std::string parseDate(const Date& date) {
        std::string day   = date.dayOfMonth() < 10 ? "0" + std::to_string(date.dayOfMonth()) : std::to_string(date.dayOfMonth());
        std::string month = date.month() < 10 ? "0" + std::to_string(date.month()) : std::to_string(date.month());
        return std::to_string(date.year()) + "-" + month + "-" + day;
    };  

    /***
     * @brief Parses a string to a date ISO format
     * @param date String to parse
     * @return Date
     */
    inline Date parseDate(const std::string& date) {
        return DateParser::parseISO(date);
    };

    inline Currency parseCurrency(const std::string& currency) {
        switch (map_Currencies.at(currency)) {
            case CLP:
                return CLPCurrency();
            case CLF:
                return CLFCurrency();
            case USD:
                return USDCurrency();
            case EUR:
                return EURCurrency();
            default:
                throw std::runtime_error("Unknown currency: " + currency);
        }
    };

    inline std::string parseCurrency(const Currency& currency) {
        return currency.name();
    };

    inline DayCounter parseDayCounter(const std::string& dayCounter) {
        switch (map_DayCounters.at(dayCounter)) {
            case Act360:
                return Actual360();
            case Act365:
                return Actual365Fixed();
            case Thirty360:
                return QuantLib::Thirty360(Thirty360::BondBasis);
            default:
                throw std::runtime_error("Unknown day counter:" + dayCounter);
        }
    };

    inline std::string parseDayCounter(DayCounter& dayCounter) {
        return dayCounter.name();
    };

    inline Compounding parseCompounding(const std::string& compounding) {
        switch (map_Compoundings.at(compounding)) {
            case Simple:
                return Compounding::Simple;
            case Compounded:
                return Compounding::Compounded;
            case Continuous:
                return Compounding::Continuous;
            default:
                throw std::runtime_error("Unknown compounding:" + compounding);
        }
    };

    inline std::string parseCompounding(Compounding& compounding) {
        switch (compounding) {
            case Compounding::Simple:
                return "Simple";
            case Compounding::Compounded:
                return "Compounded";
            default:
                throw std::runtime_error("Unknown compounding");
        }
    };

    inline Frequency parseFrequency(const std::string& frequency) {
        switch (map_Frequencies.at(frequency)) {
            case Annual:
                return Frequency::Annual;
            case Semiannual:
                return Frequency::Semiannual;
            case Monthly:
                return Frequency::Monthly;
            case Quarterly:
                return Frequency::Quarterly;
            case Once:
                return Frequency::Once;
            case NoFrequency:
                return Frequency::NoFrequency;
            default:
                throw std::runtime_error("Unknown frequency:" + frequency);
        }
    };

    inline std::string parseFrequency(Frequency& frequency) {
        switch (frequency) {
            case Frequency::Annual:
                return "Annual";
            case Frequency::Semiannual:
                return "Semiannual";
            case Frequency::Monthly:
                return "Monthly";
            case Frequency::Quarterly:
                return "Quarterly";
            case Frequency::Once:
                return "Once";
            default:
                throw std::runtime_error("Unknown frequency");
        }
    };

    inline Period parsePeriod(const std::string& period) {
        return PeriodParser::parse(period);
    }

    inline std::string parsePeriod(const Period& period) {
        return std::to_string(period.length()) + std::to_string(period.units());
    }

    inline TimeUnit parseTimeUnit(const std::string& timeUnit) {
        switch (map_TimeUnits.at(timeUnit)) {
            case Days:
                return TimeUnit::Days;
            case Weeks:
                return TimeUnit::Weeks;
            case Months:
                return TimeUnit::Months;
            case Years:
                return TimeUnit::Years;
            default:
                throw std::runtime_error("Unknown timeunit:" + timeUnit);
        }
    };

    inline Calendar parseCalendar(const std::string& calendar) {
        switch (map_Calendars.at(calendar)) {
            case UnitedStates:
                return QuantLib::UnitedStates(UnitedStates::Market::Settlement);
            case Chile:
                return QuantLib::Chile();
            case NullCalendar:
                return QuantLib::NullCalendar();
            case Joint:
                return JointCalendar(QuantLib::Chile(), QuantLib::UnitedStates(UnitedStates::Market::Settlement));
            default:
                throw std::runtime_error("Unknown calendar: " + calendar);
        }
    }

    inline std::string parseCalendar(Calendar& calendar) {
        return calendar.name();
    }

    inline BusinessDayConvention parseBusinessDayConvention(const std::string& convention) {
        switch (map_BDConventions.at(convention)) {
            case Following:
                return BusinessDayConvention::Following;
            case ModifiedFollowing:
                return BusinessDayConvention::ModifiedFollowing;
            case Unadjusted:
                return BusinessDayConvention::Unadjusted;
            default:
                throw std::runtime_error("Unknown convention: " + convention);
        }
    };
}  // namespace QuantLibParser

#endif /* E4E9B4BF_865E_4019_95EB_14FB177F2231 */

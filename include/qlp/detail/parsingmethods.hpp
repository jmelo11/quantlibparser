#ifndef E4E9B4BF_865E_4019_95EB_14FB177F2231
#define E4E9B4BF_865E_4019_95EB_14FB177F2231

#include <qlp/detail/macros.hpp>
#include <ql/currencies/all.hpp>
#include <ql/indexes/all.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/time/calendars/all.hpp>
#include <ql/time/date.hpp>
#include <ql/time/daycounters/actual360.hpp>
#include <ql/time/daycounters/actual365fixed.hpp>
#include <ql/time/daycounters/thirty360.hpp>
#include <ql/utilities/dataparsers.hpp>

namespace QuantLibParser {
    using namespace QuantLib;

    SERIALIZE_ENUM_WITH_CONVERSIONS(Currencies, (CLP)(CLF)(USD)(EUR))
    SERIALIZE_ENUM_WITH_CONVERSIONS(Compoundings, (SIMPLE)(COMPOUNDED)(CONTINUOUS))
    SERIALIZE_ENUM_WITH_CONVERSIONS(DayCounters, (ACT360)(ACT365)(THIRTY360))
    SERIALIZE_ENUM_WITH_CONVERSIONS(Calendars, (CHILE)(NULLCALENDAR)(USA)(JOINT))
    SERIALIZE_ENUM_WITH_CONVERSIONS(TimeUnits, (DAYS)(WEEKS)(MONTHS)(YEARS))
    SERIALIZE_ENUM_WITH_CONVERSIONS(BDConventions, (FOLLOWING)(UNADJUSTED)(MODIFIEDFOLLOWING))
    SERIALIZE_ENUM_WITH_CONVERSIONS(Frequencies, (ONCE)(ANNUAL)(SEMIANNUAL)(MONTHLY)(QUARTERLY)(NOFREQUENCY))

    enum DateFormat { MIXED, SLASH, HYPHEN };

    inline std::string parseDate(const Date& date, DateFormat format = DateFormat::MIXED) {
        std::string day   = date.dayOfMonth() < 10 ? "0" + std::to_string(date.dayOfMonth()) : std::to_string(date.dayOfMonth());
        std::string month = date.month() < 10 ? "0" + std::to_string(date.month()) : std::to_string(date.month());
        switch (format) {
            case MIXED:
                return day + month + std::to_string(date.year());
            case SLASH:
                return day + "/" + month + "/" + std::to_string(date.year());
            case HYPHEN:
                return day + "-" + month + "-" + std::to_string(date.year());
            default:
                return day + month + std::to_string(date.year());
        }
    };

    inline Date parseDate(const std::string& date, DateFormat format = DateFormat::MIXED) {
        int day, month, year;
        if (format == DateFormat::MIXED) {
            day   = std::stoi(date.substr(0, 2));
            month = std::stoi(date.substr(2, 2));
            year  = std::stoi(date.substr(4, 4));
        } else if (format == DateFormat::HYPHEN || format == DateFormat::SLASH) {
            day   = std::stoi(date.substr(0, 2));
            month = std::stoi(date.substr(2, 2));
            year  = std::stoi(date.substr(4, 4));
        } else {
            throw std::runtime_error("Unknown date format");
        }
        try {
            return Date(day, (Month)month, year);
        } catch (std::exception&) { throw std::runtime_error("Invalid date: " + date); }
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

    inline std::string parseCurrency(const Currency& currency) { return currency.name(); };

    inline DayCounter parseDayCounter(const std::string& dayCounter) {
        switch (map_DayCounters.at(dayCounter)) {
            case ACT360:
                return Actual360();
            case ACT365:
                return Actual365Fixed();
            case THIRTY360:
                return Thirty360(Thirty360::BondBasis);
            default:
                throw std::runtime_error("Unknown day counter:" + dayCounter);
        }
    };

    inline std::string parseDayCounter(DayCounter& dayCounter) { return dayCounter.name(); };

    inline Compounding parseCompounding(const std::string& compounding) {
        switch (map_Compoundings.at(compounding)) {
            case SIMPLE:
                return Compounding::Simple;
            case COMPOUNDED:
                return Compounding::Compounded;
            case CONTINUOUS:
                return Compounding::Continuous;
            default:
                throw std::runtime_error("Unknown compounding:" + compounding);
        }
    };

    inline std::string parseCompounding(Compounding& compounding) {
        switch (compounding) {
            case Compounding::Simple:
                return "SIMPLE";
            case Compounding::Compounded:
                return "COMPOUNDED";
            default:
                throw std::runtime_error("Unknown compounding");
        }
    };

    inline Frequency parseFrequency(const std::string& frequency) {
        switch (map_Frequencies.at(frequency)) {
            case ANNUAL:
                return Frequency::Annual;
            case SEMIANNUAL:
                return Frequency::Semiannual;
            case MONTHLY:
                return Frequency::Monthly;
            case QUARTERLY:
                return Frequency::Quarterly;
            case ONCE:
                return Frequency::Once;
            case NOFREQUENCY:
                return Frequency::NoFrequency;
            default:
                throw std::runtime_error("Unknown frequency:" + frequency);
        }
    };

    inline std::string parseFrequency(Frequency& frequency) {
        switch (frequency) {
            case Frequency::Annual:
                return "ANNUAL";
            case Frequency::Semiannual:
                return "SEMIANNUAL";
            case Frequency::Monthly:
                return "MONTHLY";
            case Frequency::Quarterly:
                return "QUARTERLY";
            case Frequency::Once:
                return "ONCE";
            default:
                throw std::runtime_error("Unknown frequency");
        }
    };

    inline Period parsePeriod(const std::string& period) { return PeriodParser::parse(period); }

    inline std::string parsePeriod(const Period& period) { return std::to_string(period.length()) + std::to_string(period.units()); }

    inline TimeUnit parseTimeUnit(const std::string& timeUnit) {
        switch (map_TimeUnits.at(timeUnit)) {
            case DAYS:
                return TimeUnit::Days;
            case WEEKS:
                return TimeUnit::Weeks;
            case MONTHS:
                return TimeUnit::Months;
            case YEARS:
                return TimeUnit::Years;
            default:
                throw std::runtime_error("Unknown timeunit:" + timeUnit);
        }
    };

    inline Calendar parseCalendar(const std::string& calendar) {
        switch (map_Calendars.at(calendar)) {
            case USA:
                return UnitedStates(UnitedStates::Market::Settlement);
            case CHILE:
                return Chile();
            case NULLCALENDAR:
                return NullCalendar();
            case JOINT:
                return JointCalendar(Chile(), UnitedStates(UnitedStates::Market::Settlement));
            default:
                throw std::runtime_error("Unknown calendar: " + calendar);
        }
    }

    inline std::string parseCalendar(Calendar& calendar) { return calendar.name(); }

    inline BusinessDayConvention parseBusinessDayConvention(const std::string& convention) {
        switch (map_BDConventions.at(convention)) {
            case FOLLOWING:
                return BusinessDayConvention::Following;
            case MODIFIEDFOLLOWING:
                return BusinessDayConvention::ModifiedFollowing;
            case UNADJUSTED:
                return BusinessDayConvention::Unadjusted;
            default:
                throw std::runtime_error("Unknown convention: " + convention);
        }
    };
}  // namespace QuantLibParser

#endif /* E4E9B4BF_865E_4019_95EB_14FB177F2231 */

#pragma once

#ifndef QLP_PARSER_HPP
#define QLP_PARSER_HPP

#include <qlp/detail/parsingmethods.hpp>
#include <boost/algorithm/string.hpp>
#include <string>

namespace QuantLibParser {

    template <typename T>
    inline T parse(const std::string& value);

    template <>
    inline int parse<int>(const std::string& value) {
        return std::stoi(value);
    }

    template <>
    inline double parse<double>(const std::string& value) {
        return std::stod(value);
    }

    template <>
    inline bool parse<bool>(const std::string& value) {
        std::string v = value;
        boost::algorithm::to_lower(v);
        if (v == "true")
            return true;
        else if (v == "false")
            return false;
        else
            throw std::invalid_argument("Invalid boolean value");
    }

    template <>
    inline Date parse<Date>(const std::string& value) {
        return parseDate(value);
    }

    template <>
    inline Currency parse<Currency>(const std::string& value) {
        return parseCurrency(value);
    }

    template <>
    inline Period parse<Period>(const std::string& value) {
        return parsePeriod(value);
    }

    template <>
    inline DayCounter parse<DayCounter>(const std::string& value) {
        return parseDayCounter(value);
    }

    template <>
    inline Calendar parse<Calendar>(const std::string& value) {
        return parseCalendar(value);
    }

    template <>
    inline BusinessDayConvention parse<BusinessDayConvention>(const std::string& value) {
        return parseBusinessDayConvention(value);
    }

    template <>
    inline Frequency parse<Frequency>(const std::string& value) {
        return parseFrequency(value);
    }

    template <>
    inline Compounding parse<Compounding>(const std::string& value) {
        return parseCompounding(value);
    }

    template <>
    inline TimeUnit parse<TimeUnit>(const std::string& value) {
        return parseTimeUnit(value);
    }
}  // namespace QuantLibParser

#endif  // !QLP_PARSER_HPP
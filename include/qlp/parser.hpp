#pragma once
#include <string>
#include <boost/algorithm/string.hpp>
#include <qlp/detail/parsingmethods.hpp>

namespace QuantLibParser {

	template<typename T>
	 T parse(const std::string& value);
	
	template<>
	 int parse<int>(const std::string& value)
	{
		return std::stoi(value);
	}

	template<>
	 double parse<double>(const std::string& value)
	{
		return std::stod(value);
	}

	template<>
	 bool parse<bool>(const std::string& value)
	{
		std::string v = value;
		boost::algorithm::to_lower(v);
		if (v == "true")
			return true;
		else if (v == "false")
			return false;
		else
			throw std::invalid_argument("Invalid boolean value");		
	}

	template<>
	 Date parse<Date>(const std::string& value)
	{
		return parseDate(value);
	}

	template<>
	 Currency parse<Currency>(const std::string& value)
	{
		return parseCurrency(value);
	}

	template<>
	 Period parse<Period>(const std::string& value)
	{
		return parsePeriod(value);
	}

	template<>
	 DayCounter parse<DayCounter>(const std::string& value)
	{
		return parseDayCounter(value);
	}

	template<>
	 Calendar parse<Calendar>(const std::string& value)
	{
		return parseCalendar(value);
	}

	template<>
	 BusinessDayConvention parse<BusinessDayConvention>(const std::string& value)
	{
		return parseBusinessDayConvention(value);
	}

	template<>
	 Frequency parse<Frequency>(const std::string& value)
	{
		return parseFrequency(value);
	}

	template<>
	 Compounding parse<Compounding>(const std::string& value)
	{
		return parseCompounding(value);
	}


	template<>
	 TimeUnit parse<TimeUnit>(const std::string& value)
	{
		return parseTimeUnit(value);
	}
}

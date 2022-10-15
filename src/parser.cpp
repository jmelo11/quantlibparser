#include <parser.hpp>
#include <detail/parsingmethods.hpp>

namespace QuantLibParser {

	template<>
	static int parse<int>(const std::string& value)
	{
		return std::stoi(value);
	}

	template<>
	static double parse<double>(const std::string& value)
	{
		return std::stod(value);
	}

	template<>
	static Date parse<Date>(const std::string& value)
	{
		return parseDate(value);
	}
	
	template<>
	static Currency parse<Currency>(const std::string& value)
	{
		return parseCurrency(value);
	}
	
	template<>
	static Period parse<Period>(const std::string& value)
	{
		return parsePeriod(value);
	}
	
	template<>
	static DayCounter parse<DayCounter>(const std::string& value)
	{
		return parseDayCounter(value);
	}
	
	template<>
	static Calendar parse<Calendar>(const std::string& value)
	{
		return parseCalendar(value);
	}
	
	template<>
	static BusinessDayConvention parse<BusinessDayConvention>(const std::string& value)
	{
		return parseBusinessDayConvention(value);
	}
	
	template<>
	static Frequency parse<Frequency>(const std::string& value)
	{
		return parseFrequency(value);
	}
	
	template<>
	static Compounding parse<Compounding>(const std::string& value)
	{
		return parseCompounding(value);
	}


	template<>
	static TimeUnit parse<TimeUnit>(const std::string& value)
	{
		return parseTimeUnit(value);
	}
}
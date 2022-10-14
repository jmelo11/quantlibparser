#pragma once

#include <ql/utilities/dataparsers.hpp>
#include <ql/time/date.hpp>
#include <ql/time/daycounters/actual360.hpp>
#include <ql/time/daycounters/actual365Fixed.hpp>
#include <ql/time/daycounters/thirty360.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/indexes/all.hpp>
#include <ql/time/calendars/all.hpp>
#include <ql/currencies/all.hpp>

namespace QuantLibParser {	
	using PeriodParser = QuantLib::PeriodParser;
	using DateParser = QuantLib::DateParser;	

	using Month = QuantLib::Month;	
	using Date = QuantLib::Date;
	using Calendar = QuantLib::Calendar;
	using Schedule = QuantLib::Schedule;
	using makeSchedule = QuantLib::MakeSchedule;
	using Period = QuantLib::Period;
	using TimeUnit = QuantLib::TimeUnit;
	using Frequency = QuantLib::Frequency;
	using BusinessDayConvention = QuantLib::BusinessDayConvention;

	using UnitedStates = QuantLib::UnitedStates;
	using Chile = QuantLib::Chile;
	using NullCalendar = QuantLib::NullCalendar;
	using JoinCalendar = QuantLib::JointCalendar;
	
	using Currency = QuantLib::Currency;
	using USDCurrency = QuantLib::USDCurrency;
	using EURCurrency = QuantLib::EURCurrency;
	using JPYCurrency = QuantLib::JPYCurrency;
	using CLPCurrency = QuantLib::CLPCurrency;
	using CLFCurrency = QuantLib::CLFCurrency;
		
	using DayCounter = QuantLib::DayCounter;
	using Act360 = QuantLib::Actual360;
	using Thirty360 = QuantLib::Thirty360;
	using Act365 = QuantLib::Actual365Fixed;
	using Compounding = QuantLib::Compounding;
}
#pragma once
#include <ql/time/date.hpp>
#include <ql/utilities/dataparsers.hpp>
#include <ql/time/schedule.hpp>
#include <ql/interestrate.hpp>

#include <ql/time/daycounters/actual360.hpp>
#include <ql/time/daycounters/actual365Fixed.hpp>
#include <ql/time/daycounters/thirty360.hpp>

#include <ql/math/interpolations/linearinterpolation.hpp>
#include <ql/math/interpolations/cubicinterpolation.hpp>

#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/termstructures/yield/piecewiseyieldcurve.hpp>
#include <ql/handle.hpp>
#include <ql/termstructures/yield/ratehelpers.hpp>
#include <ql/termstructures/yield/bondhelpers.hpp>

#include <ql/experimental/termstructures/basisswapratehelpers.hpp>
#include <qle/termstructures/crossccyfixfloatswaphelper.hpp>
#include <qle/termstructures/crossccybasisswaphelper.hpp>
#include <qle/termstructures/tenorbasisswaphelper.hpp>
#include <ql/termstructures/yield/discountcurve.hpp>
#include <ql/termstructures/yield/flatforward.hpp>	
#include <ql/termstructures/yield/oisratehelper.hpp>

#include <ql/indexes/iborindex.hpp>
#include <ql/indexes/all.hpp>

#include <ql/time/calendars/all.hpp>
#include <ql/currencies/all.hpp>

#include <ql/instruments/bonds/fixedratebond.hpp>
#include <ql/instruments/vanillaswap.hpp>
#include <qle/instruments/crossccyfixfloatswap.hpp>
#include <qle/pricingengines/crossccyswapengine.hpp>

#include <ql/pricingengines/bond/discountingbondengine.hpp>
#include <ql/pricingengines/swap/discountingswapengine.hpp>

#include <ql/cashflows/cashflows.hpp>
#include <ql/cashflows/iborcoupon.hpp>
#include <ql/cashflows/simplecashflow.hpp>

namespace QuantLibParser {
	
	/*
	* setting
	*/
	
	using Settings = QuantLib::Settings;
	using PeriodParser = QuantLib::PeriodParser;

	/*
	* Instruments & engines
	*/
	using CashFlow = QuantLib::CashFlow;
	using SimpleCashFlow = QuantLib::SimpleCashFlow;
	
	using Leg = QuantLib::Leg;
	using IborLeg = QuantLib::IborLeg;
	using FixedRateBond = QuantLib::FixedRateBond;
	using VanillaSwap = QuantLib::VanillaSwap;
	using Swap = QuantLib::Swap;
	using SwapEngine = QuantLib::DiscountingSwapEngine;
	using BondEngine = QuantLib::DiscountingBondEngine;
	using CrossEngine = QuantExt::CrossCcySwapEngine;
	using CrossCcyFixFloatSwap = QuantExt::CrossCcyFixFloatSwap;
	/*
	* Cashflows	
	*/

	using Cashflows = QuantLib::CashFlows;
	
	/*
	* Date and time
	*/
		
	using Month = QuantLib::Month;	
	using Date = QuantLib::Date;
	using DateParser = QuantLib::DateParser;	
	using Calendar = QuantLib::Calendar;
	using Schedule = QuantLib::Schedule;
	using makeSchedule = QuantLib::MakeSchedule;
	using Period = QuantLib::Period;
	using TimeUnit = QuantLib::TimeUnit;
	using Frequency = QuantLib::Frequency;
	using BusinessDayConvention = QuantLib::BusinessDayConvention;

	/*
	* Calendar
	*/
	
	using UnitedStates = QuantLib::UnitedStates;
	using Chile = QuantLib::Chile;
	using NullCalendar = QuantLib::NullCalendar;
	using JoinCalendar = QuantLib::JointCalendar;
	
	/*
	* Currencies 
	*/
	
	using Currency = QuantLib::Currency;
	using USDCurrency = QuantLib::USDCurrency;
	using EURCurrency = QuantLib::EURCurrency;
	using JPYCurrency = QuantLib::JPYCurrency;
	using CLPCurrency = QuantLib::CLPCurrency;
	using CLFCurrency = QuantLib::CLFCurrency;
	using NullCurrency = QuantLib::NGNCurrency;
		
	/*
	* Rates
	*/

	using InterestRate = QuantLib::InterestRate;
	using DayCounter = QuantLib::DayCounter;
	using Act360 = QuantLib::Actual360;
	using Thirty360 = QuantLib::Thirty360;
	using Act365 = QuantLib::Actual365Fixed;
	using Compounding = QuantLib::Compounding;

	/*
	* Interpolation
	*/

	using Linear = QuantLib::Linear;
	using Cubic = QuantLib::Cubic;
	using LogLinear = QuantLib::LogLinear;
	using LogCubic = QuantLib::LogCubic;
	
	using Interpolation = QuantLib::Interpolation;

	/*
	* TermStructure
	*/
	
	using YieldTermStructure = QuantLib::YieldTermStructure;	
	
	template <class DataType, class Interpol>
	using PiecewiseYieldCurve = QuantLib::PiecewiseYieldCurve<DataType, Interpol>;
	
	template<class Interpol>
	using InterpolatedDiscountCurve = QuantLib::InterpolatedDiscountCurve<Interpol>;
	
	using FlatForward = QuantLib::FlatForward;

	using RateHelper = QuantLib::RateHelper;
	
	template<typename T>
	using Handle = QuantLib::Handle<T>;

	template<typename T>
	using RelinkableHandle = QuantLib::RelinkableHandle<T>;
	using Quote = QuantLib::Quote;
	using SimpleQuote = QuantLib::SimpleQuote;
	using SwapIndex = QuantLib::SwapIndex;
	using OvernightIndex = QuantLib::OvernightIndex;
	using IborIndex = QuantLib::IborIndex;
	
	/*
	* DataTypes
	*/
	using Discount = QuantLib::Discount;
	using ForwardRate = QuantLib::ForwardRate;
	using ZeroYield = QuantLib::ZeroYield;

	
	/*
	* Rate helpers
	*/
	//derivates
	using SwapRateHelper = QuantLib::SwapRateHelper;
	using FxSwapRateHelper = QuantLib::FxSwapRateHelper;
	
	using OISRateHelper = QuantLib::OISRateHelper;
	
	using IborIborBasisSwapRateHelper = QuantLib::IborIborBasisSwapRateHelper;
	using OvernightIborBasisSwapRateHelper = QuantLib::OvernightIborBasisSwapRateHelper;
	using CrossCcyFixFloatSwapHelper = QuantExt::CrossCcyFixFloatSwapHelper;
	using CrossCcyBasisSwapHelper = QuantExt::CrossCcyBasisSwapHelper;
	using TenorBasisSwapHelper = QuantExt::TenorBasisSwapHelper;
	//using ConstNotionalCrossCurrencyBasisSwapRateHelper = QuantLib::ConstNotionalCrossCurrencyBasisSwapRateHelper;
	
	//fixed rate helpers
	using DepositRateHelper = QuantLib::DepositRateHelper;
	using FixedRateBondHelper = QuantLib::FixedRateBondHelper;
	using CPIBondHelper = QuantLib::CPIBondHelper;
	
	/*
	* Instruments
	*/	
	using FixedRateBond = QuantLib::FixedRateBond;
}
#pragma once

#include <schemas/termstructures/bootstrapcurveschema.hpp>
#include <schemas/ratehelpers/depositratehelperschema.hpp>
#include <schemas/ratehelpers/bondratehelperschema.hpp>
#include <schemas/ratehelpers/fxswapratehelperschema.hpp>
#include <schemas/ratehelpers/swapratehelperschema.hpp>
#include <schemas/ratehelpers/oisratehelperschema.hpp>
#include <schemas/ratehelpers/tenorbasisratehelperschema.hpp>
#include <schemas/ratehelpers/fixfloatxccyratehelperschema.hpp>
#include <schemas/ratehelpers/xccybasisratehelperschema.hpp>
#include <schemas/commonschemas.hpp>

namespace QuantLibParser
{
	template <>
	void Schema<QuantLib::PiecewiseYieldCurve<QuantLib::LogLinear, QuantLib::Discount>>::initSchema()
	{
		using namespace QuantExt;
		using namespace QuantLib;
		
		json base = R"({
            "title": "Bootstrap Curve Schema",
            "properties": {},			
            "required": ["NAME", "ENABLEEXTRAPOLATION", "RATEHELPERS", "TYPE"]
        })"_json;

		json ratehelpers = R"({
			"type": "array",
			"items": {
				"anyOf": []
			}
		})"_json;

		base["properties"] = baseCurveSchema;
		
		Schema<DepositRateHelper> depositHelperSchema;
		Schema<FixedRateBondHelper> bondHelperSchema;
		Schema<FxSwapRateHelper> fxSwapHelperSchema;
		Schema<SwapRateHelper> swapHelperSchema;
		Schema<OISRateHelper> oisHelperSchema;
		Schema<TenorBasisSwapHelper> tenorBasisHelperSchema;
		Schema<CrossCcyBasisSwapHelper> xccyBasisHelperSchema;
		Schema<CrossCcyFixFloatSwapHelper> xccyFixFloatHelperSchema;
		
		ratehelpers["items"]["anyOf"].emplace_back(depositHelperSchema.schema());
		ratehelpers["items"]["anyOf"].emplace_back(bondHelperSchema.schema());
		ratehelpers["items"]["anyOf"].emplace_back(fxSwapHelperSchema.schema());
		ratehelpers["items"]["anyOf"].emplace_back(swapHelperSchema.schema());
		ratehelpers["items"]["anyOf"].emplace_back(oisHelperSchema.schema());
		ratehelpers["items"]["anyOf"].emplace_back(tenorBasisHelperSchema.schema());
		ratehelpers["items"]["anyOf"].emplace_back(xccyBasisHelperSchema.schema());
		ratehelpers["items"]["anyOf"].emplace_back(xccyFixFloatHelperSchema.schema());
		
		mySchema_ = base;
	}

	template<>
	void Schema<QuantLib::PiecewiseYieldCurve<QuantLib::LogLinear, QuantLib::Discount>>::initDefaultValues()
	{
		myDefaultValues_["ENABLEEXTRAPOLATION"] = true;
		myDefaultValues_["DAYCOUNTER"] = "ACT360";
	}

}
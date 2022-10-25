#include <qlp/schemas/ratehelpers/fxswapratehelperschema.hpp>

namespace QuantLibParser
{
    template <>
    void Schema<QuantLib::FxSwapRateHelper>::initSchema()
    {
        json base = R"({
            "title": "FX Swap Rate Helper Schema",
            "properties": {},
            "required": ["TYPE", "FXPOINTS", "FXPOINTSTICKER", "FXSPOTTICKER", "FXSPOT"]
        })"_json;

        base["properties"]["FXSPOT"] = priceSchema;
        base["properties"]["FXSPOTTICKER"] = tickerSchema;
        base["properties"]["FXPOINTS"] = priceSchema;
        base["properties"]["FXPOINTSTICKER"] = tickerSchema;
		base["properties"]["ENDDATE"] = dateSchema;
        base["properties"]["TENOR"] = tenorSchema;
        base["properties"]["TYPE"] = rateHelperTypeSchema;
        base["properties"]["ENDOFMONTH"] = eomSchema;
        base["properties"]["CONVENTION"] = conventionSchema;
        base["properties"]["CALENDAR"] = calendarSchema;
        base["properties"]["FIXINGDATS"] = fixingDaysSchema;
        base["properties"]["BASECURRENCYCOLLATERAL"] = isBaseCurrencySchema;
		base["properties"]["COLLATERALCURVE"] = curveNameSchema;
        
        mySchema_ = base;
    }

    template <>
    void Schema<QuantLib::FxSwapRateHelper>::initDefaultValues()
    {
        myDefaultValues_["CALENDAR"] = "NULLCALENDAR";
        myDefaultValues_["FIXINGDAYS"] = 0;
        myDefaultValues_["ENDOFMONTH"] = false;
        myDefaultValues_["DAYCOUNTER"] = "ACT360";
        myDefaultValues_["CONVENTION"] = "UNADJUSTED";
    }
	
    template class Schema<QuantLib::FxSwapRateHelper>;
}
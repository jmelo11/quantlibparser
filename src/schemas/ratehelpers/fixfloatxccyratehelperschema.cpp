
#include <qlp/schemas/ratehelpers/fixfloatxccyratehelperschema.hpp>

namespace QuantLibParser
{
    template <>
    void Schema<QuantExt::CrossCcyFixFloatSwapHelper>::initSchema()
    {
        json base = R"({
            "title": "Xccy Rate Helper Schema",
            "properties": {},
            "required": ["TYPE", "RATE", "RATETICKER", "FXSPOT", "FXSPOTTICKER", "TENOR", "CURRENCY", "INDEX"]
        })"_json;

        base["properties"]["DAYCOUNTER"] = dayCounterSchema;
        base["properties"]["CALENDAR"] = calendarSchema;
        base["properties"]["CONVENTION"] = conventionSchema;
        base["properties"]["ENDOFMONTH"] = eomSchema;
		base["properties"]["FREQUENCY"] = frequencySchema;
        base["properties"]["SETTLEMENTDAYS"] = fixingDaysSchema;
		base["properties"]["SPREAD"] = priceSchema;
		base["properties"]["DISCOUNTINGCURVE"] = curveNameSchema;
		base["properties"]["RATE"] = priceSchema;
		base["properties"]["RATETICKER"] = tickerSchema;
        base["properties"]["FXSPOT"] = priceSchema;
        base["properties"]["FXSPOTTICKER"] = tickerSchema;
        base["properties"]["INDEX"] = curveNameSchema;
		base["properties"]["CURRENCY"] = currencySchema;
        base["properties"]["TYPE"] = rateHelperTypeSchema;
        base["properties"]["TENOR"] = tenorSchema;
		              
        mySchema_ = base;
    }

    template <>
    void Schema<QuantExt::CrossCcyFixFloatSwapHelper>::initDefaultValues()
    {
		myDefaultValues_["DAYCOUNTER"] = "ACT360";
        myDefaultValues_["CALENDAR"] = "NULLCALENDAR";
        myDefaultValues_["CONVENTION"] = "UNADJUSTED";
        myDefaultValues_["SETTLEMENTDAYS"] = 0;
        myDefaultValues_["ENDOFMONTH"] = false;
        myDefaultValues_["FREQUENCY"] = "SEMIANNUAL";
		myDefaultValues_["SPREAD"] = 0.0;				
    }

	template class Schema<QuantExt::CrossCcyFixFloatSwapHelper>;
}
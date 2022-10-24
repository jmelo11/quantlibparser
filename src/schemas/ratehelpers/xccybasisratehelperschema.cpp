#pragma once
#include <qlp/schemas/ratehelpers/xccybasisratehelperschema.hpp>

namespace QuantLibParser
{
    template <>
    void Schema<QuantExt::CrossCcyBasisSwapHelper>::initSchema()
    {
        json base = R"({
            "title": "Xccy Basis Rate Helper Schema",
            "properties": {},
            "required": ["TYPE", "SPREAD", "SPREADTICKER", "FXSPOT", "FXSPOTTICKER", "FLATINDEX", "SPREADINDEX" ]
        })"_json;

        base["properties"]["CALENDAR"] = calendarSchema;
        base["properties"]["CONVENTION"] = conventionSchema;
        base["properties"]["ENDOFMONTH"] = eomSchema;
		base["properties"]["FLATISDOMESTIC"] = eomSchema;
        base["properties"]["SETTLEMENTDAYS"] = fixingDaysSchema;
        
        base["properties"]["SPREAD"] = priceSchema;
        base["properties"]["SPREADTICKER"] = tickerSchema;

        base["properties"]["FLATDISCOUNTINGCURVE"] = curveNameSchema;
        base["properties"]["SPREADDISCOUNTINGCURVE"] = curveNameSchema;

        base["properties"]["FXSPOT"] = priceSchema;
        base["properties"]["FXSPOTTICKER"] = tickerSchema;

		base["properties"]["FLATINDEX"] = curveNameSchema;
        base["properties"]["SPREADINDEX"] = curveNameSchema;
		
        base["properties"]["TENOR"] = tenorSchema;
        base["properties"]["TYPE"] = rateHelperTypeSchema;
        
        mySchema_ = base;
    }

    template <>
    void Schema<QuantExt::CrossCcyBasisSwapHelper>::initDefaultValues()
    {
        myDefaultValues_["CALENDAR"] = "NULLCALENDAR";
		myDefaultValues_["CONVENTION"] = "MODIFIEDFOLLOWING";
        myDefaultValues_["ENDOFMONTH"] = false;
        myDefaultValues_["FLATISDOMESTIC"] = true;
        myDefaultValues_["SETTLEMENTDAYS"] = 0;
   
    }

	template class Schema<QuantExt::CrossCcyBasisSwapHelper>;
}
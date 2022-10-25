#include <qlp/schemas/ratehelpers/tenorbasisratehelperschema.hpp>

namespace QuantLibParser
{
    template <>
    void Schema<QuantExt::TenorBasisSwapHelper>::initSchema()
    {
        json base = R"({
            "title": "Tenor Basis Swap Rate Helper Schema",
            "properties": {},
            "required": ["TYPE", "SPREAD", "SPREADTICKER", "SHORTINDEX", "LONGINDEX", "TENOR"]
        })"_json;

        base["properties"]["SPREAD"] = priceSchema;
        base["properties"]["SPREADTICKER"] = tickerSchema;
        base["properties"]["SHORTINDEX"] = curveNameSchema;
        base["properties"]["LONGINDEX"] = curveNameSchema;
        base["properties"]["TENOR"] = tenorSchema;
        base["properties"]["SPREADONSHORT"] = eomSchema;
        base["properties"]["SHORTPAYTENOR"] = tenorSchema;
        base["properties"]["TYPE"] = rateHelperTypeSchema;
		base["properties"]["DISCOUNTINGCURVE"] = curveNameSchema;
              
        mySchema_ = base;
    }

    template <>
    void Schema<QuantExt::TenorBasisSwapHelper>::initDefaultValues()
    {
        myDefaultValues_["SPREADONSHORT"] = true;       
    }

	template class Schema<QuantExt::TenorBasisSwapHelper>;
}
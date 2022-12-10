#ifndef A41B4609_6780_4032_8436_DC2C44D02812
#define A41B4609_6780_4032_8436_DC2C44D02812

#include <nlohmann/json.hpp>

namespace QuantLibParser {
    using json = nlohmann::json;

    static json rateHelperTypeSchema = R"({
        "type": "string",
        "description": "Type of rate helper",
        "enum": ["DEPOSIT", "BOND", "FXSWAP", "XCCY","XCCYBASIS","SWAP","OIS","TENORBASIS"]
    })"_json;

    static json interpolationTypeSchema = R"({
        "type": "string",
        "description": "Type of interpolation",
        "enum": ["LINEAR", "CUBIC", "LOGLINEAR"]
    })"_json;

    static json indexTypesSchema = R"({
        "type":"string",
        "description": "Index types",
        "enum": ["OVERNIGHT", "IBOR"]
    })"_json;

    static json curveTypeSchema = R"({
        "type": "string",
        "description": "Type of curve",
        "enum": ["PIECEWISE", "DISCOUNT", "FLATFORWARD"]
    })"_json;

    static json enableExtrapolationSchema = R"({             
        "type": "boolean",
        "description": "Enable extrapolation"								              
    })"_json;

    static json curveNameSchema = R"({
    "type": "string",
		"description": "Name of the curve"
	})"_json;

    static json isBaseCurrencySchema = R"({
    "type": "boolean",
    "description": "Is the currency the base currency"
    })"_json;

    static json priceOrTickerSchema = R"({
        "oneOf": [
            { "type": "number"},
            { "type": "string"}
        ],
        "description": "ticker or price/rate value"
    })"_json;

    static json priceSchema = R"({
        "type": "number",
        "description": "price/rate value"
    })"_json;

    static json dayCounterSchema = R"({
      "type": "string",
      "description": "day counter",
      "example": "ACT360",
      "enum": [
        "ACT360",
        "ACT365",
        "THIRTY360"
      ]
    })"_json;

    static json compoundingSchema = R"({
      "type": "string",
      "description": "compounding",
      "example": "SIMPLE",
      "enum": ["SIMPLE","COMPOUNDED","CONTINUOUS"]
    })"_json;

    static json dateSchema = R"({
        "type": "string",
        "description": "date",
        "pattern": "^\\d{8}$",
        "example": "28092025"        
    })"_json;

    static json frequencySchema = R"({
      "type": "string",
      "description": "frequency",
      "example": "ANNUAL",
      "enum": ["ANNUAL","SEMIANNUAL","QUARTERLY","MONTHLY","ONCE","NOFREQUENCY"]
    })"_json;

    static json calendarSchema = R"({
      "type": "string",
      "description": "calendar",
      "example": "NULLCALENDAR",
      "enum": ["NULLCALENDAR","CHILE","USA","JOINT"]
    })"_json;

    static json conventionSchema = R"({
      "type": "string",
      "description": "convention",
      "example": "UNADJUSTED",
      "enum": ["FOLLOWING","MODIFIEDFOLLOWING","UNADJUSTED"]
    })"_json;

    static json currencySchema = R"({
      "type": "string",
      "description": "convention",
      "example": "UNADJUSTED",
      "enum": ["CLP","USD","EUR","CLF"]
    })"_json;

    static json fixingDaysSchema = R"({
        "anyOf": [
            {
                "type": "integer",             
                "minimum": 0,
                "example": 2
            },
            {
                "type": "number",             
                "minimum": 0,
                "example": 2.0
            }
        ],
        "description": "fixing/settlement days"
     })"_json;

    static json eomSchema = R"({
        "type": "boolean",
        "description": "end of month",
        "example": true
    })"_json;

    static json faceAmountSchema = R"({
        "type": "number", 
        "description": "face amount",
        "minimum": 0,
        "example": 100
        })"_json;

    static json tickerSchema = R"({
        "type": "string", 
        "description": "ticker",
        "example": "CLP Currency"
        })"_json;

    static json tenorSchema = R"({
        "type": "string", 
        "description": "tenor",
        "pattern": "^\\d+[YWDM]$",
        "example": "1Y"
        })"_json;

    static json baseRateSchema = {{"title", "Base Rate Schema"},
                                  {"properties",
                                   {
                                       {"VALUE", {{"type", "number"}, {"description", "Base rate"}}},
                                       {"DAYCOUNTER", dayCounterSchema},
                                       {"COMPOUNDING", compoundingSchema},
                                       {"FREQUENCY", frequencySchema},
                                   }},
                                  {"required", json::array({"VALUE", "DAYCOUNTER", "COMPOUNDING", "FREQUENCY"})}};

}  // namespace QuantLibParser

#endif /* A41B4609_6780_4032_8436_DC2C44D02812 */

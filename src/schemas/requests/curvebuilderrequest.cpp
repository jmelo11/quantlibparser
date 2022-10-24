#pragma once
#include <qlp/schemas/requests/curvebuilderrequest.hpp>
#include <qlp/schemas/commonschemas.hpp>

namespace QuantLibParser
{
    template <>
    void Schema<CurveBuilderRequest>::initSchema()
    {
        json base = R"({
            "title": "Curve Builder Request Schema",
            "properties": {},
            "required": ["REFDATE", "CURVES", "INDICES"]
        })"_json;

        base["properties"]["REFDATE"] = dateSchema;
        base["properties"]["CURVES"] = R"({               
                    "type":"array", 
                    "items":{ "type": "object" }
        })"_json;

		base["properties"]["INDICES"] = R"({               
					"type":"array", 
					"items":{ "type": "object" }     
        })"_json;
		
        mySchema_ = base;
    };

    template <>
    void Schema<CurveBuilderRequest>::initDefaultValues()
    {
       
    };

	template class Schema<CurveBuilderRequest>;
}
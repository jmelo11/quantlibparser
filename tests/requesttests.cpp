#include "pch.h"
#include <qlp/schemas/requests/curvebuilderrequest.hpp>
#include <qlp/schemas/requests/updatequoterequest.hpp>

using namespace QuantLibParser;

TEST(CurveBuilder, Requests) {
	json data = R"({
		"REFDATE":"28022022",
		"CURVES": [{}],
		"INDICES":[{}]
	})"_json;
	Schema<CurveBuilderRequest> schema;
	EXPECT_NO_THROW(schema.validate(data));	
}

TEST(UpdateQuote, Requests) {
	json data = R"([		
			{
				"NAME": "CLP CURRENCY",
				"VALUE": 800
			}		
	])"_json;
	
	Schema<UpdateQuoteRequest> schema;
	EXPECT_NO_THROW(schema.validate(data));
}
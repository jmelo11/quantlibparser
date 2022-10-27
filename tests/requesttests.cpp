#include "pch.h"
#include <qlp/schemas/requests/curvebuilderrequest.hpp>
#include <qlp/schemas/requests/updatequoterequest.hpp>
#include <qlp/schemas/requests/zeroratesrequest.hpp>
#include <qlp/schemas/requests/forwardratesrequest.hpp>
#include <qlp/schemas/requests/discountfactorsrequest.hpp>

using namespace QuantLibParser;

TEST(CurveBuilder, Requests) {
	json data = R"({
		"REFDATE":"28022022",
		"CURVES": [{}],
		"INDEXES":[{}]
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

TEST(DiscountFactors, Requests) {
	json data = R"({
		"REFDATE":"24082022",
		"CURVE":"ICP_ICAP",		
		"DATES":["24022023"]
	})"_json;

	Schema<DiscountFactorsRequest> schema;
	EXPECT_NO_THROW(schema.validate(data));
}

TEST(ZeroRates, Requests) {
	json data = R"({
		"REFDATE":"24082022",
		"CURVE":"ICP_ICAP",
		"DAYCOUNTER":"ACT360",
		"COMPOUNDING":"SIMPLE",
		"DATES":["24022023"]
	})"_json;

	Schema<ZeroRatesRequests> schema;
	EXPECT_NO_THROW(schema.validate(data));
}

TEST(ForwardRates, Requests) {
	json data = R"({
		"REFDATE":"24082022",
		"CURVE":"ICP_ICAP",
		"DAYCOUNTER":"ACT360",
		"COMPOUNDING":"SIMPLE",
		"DATES":[["24022023","24022024"]]
	})"_json;

	Schema<ForwardRatesRequest> schema;
	EXPECT_NO_THROW(schema.validate(data));
}
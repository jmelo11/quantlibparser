#include "pch.hpp"
#include <qlp/schemas/requests/curvebuilderrequest.hpp>
#include <qlp/schemas/requests/discountfactorsrequest.hpp>
#include <qlp/schemas/requests/forwardratesrequest.hpp>
#include <qlp/schemas/requests/updatequoterequest.hpp>
#include <qlp/schemas/requests/zeroratesrequest.hpp>

using namespace QuantLibParser;

TEST(Requests, CurveBuilder) {
    json data = R"({
		"REFDATE":"28022022",
		"CURVES": [{}],
		"INDEXES":[{}]
	})"_json;
    Schema<CurveBuilderRequest> schema;
    EXPECT_NO_THROW(schema.validate(data));
}

TEST(Requests, UpdateQuote) {
    json data = R"([		
		{
			"NAME": "CLP CURRENCY",
			"VALUE": 800
		}		
	])"_json;

    Schema<UpdateQuoteRequest> schema;
    EXPECT_NO_THROW(schema.validate(data));
}

TEST(Requests, DiscountFactors) {
    json data = R"({
		"REFDATE":"24082022",
		"CURVE":"ICP_ICAP",		
		"DATES":["24022023"]
	})"_json;

    Schema<DiscountFactorsRequest> schema;
    EXPECT_NO_THROW(schema.validate(data));
}

TEST(Requests, ZeroRates) {
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

TEST(Requests, ForwardRates) {
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
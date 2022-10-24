#include "pch.h"
#include <nlohmann/json-schema.hpp>
#include <qlp/schemas/commonschemas.hpp>

using nlohmann::json_schema::json_validator;
using json = nlohmann::json;
using namespace QuantLibParser;

TEST(Daycounter, TestCommonSchemas) {		
	json base = R"({
            "title": "Day counter schema test",
            "properties": {},
            "required": ["DAYCOUNTER"]
        })"_json;
	
	base["properties"]["DAYCOUNTER"] = dayCounterSchema;

	json_validator validator;
	validator.set_root_schema(base);	

	json test = R"(
	{
		"DAYCOUNTER": "ACT360"
	}
	)"_json;
		
	EXPECT_NO_THROW(validator.validate(test));

	test = R"(
	{
		"DAYCOUNTER": "OTHER"
	}
	)"_json;
	
	EXPECT_ANY_THROW(validator.validate(test));

	test = R"(
	{
		"OTHERNAME": "ACT360"
	}
	)"_json;
	
	EXPECT_ANY_THROW(validator.validate(test));

}

TEST(Date, TestCommonSchemas) {
	json base = R"({
            "title": "Day counter schema test",
            "properties": {},
            "required": ["DATES"]
        })"_json;

	base["properties"]["DATES"] = dateSchema;
	
	json test = R"(
	{
		"DATES": "28092022"
	}
	)"_json;

	json_validator validator;
	validator.set_root_schema(base);

	EXPECT_NO_THROW(validator.validate(test));
	
	test = R"(
	{
		"DATES": "28-09-2022"
	}
	)"_json;

	EXPECT_ANY_THROW(validator.validate(test));
}

TEST(Tenor, TestCommonSchemas) {
	json base = R"({
            "title": "Day counter schema test",
            "properties": {},
            "required": ["TENOR"]
        })"_json;

	base["properties"]["TENOR"] = tenorSchema;

	json_validator validator;
	validator.set_root_schema(base);

	json test = R"(
	{
		"TENOR": "1Y"
	}
	)"_json;

	EXPECT_NO_THROW(validator.validate(test));

	test = R"(
	{
		"TENOR": "1P"
	}
	)"_json;

	EXPECT_ANY_THROW(validator.validate(test));

	test = R"(
	{
		"TENOR": "50Y"
	}
	)"_json;

	EXPECT_NO_THROW(validator.validate(test));
	
}

TEST(PriceOrTicker, TestCommonSchemas) {
	json base = R"({
            "title": "Price or ticker schema test",
            "properties": {},
            "required": ["PRICE"]
        })"_json;

	base["properties"]["PRICE"] = priceOrTickerSchema;
	
	json test = R"(
	{
		"PRICE": 0.03
	}
	)"_json;

	json_validator validator;
	validator.set_root_schema(base);
	EXPECT_NO_THROW(validator.validate(test));

	test = R"(
	{
		"PRICE": "someticker"
	}
	)"_json;

	EXPECT_NO_THROW(validator.validate(test));

	test = R"(
	{
		"PRICE": 1
	}
	)"_json;

	EXPECT_NO_THROW(validator.validate(test));
	
}
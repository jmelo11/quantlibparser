#include "pch.hpp"
#include <qlp/parser.hpp>

using namespace QuantLib;
using namespace QuantLibParser;

TEST(Date, Parser) {
    std::string date = "01022022";
    Date qlDate      = parse<Date>(date);
    EXPECT_EQ(qlDate, Date(1, February, 2022));
}
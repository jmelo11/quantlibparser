#include <schemas/schema.hpp>
#include <schemas/commonschemas.hpp>
#include <ql/termstructures/yield/discountcurve.hpp>

namespace QuantLibParser
{
	template <>
	void Schema<QuantLib::DiscountCurve> ::initSchema();

	template<>
	void Schema<QuantLib::DiscountCurve>::initDefaultValues();

}
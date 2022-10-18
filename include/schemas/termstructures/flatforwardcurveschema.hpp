#include <schemas/schema.hpp>
#include <schemas/commonschemas.hpp>
#include <ql/termstructures/yield/flatforward.hpp>

namespace QuantLibParser
{
	template <>
	void Schema<QuantLib::FlatForward> ::initSchema();

	template<>
	void Schema<QuantLib::FlatForward>::initDefaultValues();

}
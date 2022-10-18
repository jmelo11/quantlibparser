#include <schemas/schema.hpp>

#include <ql/termstructures/yieldtermstructure.hpp>
#include <schemas/termstructures/bootstrapcurveschema.hpp>
#include <schemas/termstructures/discountcurveschema.hpp>
#include <schemas/termstructures/flatforwardcurveschema.hpp>

namespace QuantLibParser
{
	template <>
	void Schema<QuantLib::YieldTermStructure>::initSchema();

	template <>
	void Schema<QuantLib::YieldTermStructure>::initDefaultValues();
}
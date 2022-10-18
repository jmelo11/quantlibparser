
#include <schemas/schema.hpp>
#include <schemas/commonschemas.hpp>
#include <ql/indexes/interestrateindex.hpp>

namespace QuantLibParser
{
	template<>
	void Schema<QuantLib::InterestRateIndex>::initSchema();

	template<>
	void Schema<QuantLib::InterestRateIndex>::initDefaultValues();
}
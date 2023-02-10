#include <qlp/parser.hpp>
#include <qlp/schemas/ratehelpers/tenorbasisratehelperschema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantExt::TenorBasisSwapHelper>::initSchema() {
        mySchema_ = readJSONFile("tenorbasis.ratehelper.schema.json");
    }

    template <>
    void Schema<QuantExt::TenorBasisSwapHelper>::initDefaultValues() {
        myDefaultValues_["helperConfig"]["spreadOnShort"] = true;
    }

    template <>
    template <>
    QuantExt::TenorBasisSwapHelper Schema<QuantExt::TenorBasisSwapHelper>::makeObj(const json& params, PriceGetter& priceGetter,
                                                                                   IndexGetter& indexGetter, CurveGetter& curveGetter) {
        json data = setDefaultValues(params);
        validate(data);
        const json& helperConfig = data.at("helperConfig");
        const json& marketConfig = data.at("marketConfig");

        auto discountCurve = helperConfig.find("discountCurve") != helperConfig.end() ? curveGetter(helperConfig.at("discountCurve")) :
                                                                                        QuantLib::RelinkableHandle<QuantLib::YieldTermStructure>();
        auto shortIndex    = indexGetter(helperConfig.at("shortIndex"));
        auto longIndex     = indexGetter(helperConfig.at("longIndex"));

        /*check if any of the curves can be build, otherwise fail*/
        if (shortIndex->forwardingTermStructure().empty() && longIndex->forwardingTermStructure().empty()) {
            auto handle = curveGetter(helperConfig.at("shortIndex"));
            if (handle.empty()) {
                handle    = curveGetter(helperConfig.at("longIndex"));
                longIndex = indexGetter(helperConfig.at("longIndex"));
            } else {
                shortIndex = indexGetter(helperConfig.at("shortIndex"));
            }
        }
        QuantLib::Period tenor = parse<QuantLib::Period>(helperConfig.at("tenor"));

        QuantLib::Period shortPayTenor =
            helperConfig.find("shortPayTenor") != helperConfig.end() ? parse<QuantLib::Period>(helperConfig.at("shortPayTenor")) : tenor;

        bool spreadOnShort = helperConfig.at("spreadOnShort");

        auto spreadQuote = priceGetter(marketConfig.at("spread").at("value"), marketConfig.at("spread").at("ticker"));

        QuantLib::Period sortPayTenor =
            helperConfig.find("shortPayTenor") != helperConfig.end() ? parse<QuantLib::Period>(helperConfig.at("shortPayTenor")) : QuantLib::Period();

        return QuantExt::TenorBasisSwapHelper(spreadQuote, tenor, longIndex, shortIndex, sortPayTenor, discountCurve, spreadOnShort);
    }
}  // namespace QuantLibParser
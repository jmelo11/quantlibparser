#include <qlp/parser.hpp>
#include <qlp/schemas/ratehelpers/tenorbasisratehelperschema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantExt::TenorBasisSwapHelper>::initSchema() {
        json base = R"({
            "title": "Tenor Basis Swap Rate Helper Schema",
            "properties": {},
            "required": ["TYPE", "SPREAD", "SPREADTICKER", "SHORTINDEX", "LONGINDEX", "TENOR"]
        })"_json;

        base["properties"]["SPREAD"]           = priceSchema;
        base["properties"]["SPREADTICKER"]     = tickerSchema;
        base["properties"]["SHORTINDEX"]       = curveNameSchema;
        base["properties"]["LONGINDEX"]        = curveNameSchema;
        base["properties"]["TENOR"]            = tenorSchema;
        base["properties"]["SPREADONSHORT"]    = eomSchema;
        base["properties"]["SHORTPAYTENOR"]    = tenorSchema;
        base["properties"]["TYPE"]             = rateHelperTypeSchema;
        base["properties"]["DISCOUNTINGCURVE"] = curveNameSchema;

        mySchema_ = base;
    }

    template <>
    void Schema<QuantExt::TenorBasisSwapHelper>::initDefaultValues() {
        myDefaultValues_["SPREADONSHORT"] = true;
    }

    template <>
    template <>
    QuantExt::TenorBasisSwapHelper Schema<QuantExt::TenorBasisSwapHelper>::makeObj(const json& params, PriceGetter& priceGetter,
                                                                                   IndexGetter& indexGetter, CurveGetter& curveGetter) {
        validate(params);
        json data = setDefaultValues(params);

        auto discountCurve = data.find("DISCOUNTINGCURVE") != data.end() ? curveGetter(data.at("DISCOUNTINGCURVE")) :
                                                                           QuantLib::RelinkableHandle<QuantLib::YieldTermStructure>();
        auto shortIndex    = indexGetter(params.at("SHORTINDEX"));
        auto longIndex     = indexGetter(params.at("LONGINDEX"));

        /*check if any of the curves can be build, otherwise fail*/
        if (shortIndex->forwardingTermStructure().empty() && longIndex->forwardingTermStructure().empty()) {
            auto handle = curveGetter(data.at("SHORTINDEX"));
            if (handle.empty()) {
                handle    = curveGetter(data.at("LONGINDEX"));
                longIndex = indexGetter(data.at("LONGINDEX"));
            } else {
                shortIndex = indexGetter(data.at("SHORTINDEX"));
            }
        }
        QuantLib::Period tenor = parse<QuantLib::Period>(data.at("TENOR"));

        QuantLib::Period shortPayTenor = data.find("SHORTPAYTENOR") != data.end() ? parse<QuantLib::Period>(data.at("SHORTPAYTENOR")) : tenor;

        bool spreadOnShort = data.at("SPREADONSHORT");

        double spread = data.at("SPREAD");
        boost::shared_ptr<QuantLib::Quote> spreadPtr(new QuantLib::SimpleQuote(spread));
        QuantLib::Handle<QuantLib::Quote> spreadQuote(spreadPtr);

        QuantLib::Period sortPayTenor =
            data.find("SHORTPAYTENOR") != data.end() ? parse<QuantLib::Period>(data.at("SHORTPAYTENOR")) : QuantLib::Period();

        return QuantExt::TenorBasisSwapHelper(spreadQuote, tenor, longIndex, shortIndex, sortPayTenor, discountCurve, spreadOnShort);
    }
}  // namespace QuantLibParser
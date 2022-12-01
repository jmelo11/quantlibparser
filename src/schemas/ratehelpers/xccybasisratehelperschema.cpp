#include <qlp/parser.hpp>
#include <qlp/schemas/ratehelpers/xccybasisratehelperschema.hpp>

namespace QuantLibParser {
    template <>
    void Schema<QuantExt::CrossCcyBasisSwapHelper>::initSchema() {
        json base = R"({
            "title": "Xccy Basis Rate Helper Schema",
            "properties": {},
            "required": ["TYPE", "SPREAD", "SPREADTICKER", "FXSPOT", "FXSPOTTICKER", "FLATINDEX", "SPREADINDEX" ]
        })"_json;

        base["properties"]["CALENDAR"]               = calendarSchema;
        base["properties"]["CONVENTION"]             = conventionSchema;
        base["properties"]["ENDOFMONTH"]             = eomSchema;
        base["properties"]["FLATISDOMESTIC"]         = eomSchema;
        base["properties"]["SETTLEMENTDAYS"]         = fixingDaysSchema;
        base["properties"]["SPREAD"]                 = priceSchema;
        base["properties"]["SPREADTICKER"]           = tickerSchema;
        base["properties"]["FLATDISCOUNTINGCURVE"]   = curveNameSchema;
        base["properties"]["SPREADDISCOUNTINGCURVE"] = curveNameSchema;
        base["properties"]["FXSPOT"]                 = priceSchema;
        base["properties"]["FXSPOTTICKER"]           = tickerSchema;
        base["properties"]["FLATINDEX"]              = curveNameSchema;
        base["properties"]["SPREADINDEX"]            = curveNameSchema;
        base["properties"]["TENOR"]                  = tenorSchema;
        base["properties"]["TYPE"]                   = rateHelperTypeSchema;

        mySchema_ = base;
    }

    template <>
    void Schema<QuantExt::CrossCcyBasisSwapHelper>::initDefaultValues() {
        myDefaultValues_["CALENDAR"]       = "NULLCALENDAR";
        myDefaultValues_["CONVENTION"]     = "MODIFIEDFOLLOWING";
        myDefaultValues_["ENDOFMONTH"]     = false;
        myDefaultValues_["FLATISDOMESTIC"] = true;
        myDefaultValues_["SETTLEMENTDAYS"] = 0;
    }

    template <>
    template <>
    QuantExt::CrossCcyBasisSwapHelper Schema<QuantExt::CrossCcyBasisSwapHelper>::makeObj(const json& params, PriceGetter& priceGetter,
                                                                                         IndexGetter& indexGetter, CurveGetter& curveGetter) {
        json data = setDefaultValues(params);
        validate(data);

        QuantLib::Calendar calendar                = parse<QuantLib::Calendar>(data.at("CALENDAR"));
        QuantLib::BusinessDayConvention convention = parse<QuantLib::BusinessDayConvention>(data.at("CONVENTION"));
        QuantLib::Period tenor                     = parse<QuantLib::Period>(data.at("TENOR"));

        bool endOfMonth     = data.at("ENDOFMONTH");
        bool flatIsDomestic = data.at("FLATISDOMESTIC");
        int settlementDays  = data.at("SETTLEMENTDAYS");

        auto spread = priceGetter(data.at("SPREAD"), data.at("SPREADTICKER"));

        auto flatDiscountCurve =
            data.find("FLATDISCOUNTINGCURVE") != data.end() ? curveGetter(data.at("FLATDISCOUNTINGCURVE")) : RelinkableHandle<YieldTermStructure>();

        auto spreadDiscountCurve = data.find("SPREADDISCOUNTINGCURVE") != data.end() ? curveGetter(data.at("SPREADDISCOUNTINGCURVE")) :
                                                                                       RelinkableHandle<YieldTermStructure>();
        if (flatDiscountCurve.empty() && spreadDiscountCurve.empty())
            throw std::runtime_error(
                "Either FLATDISCOUNTINGCURVE or "
                "SPREADDISCOUNTINGCURVE must be specified");

        auto fxSpot      = priceGetter(data.at("FXSPOT"), data.at("FXSPOTTICKER"));
        auto flatIndex   = indexGetter(data.at("FLATINDEX"));
        auto spreadIndex = indexGetter(data.at("SPREADINDEX"));

        return QuantExt::CrossCcyBasisSwapHelper(spread, fxSpot, settlementDays, calendar, tenor, convention, flatIndex, spreadIndex,
                                                 flatDiscountCurve, spreadDiscountCurve, endOfMonth, flatIsDomestic);
    }

}  // namespace QuantLibParser
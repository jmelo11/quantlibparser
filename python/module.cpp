#include <qlp/schemas/ratehelpers/bondratehelperschema.hpp>
#include <qlp/schemas/ratehelpers/depositratehelperschema.hpp>
#include <qlp/schemas/ratehelpers/fixfloatxccyratehelperschema.hpp>
#include <qlp/schemas/ratehelpers/fxswapratehelperschema.hpp>
#include <qlp/schemas/ratehelpers/oisratehelperschema.hpp>
#include <qlp/schemas/ratehelpers/swapratehelperschema.hpp>
#include <qlp/schemas/ratehelpers/tenorbasisratehelperschema.hpp>
#include <qlp/schemas/ratehelpers/xccybasisratehelperschema.hpp>
#include <qlp/schemas/requests/discountfactorsrequest.hpp>
#include <qlp/schemas/requests/forwardratesrequest.hpp>
#include <qlp/schemas/requests/zeroratesrequest.hpp>
#include <qlp/schemas/termstructures/bootstrapcurveschema.hpp>
#include <qlp/schemas/termstructures/discountcurveschema.hpp>
#include <qlp/schemas/termstructures/flatforwardcurveschema.hpp>
#include <qlp/schemas/termstructures/rateindexschema.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11_json/pybind11_json.hpp>

#define SchemaWithoutMaker(name)                                      \
    py::class_<Schema<name>>(m, #name)                                \
        .def(py::init<>())                                            \
        .def("validate", &Schema<name>::validate)                     \
        .def("isValid", &Schema<name>::isValid)                       \
        .def("schema", &Schema<name>::schema)                         \
        .def("addDefaultValue", &Schema<name>::addDefaultValue)       \
        .def("removeDefaultValue", &Schema<name>::removeDefaultValue) \
        .def("schema", &Schema<name>::schema)                         \
        .def("addRequired", &Schema<name>::addRequired)               \
        .def("removeRequired", &Schema<name>::removeRequired)

#define SchemaWithMaker(name) SchemaWithoutMaker(name).def("makeObj", &Schema<name>::makeObj<>)

namespace py = pybind11;
using namespace QuantLibParser;
using namespace QuantLib;
using namespace QuantExt;
using namespace std;

struct CommonSchemas {};

PYBIND11_MODULE(QuantLibParser, m) {
    m.doc() = "quantlibparser for python";  // optional module docstring

    // Rate Helpers
    SchemaWithoutMaker(FixedRateBondHelper);
    SchemaWithoutMaker(DepositRateHelper);
    SchemaWithoutMaker(CrossCcyFixFloatSwapHelper);
    SchemaWithoutMaker(FxSwapRateHelper);
    SchemaWithoutMaker(OISRateHelper);
    SchemaWithoutMaker(SwapRateHelper);
    SchemaWithoutMaker(TenorBasisSwapHelper);
    SchemaWithoutMaker(CrossCcyBasisSwapHelper);

    // curves
    SchemaWithMaker(DiscountCurve);
    SchemaWithMaker(FlatForward);
    SchemaWithoutMaker(BootstrapCurve);
    SchemaWithoutMaker(InterestRateIndex);

    // common schemas
    m.attr("RateHelperTypeSchema") = &rateHelperTypeSchema;
    m.attr("IndexTypeSchemas")     = &indexTypesSchema;
    m.attr("DayCounterTypeSchema") = &dayCounterSchema;
    m.attr("CalendarTypeSchema")   = &calendarSchema;
    m.attr("ConventionTypeSchema") = &conventionSchema;
    m.attr("FrequencyTypeSchema")  = &frequencySchema;
    m.attr("TenorSchema")          = &tenorSchema;
    m.attr("DateSchema")           = &dateSchema;
    m.attr("RateSchema")           = &baseRateSchema;

    // requests
    py::class_<Schema<DiscountFactorsRequest>>(m, "DiscountFactorsRequestSchema")
        .def(py::init<>())
        .def("validate", &Schema<DiscountFactorsRequest>::validate)
        .def("schema", &Schema<DiscountFactorsRequest>::schema);

    py::class_<Schema<ZeroRatesRequests>>(m, "ZeroRatesRequestsSchema")
        .def(py::init<>())
        .def("validate", &Schema<ZeroRatesRequests>::validate)
        .def("schema", &Schema<ZeroRatesRequests>::schema);

    py::class_<Schema<ForwardRatesRequest>>(m, "ForwardRatesRequestSchema")
        .def(py::init<>())
        .def("validate", &Schema<ForwardRatesRequest>::validate)
        .def("schema", &Schema<ForwardRatesRequest>::schema);
}

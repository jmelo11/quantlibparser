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

namespace py = pybind11;
using namespace QuantLibParser;
using namespace QuantLib;
using namespace QuantExt;
using namespace std;

using BootstrapCurveSchema = PiecewiseYieldCurve<Discount, LogLinear>;

PYBIND11_MODULE(quantlibparser, m) {
    m.doc() = "quantlibparser for python";  // optional module docstring

    // ratehelpers
    py::class_<Schema<FixedRateBondHelper>>(m, "FixedRateBondHelperSchema")
        .def(py::init<>())
        .def("validate", &Schema<FixedRateBondHelper>::validate)
        .def("schema", &Schema<FixedRateBondHelper>::schema);

    py::class_<Schema<DepositRateHelper>>(m, "DepositRateHelperSchema")
        .def(py::init<>())
        .def("validate", &Schema<DepositRateHelper>::validate)
        .def("schema", &Schema<DepositRateHelper>::schema);

    py::class_<Schema<CrossCcyFixFloatSwapHelper>>(m, "CrossCcyFixFloatSwapHelperSchema")
        .def(py::init<>())
        .def("validate", &Schema<CrossCcyFixFloatSwapHelper>::validate)
        .def("schema", &Schema<CrossCcyFixFloatSwapHelper>::schema);

    py::class_<Schema<FxSwapRateHelper>>(m, "FxSwapRateHelperSchema")
        .def(py::init<>())
        .def("validate", &Schema<FxSwapRateHelper>::validate)
        .def("schema", &Schema<FxSwapRateHelper>::schema);

    py::class_<Schema<OISRateHelper>>(m, "OISRateHelperSchema")
        .def(py::init<>())
        .def("validate", &Schema<OISRateHelper>::validate)
        .def("schema", &Schema<OISRateHelper>::schema);

    py::class_<Schema<SwapRateHelper>>(m, "SwapRateHelperSchema")
        .def(py::init<>())
        .def("validate", &Schema<SwapRateHelper>::validate)
        .def("schema", &Schema<SwapRateHelper>::schema);

    py::class_<Schema<TenorBasisSwapHelper>>(m, "TenorBasisSwapHelperSchema")
        .def(py::init<>())
        .def("validate", &Schema<TenorBasisSwapHelper>::validate)
        .def("schema", &Schema<TenorBasisSwapHelper>::schema);

    py::class_<Schema<CrossCcyBasisSwapHelper>>(m, "CrossCcyBasisSwapHelperSchema")
        .def(py::init<>())
        .def("validate", &Schema<CrossCcyBasisSwapHelper>::validate)
        .def("schema", &Schema<CrossCcyBasisSwapHelper>::schema);

    // curves
    py::class_<Schema<BootstrapCurveSchema>>(m, "BootstrapCurveSchema")
        .def(py::init<>())
        .def("validate", &Schema<BootstrapCurveSchema>::validate)
        .def("schema", &Schema<BootstrapCurveSchema>::schema);

    py::class_<Schema<FlatForward>>(m, "FlatForwardCurveSchema")
        .def(py::init<>())
        .def("validate", &Schema<FlatForward>::validate)
        .def("schema", &Schema<FlatForward>::schema);

    py::class_<Schema<InterestRateIndex>>(m, "InterestRateIndexSchema")
        .def(py::init<>())
        .def("validate", &Schema<InterestRateIndex>::validate)
        .def("schema", &Schema<InterestRateIndex>::schema);

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

#include <qlp/schemas/ratehelpers/all.hpp>
#include <qlp/schemas/termstructures/all.hpp>

#include <iostream>
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
    SchemaWithMaker(InterestRate);
    SchemaWithoutMaker(BootstrapCurve);
    SchemaWithoutMaker(IborIndex);
    SchemaWithoutMaker(OvernightIndex);

    // json validator

    m.def("schemaValidation", [](const json& schema, const json& data) {
        nlohmann::json_schema::json_validator validator;
        try {
            validator.set_root_schema(schema);  // insert root-schema
            validator.validate(data);
        } catch (const std::invalid_argument& e) { throw e; }
    });
}

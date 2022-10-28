#pragma once

#ifndef QLP_SCHEMA_HPP
#define QLP_SCHEMA_HPP

#include <nlohmann/json-schema.hpp>
#include <stdexcept>

namespace QuantLibParser {
    using json = nlohmann::json;
    using nlohmann::json_schema::json_validator;

    template <typename T>
    class Schema;

    template <typename T>
    class Schema {
       public:
        Schema() {
            initSchema();
            initDefaultValues();
            mySchema_["$schema"] = "http://json-schema.org/draft-07/schema#";
        }

        json schema() { return mySchema_; };

        void validate(const json& data) {
            json_validator validator;
            try {
                validator.set_root_schema(mySchema_);  // insert root-schema
                validator.validate(data);
            } catch (const std::exception& e) {
                std::string error = e.what();
                throw std::runtime_error("Validation of schema failed:\t" + error + "\n");
            }
        };

        json setDefaultValues(json target) {
            for (auto& [k, v] : myDefaultValues_.items()) {
                if (target.find(k) == target.end()) target[k] = v;
            }
            return target;
        };

       private:
        void initSchema();
        void initDefaultValues();

        json myDefaultValues_;
        json mySchema_;
    };
}  // namespace QuantLibParser

#endif  // QLP_SCHEMA_HPP
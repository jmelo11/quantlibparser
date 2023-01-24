#ifndef C7259EDE_8AB0_4851_B8F0_93EF8D404811
#define C7259EDE_8AB0_4851_B8F0_93EF8D404811

#include <ql/handle.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/quote.hpp>
#include <qlp/schemapath.hpp>
#include <nlohmann/json-schema.hpp>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace QuantLibParser {

    using nlohmann::json;
    using nlohmann::json_uri;
    using nlohmann::json_schema::json_validator;
    namespace ext = boost;

    using PriceGetter = std::function<QuantLib::Handle<QuantLib::Quote>(double price, const std::string& ticker)>;

    using IndexGetter = std::function<ext::shared_ptr<QuantLib::IborIndex>(const std::string& name)>;

    using CurveGetter = std::function<QuantLib::RelinkableHandle<QuantLib::YieldTermStructure>(const std::string& name)>;

    template <typename T>
    class Schema {
       public:
        /**
        Constructor that initialize the schema and default values.
        */
        Schema() {
            initSchema();
            initDefaultValues();
        }

        /**
        Getter for the json schema
        @return json
        */
        json schema() { return mySchema_; };

        /**
        Create an object of type T using data and additional arguments
        @tparam Args
        @param data
        @param args
        @return T
        */
        template <typename... Args>
        T makeObj(const json& data, Args&&... args);

        /**
        Validate the data against the schema, if it fails throws a runtime error
        @param data
        */
        void validate(const json& data) {
            json_validator validator(mySchema_, loader, nlohmann::json_schema::default_string_format_check);
            try {
                validator.validate(data);
            } catch (const std::exception& e) {
                std::string error = e.what();
                throw std::runtime_error("Validation of schema failed:\t" + error + "\n");
            }
        };

        /**
        Check if the data is valid according to the schema
        @param data
        @return bool
        */
        bool isValid(const json& data) {
            try {
                validate(data);
                return true;
            } catch (std::exception&) { return false; }
        };

        /**
        Add a new required field to the schema
        @param key
        @param format
        */
        void addRequired(const std::string& key, const json& format) {
            mySchema_["required"].push_back(key);
            mySchema_["properties"][key] = format;
        };

        /**
        Remove a required field from the schema
        @param key
        */
        void removeRequired(const std::string& key) {
            mySchema_["required"].erase(std::remove(mySchema_["required"].begin(), mySchema_["required"].end(), key), mySchema_["required"].end());
            mySchema_["properties"].erase(key);
        };

        /**
        Add a default value for a specific key
        @param key
        @param value
        */
        void addDefaultValue(const std::string& key, const json& value) { myDefaultValues_[key] = value; };

        /**
        Remove the default value for a specific key
        @param key
        */
        void removeDefaultValue(const std::string& key) { myDefaultValues_.erase(key); };

        /**
        Set the default values for target json
        @param target
        @return json
        */
        json setDefaultValues(json target) {
            dfs(myDefaultValues_, target);
            return target;
        };

       private:
        /**
         * @brief Auxiliary function to set default values
         *
         * @param defaults
         * @param target
         */
        void dfs(const json& defaults, json& target) {
            for (auto& [key, value] : defaults.items()) {
                if (target.find(key) == target.end()) {
                    target[key] = value;
                } else if (value.is_object()) {
                    dfs(value, target[key]);
                }
            }
        }

        /**
         * @brief Uri loader for json schema
         *
         * @param uri
         * @param schema
         */
        static void loader(const json_uri& uri, json& schema) {
            std::string filename = schemaPath + uri.path();
            std::ifstream lf(filename);
            if (!lf.good()) throw std::invalid_argument("could not open " + uri.url() + " tried with " + filename);
            try {
                lf >> schema;
            } catch (const std::exception& e) { throw e; }
        }

        /**
         * @brief Read a json file
         *
         * @param filePath
         * @return json
         */
        static json readJSONFile(std::string filePath) {
            std::ifstream file(schemaPath + filePath);
            std::ostringstream tmp;
            tmp << file.rdbuf();
            return json::parse(tmp.str());
        }

        /**
         * @brief Initialize the schema
         *
         */
        void initSchema();

        /**
         * @brief Initialize the default values
         *
         */
        void initDefaultValues();

        json myDefaultValues_;
        json mySchema_;
    };
}  // namespace QuantLibParser

#endif /* C7259EDE_8AB0_4851_B8F0_93EF8D404811 */

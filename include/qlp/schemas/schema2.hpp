#ifndef C7259EDE_8AB0_4851_B8F0_93EF8D404811
#define C7259EDE_8AB0_4851_B8F0_93EF8D404811

#include <ql/handle.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/quote.hpp>
#include <nlohmann/json-schema.hpp>
#include <fstream>
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
    class Schema2 {
       public:
        Schema2() {
            initSchema();
            initDefaultValues();
            mySchema_["$schema"] = "http://json-schema.org/draft-07/schema#";
        }

        json schema() { return mySchema_; };

        template <typename... Args>
        T makeObj(const json& data, Args&&... args);

        json validate(const json& data) {
            json_validator validator;
            try {
                validator.set_root_schema(mySchema_);  // insert root-schema
                const auto default_patch = validator.validate(data);
                json patch               = data.patch(default_patch);
                return patch;

            } catch (const std::exception& e) {
                std::string error = e.what();
                throw std::runtime_error("Validation of schema failed:\t" + error + "\n");
            }
        };

        bool isValid(const json& data) {
            try {
                validate(data);
                return true;
            } catch (std::exception&) { return false; }
        };

        void addRequired(const std::string& key, const json& format) {
            mySchema_["required"].push_back(key);
            mySchema_["properties"][key] = format;
        };

        void removeRequired(const std::string& key) {
            mySchema_["required"].erase(std::remove(mySchema_["required"].begin(), mySchema_["required"].end(), key), mySchema_["required"].end());
            mySchema_["properties"].erase(key);
        };

        void addDefaultValue(const std::string& key, const json& value) { myDefaultValues_[key] = value; };

        void removeDefaultValue(const std::string& key) { myDefaultValues_.erase(key); };

       private:
        void loader(const std::string& uri, json& schema) {
            std::string filename = "./" + uri;
            std::ifstream lf(filename);
            if (!lf.good()) throw std::invalid_argument("Could not open " + uri + " tried with " + filename);
            try {
                lf >> schema;
            } catch (const std::exception& e) { throw e; }
        }

        void initSchema();
        void initDefaultValues();

        json myDefaultValues_;
        json mySchema_;
    };
}  // namespace QuantLibParser

#endif /* C7259EDE_8AB0_4851_B8F0_93EF8D404811 */

#ifndef FE76B325_D614_42C2_B02D_FBBF19C04BBC
#define FE76B325_D614_42C2_B02D_FBBF19C04BBC

#include <ql/handle.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/quote.hpp>
#include <nlohmann/json-schema.hpp>
#include <stdexcept>

namespace QuantLibParser {

    using json = nlohmann::json;
    using nlohmann::json_schema::json_validator;
    namespace ext = boost;

    using PriceGetter = std::function<QuantLib::Handle<QuantLib::Quote>(double price, const std::string& ticker)>;

    using IndexGetter = std::function<ext::shared_ptr<QuantLib::IborIndex>(const std::string& name)>;

    using CurveGetter = std::function<QuantLib::RelinkableHandle<QuantLib::YieldTermStructure>(const std::string& name)>;

    template <typename T>
    class Schema {
       public:
        Schema() {
            initSchema();
            initDefaultValues();
            mySchema_["$schema"] = "http://json-schema.org/draft-07/schema#";
        }

        json schema() { return mySchema_; };

        template <typename... Args>
        T makeObj(const json& data, Args&&... args);

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

        json setDefaultValues(json target) {
            for (auto& [k, v] : myDefaultValues_.items()) {
                if (target.find(k) == target.end()) target[k] = v;
            }
            return target;
        };

        void addDefaultValue(const std::string& key, const json& value) { myDefaultValues_[key] = value; };

        void removeDefaultValue(const std::string& key) { myDefaultValues_.erase(key); };

       private:
        void initSchema();
        void initDefaultValues();

        json myDefaultValues_;
        json mySchema_;
    };
}  // namespace QuantLibParser

#endif /* FE76B325_D614_42C2_B02D_FBBF19C04BBC */

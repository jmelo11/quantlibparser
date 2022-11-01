#ifndef FBD8AA68_730E_479B_9583_A3FDEAC4D1C3
#define FBD8AA68_730E_479B_9583_A3FDEAC4D1C3

#include <boost/preprocessor.hpp>
#include <unordered_map>

#define SERIALIZE_ENUM_TO_CASES(r, data, elem) \
    case elem:                                 \
        return BOOST_PP_STRINGIZE(elem);
#define SERIALIZE_ENUM_TO_MAP(r, data, elem) {BOOST_PP_STRINGIZE(elem), elem},
#define SERIALIZE_ENUM_WITH_CONVERSIONS(name, enumerators)                    \
    enum name { BOOST_PP_SEQ_ENUM(enumerators) };                             \
    static const std::unordered_map<std::string, name> map_##name{            \
        BOOST_PP_SEQ_FOR_EACH(SERIALIZE_ENUM_TO_MAP, name, enumerators)};     \
    static inline const char* ToString(name v) {                              \
        switch (v) {                                                          \
            BOOST_PP_SEQ_FOR_EACH(SERIALIZE_ENUM_TO_CASES, name, enumerators) \
            default:                                                          \
                return "[Unknown " BOOST_PP_STRINGIZE(name) "]";              \
        }                                                                     \
    };

#endif /* FBD8AA68_730E_479B_9583_A3FDEAC4D1C3 */

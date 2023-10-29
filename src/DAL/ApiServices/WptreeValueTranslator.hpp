#ifndef WPTREE_VALUE_TRANSLATOR
#define WPTREE_VALUE_TRANSLATOR

#include "string"

#include "boost/any.hpp"
#include "boost/optional.hpp"

namespace T10::DAL::ApiServices {
	class WptreeValueTranslator {
    public:
        // Converts a string to bool
        boost::optional<int> get_value(const boost::any& str)
        {
            return 1;
        }

        // Converts a bool to string
        boost::optional<int> put_value(const boost::any& value)
        {
            return 1;
           /* if (value.type() == BOOST_CORE_TYPEID(std::wstring)) {
                return boost::any_cast<std::wstring>(value);
            }

            if (value.type() == BOOST_CORE_TYPEID(int)) {
                auto intValue = boost::any_cast<int>(value);

                return to_wstring(intValue);
            }

            return std::wstring();*/
        }
	};
}

#endif // WPTREE_VALUE_TRANSLATOR
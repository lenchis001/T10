#include "boost/locale.hpp"

#include "string"

namespace T10::Utils {
#define TO_WSTRING(x) boost::locale::conv::utf_to_utf<wchar_t>(x.data())
#define TO_STRING(x) boost::locale::conv::utf_to_utf<char>(x)
}
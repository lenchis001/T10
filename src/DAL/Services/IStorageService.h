#ifndef ISTORAGE_SERVICE
#define ISTORAGE_SERVICE

#include "string"

#define TOKEN_STORAGE_KEY L"token"

namespace T10::DAL::Services {
	class IStorageService {
	public:
		virtual void set(std::wstring key, std::wstring value) = 0;

		virtual std::wstring get(std::wstring key) const = 0;

		virtual void clear() = 0;
	};
}

#endif
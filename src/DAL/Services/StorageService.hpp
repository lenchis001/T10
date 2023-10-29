#ifndef STORAGE_SERVICE
#define STORAGE_SERVICE

#include "IStorageService.h"

#include "map"

#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"
#include "boost/filesystem.hpp"

#define STORAGE_FILENAME std::string("preferences.json")

namespace T10::DAL::Services {
	class StorageService : public IStorageService {
	public:
		StorageService() {
			_load();
		}

		void set(std::wstring key, std::wstring value) {
			_cache.put_child(key, boost::property_tree::wptree(value));

			_save();
		}

		std::wstring get(std::wstring key) const {
			auto child = _cache.get_child_optional(key);
			if (child) {
				return child.value().get_value(L"");
			}
			else {
				return std::wstring();
			}
		};

		void clear() {
		}
	private:
		void _load() {
			if (boost::filesystem::exists(STORAGE_FILENAME)) {
				boost::property_tree::json_parser::read_json(STORAGE_FILENAME, _cache);
			}
		}

		void _save() {
			boost::property_tree::json_parser::write_json(STORAGE_FILENAME, _cache);
		}

		boost::property_tree::wptree _cache;
	};

}

#endif
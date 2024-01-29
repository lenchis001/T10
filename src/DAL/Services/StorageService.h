#ifndef STORAGE_SERVICE_H
#define STORAGE_SERVICE_H

#include "IStorageService.h"

#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"
#include "boost/filesystem.hpp"

#define STORAGE_FILENAME std::string("preferences.json")

namespace T10::DAL::Services
{
	class StorageService : public IStorageService
	{
	public:
		StorageService();
		void set(std::wstring key, std::wstring value) override;
		std::wstring get(std::wstring key) const override;
		void clear() override;

	private:
		void _load();
		void _save();
		boost::property_tree::wptree _cache;
	};
}

#endif
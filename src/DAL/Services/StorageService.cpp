#include "StorageService.h"

namespace T10::DAL::Services
{
	StorageService::StorageService()
	{
		_load();
	}

	void StorageService::set(std::wstring key, std::wstring value)
	{
		_cache.put_child(key, boost::property_tree::wptree(value));
		_save();
	}

	std::wstring StorageService::get(std::wstring key) const
	{
		auto child = _cache.get_child_optional(key);
		if (child)
		{
			return child.value().get_value(L"");
		}
		else
		{
			return std::wstring();
		}
	}

	void StorageService::clear()
	{
		// implementation for the clear function
	}

	void StorageService::_load()
	{
		if (boost::filesystem::exists(STORAGE_FILENAME))
		{
			boost::property_tree::read_json(STORAGE_FILENAME, _cache);
		}
	}

	void StorageService::_save()
	{
		boost::property_tree::write_json(STORAGE_FILENAME, _cache);
	}
}
#ifndef BASE_API_SERVICE
#define BASE_API_SERVICE

#include "boost/smart_ptr.hpp"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"
#include <boost/algorithm/string.hpp>
#include "boost/filesystem.hpp"

#include "DAL/Models/DataActionResult.h"
#include "DAL/ApiServices/ICommunicationService.h"

namespace T10::DAL::ApiServices
{
    class BaseApiService
    {
    public:
        BaseApiService(boost::shared_ptr<ICommunicationService> communicationService)
        {
            _communicationService = communicationService;
        }

    protected:
        Models::DataActionResult<boost::property_tree::wptree> processRequest(Models::HttpRequest &request)
        {
            Models::HttpResponse<> response = _communicationService->process(request);

            int statusCode = response.getStatusCode();

            boost::property_tree::wptree ptreeData;
            if (statusCode < 300 && statusCode > 199 && !response.getBody().empty())
            {
                ptreeData = toWPtree(response.getBody());
            }

            Models::ErrorCode error = toErrorCode(statusCode);

            return Models::DataActionResult<boost::property_tree::wptree>(error, ptreeData);
        }

        template <typename T>
        std::vector<T> asVector(boost::property_tree::wptree pt, boost::property_tree::wptree::key_type key)
        {
            std::vector<T> r;
            for (auto &item : pt.get_child(key))
                r.push_back(item.second.get_value<T>());
            return r;
        }

        std::wstring toJson(std::map<std::wstring, boost::any> map)
        {
            auto result = std::wstring(L"{\n");

            bool isFirstProperty = true;
            for (const auto& pair : map)
            {
                if (!isFirstProperty) {
                    result += L",\n";
                }
                isFirstProperty = false;

                result += L"\"" + pair.first + L"\" : ";

                if (pair.second.type() == BOOST_CORE_TYPEID(int)) {
                    result += to_wstring(boost::any_cast<int>(pair.second));
                    continue;
                }

                if (pair.second.type() == BOOST_CORE_TYPEID(std::wstring)) {
                    result += boost::any_cast<std::wstring>(pair.second);
                    continue;
                }

                throw "An unknown type to cast.";
            }

            result += L"\n}";

            return result;
        }

    private:
        boost::property_tree::wptree toWPtree(const std::wstring &jsonData)
        {
            std::wstringstream wss;
            wss.str(jsonData);
            boost::property_tree::wptree wptree;

            boost::property_tree::json_parser::read_json(wss, wptree);

            return wptree;
        }

        Models::ErrorCode toErrorCode(int statusCode)
        {
            switch (statusCode)
            {
            case 200:
                return Models::ErrorCode::OK;
            default:
                return Models::ErrorCode::UNKNOWN;
            }
        }

        boost::shared_ptr<ICommunicationService> _communicationService;
    };
}

#endif
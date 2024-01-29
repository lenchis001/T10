#ifndef BASE_API_SERVICE_H
#define BASE_API_SERVICE_H

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
        BaseApiService(boost::shared_ptr<ICommunicationService> communicationService);

    protected:
        Models::DataActionResult<boost::property_tree::wptree> processRequest(Models::HttpRequest& request);
        template <typename T>
        std::vector<T> asVector(boost::property_tree::wptree pt, boost::property_tree::wptree::key_type key);
        std::wstring toJson(std::map<std::wstring, boost::any> map);

    private:
        boost::property_tree::wptree toWPtree(const std::wstring& jsonData);
        Models::ErrorCode toErrorCode(int statusCode);

        boost::shared_ptr<ICommunicationService> _communicationService;
    };
}

#endif // BASE_API_SERVICE_H
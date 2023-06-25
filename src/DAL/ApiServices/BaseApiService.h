#ifndef BASE_API_SERVICE
#define BASE_API_SERVICE

#include "boost/smart_ptr.hpp"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"

#include "DAL/Models/ActionResult.h"
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
        Models::ActionResult<boost::property_tree::wptree> processRequest(Models::HttpRequest &request)
        {
            Models::HttpResponse<> response = _communicationService->process(request);

            boost::property_tree::wptree ptreeData = toWPtree(response.getBody());
            Models::ErrorCode error = toErrorCode(response.getStatusCode());

            return Models::ActionResult<boost::property_tree::wptree>(Models::ErrorCode::OK, ptreeData);
        }

        template <typename T>
        std::vector<T> asVector(boost::property_tree::wptree pt, boost::property_tree::wptree::key_type key)
        {
            std::vector<T> r;
            for (auto &item : pt.get_child(key))
                r.push_back(item.second.get_value<T>());
            return r;
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
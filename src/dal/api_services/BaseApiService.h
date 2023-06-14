#ifndef BASE_API_SERVICE
#define BASE_API_SERVICE

#include "boost/smart_ptr.hpp"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"

#include "dal/models/ActionResult.h"
#include "dal/api_services/ICommunicationService.h"

namespace T10::dal::api_services
{
    class BaseApiService
    {
    public:
        BaseApiService(boost::shared_ptr<ICommunicationService> communicationService)
        {
            _communicationService = communicationService;
        }

    protected:
        models::ActionResult<boost::property_tree::wptree> processRequest(models::HttpRequest& request)
        {
            models::HttpResponse<> response = _communicationService->process(request);

            boost::property_tree::wptree ptreeData = toWPtree(response.getBody());
            models::ErrorCode error = toErrorCode(response.getStatusCode());

            return models::ActionResult<boost::property_tree::wptree>(models::ErrorCode::OK, ptreeData);
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

        models::ErrorCode toErrorCode(int statusCode)
        {
            switch (statusCode)
            {
            case 200:
                return models::ErrorCode::OK;
            default:
                return models::ErrorCode::UNKNOWN;
            }
        }

        boost::shared_ptr<ICommunicationService> _communicationService;
    };
}

#endif
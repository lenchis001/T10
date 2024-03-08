#include "CommunicationService.h"

#include "Utils/Utils.h"

using namespace T10::DAL::Models;
using namespace T10::DAL::ApiServices;

http::verb toHttpVerb(HttpRequestType requestType)
{
    switch (requestType)
    {
    case HttpRequestType::DELETE_T:
        return http::verb::delete_;
    case HttpRequestType::GET:
        return http::verb::get;
    case HttpRequestType::POST:
        return http::verb::post;
    case HttpRequestType::PUT:
        return http::verb::put;
    default:
        throw "An unknown HttpRequestType value";
    }
}

HttpResponse<> CommunicationService::process(Models::HttpRequest& request)
{
    try
    {
        auto const host = TO_STRING(request.getHost());
        auto const port = TO_STRING(request.getPort());
        auto const target = TO_STRING(request.getResource());
        int version = 11;

        // The io_context is required for all I/O
        net::io_context ioc;

        // These objects perform our I/O
        tcp::resolver resolver(ioc);
        beast::tcp_stream stream(ioc);

        // Look up the domain name
        auto const results = resolver.resolve(host, port);

        // Make the connection on the IP address we get from a lookup
        stream.connect(results);

        // Set up an HTTP GET request message
        std::string body = TO_STRING(request.getBody());
        http::request<http::string_body> req{ toHttpVerb(request.getType()), target, version, body };
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        _addHeaders(req, request.getHeaders());

        // Send the HTTP request to the remote host
        http::write(stream, req);

        // This buffer is used for reading and must be persisted
        beast::flat_buffer buffer;

        // Declare a container to hold the response
        http::response<http::dynamic_body> res;

        // Receive the HTTP response
        http::read(stream, buffer, res);

        // Gracefully close the socket
        beast::error_code ec;
        stream.socket().shutdown(tcp::socket::shutdown_both, ec);

        // not_connected happens sometimes
        // so don't bother reporting it.
        //
        if (ec && ec != beast::errc::not_connected)
            throw beast::system_error{ ec };

        // If we get here then the connection is closed gracefully

        auto bodyString = boost::beast::buffers_to_string(res.body().data());

        std::map<std::wstring, std::wstring> headers;
        std::for_each(res.begin(), res.end(), [&](auto& header)
            {
                boost::beast::basic_string_view<char> name = header.name_string();
                boost::beast::basic_string_view<char> value = header.value();

                headers.insert(std::pair<std::wstring, std::wstring>(TO_WSTRING(name), TO_WSTRING(value))); });

        return Models::HttpResponse(res.result_int(), TO_WSTRING(bodyString), headers);
    }
    catch (std::exception const& e)
    {
        return Models::HttpResponse<>(-1, L"", {});
    }
}

void CommunicationService::setAuthentication(std::wstring token)
{
    _token = token;
}

void CommunicationService::_addHeaders(http::request<http::string_body>& req, const std::map<HeaderType, std::wstring>& headers)
{
    for (std::pair<HeaderType, std::wstring> header : headers)
    {
        switch (header.first)
        {
        case HeaderType::CONTENT_TYPE:
            req.set(http::field::content_type, TO_STRING(header.second));
            break;
        }
    }

    req.content_length(req.body().length());

    if (!_token.empty()) {
        req.set("Authorization", TO_STRING(std::wstring(L"Bearer ") + _token));
    }
}
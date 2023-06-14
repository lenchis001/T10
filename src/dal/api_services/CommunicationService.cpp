#include "CommunicationService.h"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include "boost/locale.hpp"
#include <cstdlib>
#include <string>
#include "iostream"

namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http;   // from <boost/beast/http.hpp>
namespace net = boost::asio;    // from <boost/asio.hpp>
using tcp = net::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

#define TO_WSTRING(x) boost::locale::conv::utf_to_utf<wchar_t>(x.data())
#define TO_STRING(x) boost::locale::conv::utf_to_utf<char>(x)

namespace T10::dal::api_services
{
    http::verb toHttpVerb(models::HttpRequestType requestType)
    {
        switch (requestType)
        {
        case models::HttpRequestType::DELETE:
            return http::verb::delete_;
        case models::HttpRequestType::GET:
            return http::verb::get;
        case models::HttpRequestType::POST:
            return http::verb::post;
        case models::HttpRequestType::PUT:
            return http::verb::put;
        default:
            throw "An unknown HttpRequestType value";
        }
    }

    T10::dal::models::HttpResponse<> CommunicationService::process(T10::dal::models::HttpRequest &request)
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
            http::request<http::string_body> req{toHttpVerb(request.getType()), target, version, TO_STRING(request.getBody())};
            req.set(http::field::host, host);
            req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

            // Send the HTTP request to the remote host
            http::write(stream, req);

            // This buffer is used for reading and must be persisted
            beast::flat_buffer buffer;

            // Declare a container to hold the response
            http::response<http::dynamic_body> res;

            // Receive the HTTP response
            http::read(stream, buffer, res);

            // Write the message to standard out
            // std::cout << res << std::endl;

            // Gracefully close the socket
            beast::error_code ec;
            stream.socket().shutdown(tcp::socket::shutdown_both, ec);

            // not_connected happens sometimes
            // so don't bother reporting it.
            //
            if (ec && ec != beast::errc::not_connected)
                throw beast::system_error{ec};

            auto bodyString = boost::beast::buffers_to_string(res.body().data());

            std::map<std::wstring, std::wstring> headers;
            std::for_each(res.begin(), res.end(), [&](auto &header)
                          {
                              boost::beast::basic_string_view<char> name = header.name_string();
                              boost::beast::basic_string_view<char> value = header.value();

                              headers.insert(std::pair<std::wstring, std::wstring>(TO_WSTRING(name), TO_WSTRING(value))); });

            // If we get here then the connection is closed gracefully

            return models::HttpResponse(res.result_int(), TO_WSTRING(bodyString), headers);
        }
        catch (std::exception const &e)
        {
            return models::HttpResponse<>(-1, L"", {});
        }
    }
}
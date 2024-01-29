#ifndef WEB_SOCKET_API_SERVICE_H
#define WEB_SOCKET_API_SERVICE_H

#include "IWebSocketApiService.h"

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

typedef websocketpp::client<websocketpp::config::asio_client> client;
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

namespace T10::DAL::ApiServices
{
    class WebSocketApiService : public IWebSocketApiService, public boost::enable_shared_from_this<WebSocketApiService>
    {
    public:
        boost::future<void> connect(const std::string& host, const std::string& apiKey) override;
        void send(const std::string& data) override;
        void setDataHandler(boost::function<void(const std::string&)> handler) override;
        void disconnect() override;

    private:
        websocketpp::connection_hdl _handler;
        boost::shared_ptr<client> _client;
        boost::function<void(const std::string&)> _messageHandler;
        boost::shared_ptr<boost::thread> _socketThread;
        boost::promise<void> _connectPromise;
        std::string _apiKey;
    };
}

#endif // WEB_SOCKET_API_SERVICE_H
#include "WebSocketApiService.h"

using namespace T10::DAL::ApiServices;

boost::future<void> WebSocketApiService::connect(const std::string& host, const std::map<std::string, std::string>& headers)
{
    // Create a client endpoint
    _client = boost::make_shared<client>();
    _connectPromise = boost::promise<void>();

    // Set logging to be pretty verbose (everything except message payloads)
    _client->set_access_channels(websocketpp::log::alevel::all);
    _client->clear_access_channels(websocketpp::log::alevel::frame_payload);
    _client->set_open_handler([&](websocketpp::connection_hdl handler) {
            _handler = handler;

            _connectPromise.set_value();
        });

    // Initialize ASIO
    _client->init_asio();

    _client->set_message_handler([&](websocketpp::connection_hdl, message_ptr message) {
        if (_messageHandler)
            _messageHandler(message->get_payload());
        });

    websocketpp::lib::error_code ec;
    client::connection_ptr con = _client->get_connection(host, ec);

    for (auto& header : headers) {
        con->append_header(header.first, header.second);
    }

    _client->connect(con);

    _socketThread = boost::make_shared<boost::thread>([&]() {
        _client->run();
        });

    return _connectPromise.get_future();
}

void WebSocketApiService::send(const std::string& data)
{
    _client->send(_handler, data, websocketpp::frame::opcode::value::text);
}

void WebSocketApiService::setDataHandler(boost::function<void(const std::string&)> handler)
{
    _messageHandler = handler;
}

void WebSocketApiService::disconnect()
{
    _client->close(_handler, websocketpp::close::status::normal, "");
}
#ifndef WEB_SOCKET_API_SERVICE
#define WEB_SOCKET_API_SERVICE

#include "IWebSocketApiService.h"

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <iostream>

typedef websocketpp::client<websocketpp::config::asio_client> client;

// pull out the type of messages sent by our config
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

namespace T10::DAL::ApiServices {
	class WebSocketApiService : public IWebSocketApiService, public boost::enable_shared_from_this<WebSocketApiService> {
	public:
		boost::future<void> connect(const std::string& host) override {
			// Create a client endpoint
			_client = boost::make_shared<client>();

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
				if(_messageHandler)
					_messageHandler(message->get_payload());
				});

			websocketpp::lib::error_code ec;
			client::connection_ptr con = _client->get_connection(host, ec);

			_client->connect(con);

			_socketThread = boost::make_shared<boost::thread>([&]() {
				_client->run();
				});

			return _connectPromise.get_future();
		}

		void send(const std::string& data) override {
			_client->send(_handler, data, websocketpp::frame::opcode::value::text);
		}

		void setDataHandler(boost::function<void(const std::string&)> handler) override {
			_messageHandler = handler;
		}

		void disconnect() override {
			_client->close(_handler, websocketpp::close::status::normal, "");
		}
	private:
		websocketpp::connection_hdl _handler;
		boost::shared_ptr<client> _client;
		boost::function<void(const std::string&)> _messageHandler;

		boost::shared_ptr<boost::thread> _socketThread;
		boost::promise<void> _connectPromise;
	};
}

#endif // WEB_SOCKET_API_SERVICE
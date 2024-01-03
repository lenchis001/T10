#ifndef IWEB_SOCKET_API_SERVICE
#define IWEB_SOCKET_API_SERVICE

#define BOOST_THREAD_PROVIDES_FUTURE
#define BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION

#include "string"

#include <boost/thread/future.hpp>
#include <boost/function.hpp>

namespace T10::DAL::ApiServices {
	class IWebSocketApiService {
	public:
		virtual boost::future<void> connect(const std::string& host, const std::string& apiKey) = 0;
		
		virtual void send(const std::string& data) = 0;

		virtual void setDataHandler(boost::function<void(const std::string&)> handler) = 0;

		virtual void disconnect() = 0;
	};
}

#endif // IWEB_SOCKET_API_SERVICE
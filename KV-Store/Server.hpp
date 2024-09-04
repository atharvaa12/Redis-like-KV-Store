#ifndef SERVER_HPP
#define SERVER_HPP
#include <boost/asio.hpp>
#include "SessionManager.hpp"
class Server {
private:
	boost::asio::ip::tcp::acceptor acceptor;
	boost::asio::io_context& serverIOContext;
	SessionManager sessionManager;
	std::unique_ptr<boost::asio::ip::tcp::socket> socketptr;

	void accept();

public:
	Server(boost::asio::io_context& io, int port) :acceptor(io, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)), serverIOContext(io) {
		accept();
	};
		

	
};
#endif // !SERVER_HPP

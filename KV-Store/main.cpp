#include "Server.hpp"
#include "Parser.hpp"
#include <thread>

int main() {
	boost::asio::io_context io;
	Server server(io, 1234);
	std::thread t1(&Server::handleConsoleInput, &server);
	Parser parser;
	server.accept();
	io.run();
	if (t1.joinable()) {
		t1.join();
	}

	return 0;

}
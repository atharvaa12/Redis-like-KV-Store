#include "Server.hpp"
#include "Parser.hpp"
#include <thread>
#include "LogQueue.hpp"

int main() {
	boost::asio::io_context io;
	LogQueue logQueue;
	Server server(io, 1234,logQueue.getPtr());
	std::thread t1(&Server::handleConsoleInput, &server);
	std::thread t2(&LogQueue::handleLogQueue, logQueue.getPtr());
	Parser parser(logQueue.getPtr());
	server.accept();
	io.run();
	if (t1.joinable()) {
		t1.join();
	}
	if (t2.joinable()) {
		t2.join();
	}

	return 0;

}
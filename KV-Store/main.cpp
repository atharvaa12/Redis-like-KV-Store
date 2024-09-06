#include "Server.hpp"
#include "Parser.hpp"
int main() {
	boost::asio::io_context io;
	Server server(io, 1234);
	Parser parser;
	io.run();


}
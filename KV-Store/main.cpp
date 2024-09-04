#include "Server.hpp"
int main() {
	boost::asio::io_context io;
	Server server(io, 1234);
	io.run();


}
#include "Server.hpp"
#include<iostream>

void Server::accept() {

	std::cout << "listening for connection" << std::endl;
	socketptr = std::make_unique<boost::asio::ip::tcp::socket>(serverIOContext);

	acceptor.async_accept(*socketptr, [this](boost::system::error_code ec) {
		if (ec) {
			std::cerr << "Error occured while accepting connection: " << ec.message() << std::endl;
		}
		else {
			std::cout << "Connection accepted" <<std::endl;
			
			sessionManager.addSession(std::move(socketptr));
			accept();

		}

		

		});
}

void Server::handleConsoleInput()
{
	std::string input;
	while (true)
	{
		input.clear();
		std::getline(std::cin, input);
		// Trim leading and trailing whitespace
		input.erase(0, input.find_first_not_of(" \t\r\n")); // Trim leading
		input.erase(input.find_last_not_of(" \t\r\n") + 1); // Trim trailing
		if (input.empty()) {
			std::cout << "Empty input" << std::endl;
		}
		else if (input == "q") {
			stop();
			break;
		}
		else {
			std::cout << "Invalid command" << std::endl;
		}
		
	}

}
void Server::stop() {
	
	sessionManager.removeAll();
	acceptor.cancel();
	acceptor.close();
	serverIOContext.stop();
	//serverIOContext.reset();
	

}



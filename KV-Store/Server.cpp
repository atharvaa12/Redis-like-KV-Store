#include "Server.hpp"
#include<iostream>
void Server::accept() {

	
	socketptr = std::make_unique<boost::asio::ip::tcp::socket>(serverIOContext);

	acceptor.async_accept(*socketptr, [this](boost::system::error_code ec) {
		if (ec) {
			std::cerr << "Error occured while accepting connection: " << ec.message() << std::endl;
		}
		else {
			std::cout << "Connection accepted" << std::endl;
			sessionManager.addSession(std::move(socketptr));
			accept();

		}

		

		});
}


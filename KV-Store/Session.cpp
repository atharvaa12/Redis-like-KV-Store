#include "Session.hpp"
#include<iostream>
void Session::sendToClient(std::string message)
{
	boost::asio::async_write(*socketptr, boost::asio::buffer(message), [](const boost::system::error_code& error, size_t bytes) {
		if (!error) {
				
			}
		else {
			std::cerr << "error writing data to client" << std::endl;
		}
		});




}
void  Session::getLineFromClient()
{
	sessionBuffer.consume(sessionBuffer.size());
	boost::asio::async_read_until(*socketptr, sessionBuffer, '\n', [this](const boost::system::error_code& error, size_t bytes) {
		if (!error){
			//handler code
			std::istream is(&sessionBuffer);
		

			std::string message;
			getline(is, message);
			std::cout << message << std::endl;


			getLineFromClient();

		}
		else {
			std::cerr << "error reading data from client" << std::endl;
		}
		
	}
	
	
	);
}


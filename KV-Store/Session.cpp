#include "Session.hpp"
#include<iostream>
#include "ClientRequestHandler.hpp"
#include "SessionManager.hpp"
class ClientRequestHandler;
void Session::killSession()
{
	sendToClientSync("Connection closed by server");
	socketptr->cancel();
	socketptr->close();
	sessionManager.removeSession(sessionId);
}
void Session::sendToClient(std::string message)
{
	writeBuffer.consume(writeBuffer.size());
	std::ostream os(&writeBuffer);
	os << message;


	std::cout << "async writing to client" << std::endl;
	boost::asio::async_write(*socketptr, writeBuffer, [](const boost::system::error_code& error, size_t bytes) {
		if (!error) {
			std::cout << "data sent to client" << std::endl;
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
			// Trim leading and trailing whitespace
			message.erase(0, message.find_first_not_of(" \t\r\n")); // Trim leading
			message.erase(message.find_last_not_of(" \t\r\n") + 1); // Trim trailing

			// Check if the message is empty
			if (message.empty()) {
				std::cerr << "Received empty or whitespace-only message" << std::endl;
			
			}
			else if (message == "q") {
				killSession();
				return;
			}
			else {
				std::cout << "Received message: " << message << " (size: " << message.size() << ")" << std::endl;
				ClientRequestHandler crh(*this, sessionId);
				crh.handleRequest(message);
				
			}
			getLineFromClient();





			

		}
		else {
			std::cerr << "error reading data from client" << std::endl;
		}
		
	}
	
	
	);
}


void Session::sendToClientSync(std::string message)
{
	boost::asio::write(*socketptr, boost::asio::buffer(message));
	std::cout << "data sent to client" << std::endl;
}


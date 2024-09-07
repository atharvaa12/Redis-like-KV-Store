#ifndef SESSION_HPP
#define SESSION_HPP
#include<boost/asio.hpp>
#include "SessionManager.hpp"
#include<string>
class SessionManager;
class Session {
private:
	std::unique_ptr<boost::asio::ip::tcp::socket> socketptr;
	boost::asio::streambuf sessionBuffer;
	boost::asio::streambuf writeBuffer;
	
	 const int sessionId;
	 SessionManager& sessionManager;

public:
	Session(std::unique_ptr<boost::asio::ip::tcp::socket> clientSocket,  const int id,SessionManager & sm) :socketptr(std::move(clientSocket)), sessionId(id),sessionManager(sm) {
		getLineFromClient();

	};
	void killSession();
	void sendToClient(std::string message);
	void getLineFromClient();
	
	void sendToClientSync(std::string message);




};
#endif // !HANDLECLIENT_HPP

#ifndef SESSION_HPP
#define SESSION_HPP
#include<boost/asio.hpp>
#include<string>
class Session {
private:
	std::unique_ptr<boost::asio::ip::tcp::socket> socketptr;
	boost::asio::streambuf sessionBuffer;
	boost::asio::streambuf writeBuffer;
	int sessionId;

public:
	Session(std::unique_ptr<boost::asio::ip::tcp::socket> clientSocket, int id) :socketptr(std::move(clientSocket)), sessionId(id) {
		getLineFromClient();

	};
	void sendToClient(std::string message);
	void getLineFromClient();
	void sendToClientSync(std::string message);




};
#endif // !HANDLECLIENT_HPP

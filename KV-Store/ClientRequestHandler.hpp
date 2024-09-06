#ifndef CLIENT_REQUEST_HANDLER_HPP
#define CLIENT_REQUEST_HANDLER_HPP
#include "Session.hpp"
class ClientRequestHandler {
private:
	int sessionId;
	Session& currentSession;
public:
	ClientRequestHandler(Session& session,int sId) :currentSession(session), sessionId(sId) {};
	void sendToClient(std::string message);
	std::vector<std::string > tokenize(const std::string& message);
	void handleRequest(const std::string& message);
	void sendToClientSync(std::string message);


};
#endif // !CLIENT_REQUEST_HANDLER_HPP

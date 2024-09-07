#ifndef CLIENT_REQUEST_HANDLER_HPP
#define CLIENT_REQUEST_HANDLER_HPP
#include "SessionManager.hpp"
#include "Session.hpp"
class Session;
class ClientRequestHandler {
private:
	
	Session& currentSession;
	const int sessionId;

public:
	ClientRequestHandler(  Session& session,const int sId) :currentSession(session), sessionId(sId){};
	void sendToClient(std::string message);
	std::vector<std::string > tokenize(const std::string& message);
	void handleRequest(const std::string& message);
	void sendToClientSync(std::string message);
	int getSessionId() const;
	void killSession();


};
#endif // !CLIENT_REQUEST_HANDLER_HPP

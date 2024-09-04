#ifndef SESSIONMANAGER_HPP
#define SESSIONMANAGER_HPP
#include<vector>
#include<unordered_map>
#include "Session.hpp"
#include <unordered_set>
class SessionManager {
private:
	std::unordered_set<int> usedSessionId;
	std::unordered_map<int, std::unique_ptr<Session>> sessions;

public:
	void addSession(std::unique_ptr<boost::asio::ip::tcp::socket> socketptr);
	void removeSession(int sessionId);





};
#endif // !SESSIONMANAGER_HPP

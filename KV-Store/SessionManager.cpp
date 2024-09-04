#include "SessionManager.hpp"
#include<random>
void SessionManager::addSession(std::unique_ptr<boost::asio::ip::tcp::socket> socketptr)
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(1, INT_MAX);
	int randomInt;
	do {
		randomInt = distr(eng);

	} while (usedSessionId.find(randomInt) != usedSessionId.end());
	sessions[randomInt] = std::make_unique<Session>(std::move(socketptr),randomInt);

}

void SessionManager::removeSession(int sessionId)
{
	usedSessionId.erase(sessionId);
	sessions.erase(sessionId);

}

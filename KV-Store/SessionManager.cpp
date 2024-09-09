#include "SessionManager.hpp"
#include<random>
#include  <iostream>
void SessionManager::addSession(std::unique_ptr<boost::asio::ip::tcp::socket> socketptr)
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(1, INT_MAX);
	int randomInt;
	do {
		randomInt = distr(eng);

	} while (usedSessionId.find(randomInt) != usedSessionId.end());
	usedSessionId.insert(randomInt);
	sessions[randomInt] = std::make_unique<Session>(std::move(socketptr),randomInt,*this);
	std::cout << "Concurrent connections: " <<(int) usedSessionId.size() << std::endl;

}

void SessionManager::removeSession(int sessionId)
{
	sessions[sessionId]->closeSession();
	usedSessionId.erase(sessionId);
	sessions.erase(sessionId);
	std::cout << "Concurrent connections: " << (int)usedSessionId.size() << std::endl;

}

void SessionManager::removeAll()
{
	while (!usedSessionId.empty())
	{	
		removeSession(*usedSessionId.begin());

	}
}


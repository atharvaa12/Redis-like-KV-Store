#include "ClientRequestHandler.hpp"
#include <unordered_map>
#include <functional>
#include "globalHashMap.hpp"
#include "Parser.hpp"
#include "SessionManager.hpp"
#include <iostream>
std::unordered_map<std::string, std::function<void(ClientRequestHandler&, const std::vector<std::string>&)>> Parser::commands;



void ClientRequestHandler::sendToClient(std::string message)
{
	currentSession.sendToClient(message);
	


}

std::vector<std::string> ClientRequestHandler::tokenize(const std::string& message)
{
	std::vector<std::string > tokens;
	std::istringstream iss(message);
	std::string token;
	while (iss >> token) {
		tokens.push_back(token);
	}
	return tokens;
}
void ClientRequestHandler::handleRequest(const std::string& message)
{
	std::vector<std::string> tokens = tokenize(message);
	/*for (const auto &it : tokens) {
		std::cout << it << std::endl;
	}*/
	if (tokens.size() == 0)
	{
		sendToClient("token array is empty");
		return;
	}
	else if (!Parser::commands.count(tokens[0]))
	{
		sendToClient("Invalid command");
		return;
	}
	else {
		Parser::commands[tokens[0]](*this, tokens);



	}
	
}

void ClientRequestHandler::sendToClientSync(std::string message)
{
	currentSession.sendToClientSync(message);
}


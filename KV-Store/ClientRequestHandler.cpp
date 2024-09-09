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
    std::vector<std::string> tokens;
    std::string token;
    bool inQuotes = false;
    bool escapeNext = false;

    for (char ch : message) {
        if (escapeNext) {
            // Handle escaped characters
            if (ch == '"' || ch == '\\') {
                token.push_back(ch);
            }
            else {
                // If escapeNext is true but character is not handled, just add the escape character
                token.push_back('\\');
                token.push_back(ch);
            }
            escapeNext = false;
        }
        else if (ch == '\\') {
            // Handle escape character
            escapeNext = true;
        }
        else if (ch == '"') {
            // Toggle quote flag
            inQuotes = !inQuotes;
            if (inQuotes) {
                // Start of quoted string, handle accordingly
                token.push_back(ch);
            }
            else {
                // End of quoted string
                token.push_back(ch);
                tokens.push_back(token);
                token.clear();
            }
        }
        else if (ch == ' ' && !inQuotes) {
            // Split on space outside of quotes
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        }
        else {
            // Normal character or part of quoted string
            token.push_back(ch);
        }
    }

    // Add last token if present
    if (!token.empty()) {
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
		//std::cout << "calling parser function" << std::endl;
		Parser::commands[tokens[0]](*this, tokens);
		//currentSession.getLineFromClient();



	}
	
}

void ClientRequestHandler::sendToClientSync(std::string message)
{
	currentSession.sendToClientSync(message);
}

int ClientRequestHandler::getSessionId() const
{
	return sessionId;
}

void ClientRequestHandler::killSession()
{
	currentSession.killSession();
}


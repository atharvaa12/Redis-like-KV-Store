#ifndef PARSER_HPP
#define PARSER_HPP
#include "ClientRequestHandler.hpp"
#include "GlobalHashMap.hpp"
#include <unordered_map>
#include <functional>
#include <iostream>
#include "ListsManager.hpp"

struct Parser {
	static std::unordered_map<std::string, std::function<void(ClientRequestHandler&, const std::vector<std::string>&)>> commands;
	Parser() {
		commands["get"] = [](ClientRequestHandler& handler, const std::vector<std::string>& tokens) {
			if (tokens.size() <2) {
				handler.sendToClient("Invalid number of arguments");
			}
			else {
				if (!GlobalHashMap::exists(tokens[1]))
				{
					
					handler.sendToClient("Key does not exist");
					std::cout << "sent not sure" << std::endl;

				}
				else
				{
					handler.sendToClient(GlobalHashMap::get(tokens[1]));
				}

			}
			};
		commands["exists"] = [](ClientRequestHandler& handler, const std::vector<std::string>& tokens) {
			if (tokens.size() <2) {
				handler.sendToClient("Invalid number of arguments");
			}
			else {
				if (GlobalHashMap::exists(tokens[1]))
				{
					handler.sendToClient("Key exists");
				}
				else
				{
					handler.sendToClient("Key does not exist");
				}

			}
			};
		commands["del"] = [](ClientRequestHandler& handler, const std::vector<std::string>& tokens) {
			if (tokens.size() < 2) {
				handler.sendToClient("Invalid number of arguments");
			}
			else {
				if (!GlobalHashMap::exists(tokens[1]))
				{
					handler.sendToClient("Key does not exist");
				}
				else
				{
					GlobalHashMap::del(tokens[1]);
					handler.sendToClient("Key deleted successfully");
				}

			}
			};
		commands["set"] = [](ClientRequestHandler& handler, const std::vector<std::string>& tokens) {
			if (tokens.size() < 3) {
				handler.sendToClient("Invalid number of arguments");
			}
			else {
				GlobalHashMap::set(tokens[1], tokens[2]);
				handler.sendToClient("Key set successfully");
			}
			};
		commands["q"] = [](ClientRequestHandler& handler, const std::vector<std::string>& tokens) {
			handler.sendToClientSync("Disconnected from server successfully");

			};
		commands["lpush"] = [](ClientRequestHandler& handler, const std::vector<std::string>& tokens) {
			if (tokens.size() < 3) {
				handler.sendToClient("Invalid number of arguments");
			}
			ListsManager::pushFront(tokens[1], tokens[2]);

			};
		commands["rpush"] = [](ClientRequestHandler& handler, const std::vector<std::string>& tokens) {
			if (tokens.size() < 3) {
				handler.sendToClient("Invalid number of arguments");
			}
			ListsManager::pushBack(tokens[1], tokens[2]);

			};
		commands["lpop"] = [](ClientRequestHandler& handler, const std::vector<std::string>& tokens) {
			if (tokens.size() < 2) {
				handler.sendToClient("Invalid number of arguments");
			}
			ListsManager::popFront(tokens[1]);

			};
		commands["rpop"] = [](ClientRequestHandler& handler, const std::vector<std::string>& tokens) {
			if (tokens.size() < 2) {
				handler.sendToClient("Invalid number of arguments");
			}
			ListsManager::popBack(tokens[1]);

			};



	}
};
#endif // !PARSER_HPP


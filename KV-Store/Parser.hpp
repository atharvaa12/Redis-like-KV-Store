#ifndef PARSER_HPP
#define PARSER_HPP
#include "ClientRequestHandler.hpp"
#include "GlobalHashMap.hpp"
#include <unordered_map>
#include <functional>
#include <iostream>
#include "ListsManager.hpp"
#include "SessionManager.hpp"
struct Parser {
	static std::unordered_map<std::string, std::function<void(ClientRequestHandler&, const std::vector<std::string>&)>> commands;
	static bool isInt(const std::string& s) {
		if (s.empty()) return false;
		int start = 0;
		if (s[0] == '-' || s[0] == '+') {
			if (s.size() == 1) return false;
			start = 1;

		}
		for (int i = start, j = s.size(); i < j; i++) {
			if (!std::isdigit(s[i])) return false;

		}
		try {
			std::size_t pos = 0;
			int num = std::stoi(s, &pos);
			if (pos != s.size()) return false;

		}
		catch (const std::invalid_argument&) {
			return false;
		}
		catch (std::out_of_range&) {
			return false;
		}
		return true;


	}
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
			
			
			handler.killSession();
			
			};
		commands["lpush"] = [](ClientRequestHandler& handler, const std::vector<std::string>& tokens) {
			if (tokens.size() < 3) {
				handler.sendToClient("Invalid number of arguments");
			}
			else {
				ListsManager::pushFront(tokens[1], tokens[2]);
				handler.sendToClient("Value pushed successfully");
			}

			};
		commands["rpush"] = [](ClientRequestHandler& handler, const std::vector<std::string>& tokens) {
			if (tokens.size() < 3) {
				handler.sendToClient("Invalid number of arguments");
			}
			else {
				ListsManager::pushBack(tokens[1], tokens[2]);
				handler.sendToClient("Value pushed successfully");
			}

			};
		commands["lpop"] = [](ClientRequestHandler& handler, const std::vector<std::string>& tokens) {
			if (tokens.size() < 2) {
				handler.sendToClient("Invalid number of arguments");
			}
			else {
				ListsManager::popFront(tokens[1]);
				handler.sendToClient("Value popped successfully");
			}

			};
		commands["rpop"] = [](ClientRequestHandler& handler, const std::vector<std::string>& tokens) {
			if (tokens.size() < 2) {
				handler.sendToClient("Invalid number of arguments");
			}
			else {
				ListsManager::popBack(tokens[1]);
				handler.sendToClient("Value popped successfully");
			}

			};
		commands["get-range"] = [](ClientRequestHandler& handler, const std::vector<std::string>& tokens) {
			if (tokens.size() < 4) {
				handler.sendToClient("Invalid number of arguments");
			}
			if (!isInt(tokens[2]) || !isInt(tokens[3]))
			{
				handler.sendToClient("Invalid arguments: Range must be a 32 bit number");
			}
			else {
				handler.sendToClient(ListsManager::getRange(tokens[1], std::stoi(tokens[2]), std::stoi(tokens[3])));
			}

			};
		commands["get-size"] = [](ClientRequestHandler& handler, const std::vector<std::string>& tokens) {
			if (tokens.size() < 2) {
				handler.sendToClient("Invalid number of arguments");
			}
			else if (!ListsManager::exists(tokens[1]))
			{
				handler.sendToClient("Key does not exist");
			}
			else {
				handler.sendToClient(std::to_string(ListsManager::getSize(tokens[1])));
			}

			};
		commands["get-list"] = [](ClientRequestHandler& handler, const std::vector<std::string>& tokens) {
			if (tokens.size() < 2) {
				handler.sendToClient("Invalid number of arguments");
			}
			else if (!ListsManager::exists(tokens[1]))
			{
				handler.sendToClient("Key does not exist");
			}
			else {
				int size = ListsManager::getSize(tokens[1]);
				std::string result=ListsManager::getRange(tokens[1],1,size);
				handler.sendToClient(result);
				
			}
			};
		


	}
};
#endif // !PARSER_HPP


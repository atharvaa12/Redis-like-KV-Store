#ifndef PARSER_HPP
#define PARSER_HPP
#include "ClientRequestHandler.hpp"
#include "GlobalHashMap.hpp"
#include <unordered_map>
#include <functional>
#include <iostream>
#include "ListsManager.hpp"
#include "SessionManager.hpp"
#include "LogQueue.hpp"
struct Parser {
	LogQueue* logQueuePtr;
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
	static bool isValidVal(const std::string& s) {
		return (s.size() >= 2 && s.front() == '"' && s.back() == '"');
	}
	Parser(LogQueue * lq) {
		logQueuePtr = lq;
		
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
		commands["del"] = [this](ClientRequestHandler& handler, const std::vector<std::string>& tokens) {
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
					std::string log;
					for (int i = 0; i < 2; i++) {
						log += tokens[i];
						log += " ";
					}
					logQueuePtr->push(log);
					handler.sendToClient("Key deleted successfully");
				}

			}
			};
		commands["set"] = [this](ClientRequestHandler& handler, const std::vector<std::string>& tokens) {
			if (tokens.size() < 3) {
				handler.sendToClient("Invalid number of arguments");
				return;
			}
			else if (!isValidVal(tokens[2]))
			{
				handler.sendToClient("Invalid arguments: Value must be inclosed within double quotes");
				return;
			}
			std::string val = tokens[2].substr(1, tokens[2].size() - 2);
			std::string log;
			if (tokens.size() == 3) {
				GlobalHashMap::set(tokens[1], val);
				for (int i = 0; i < 3; i++)
				{
					log += tokens[i];
					log += " ";
				}
				logQueuePtr->push(log);
				handler.sendToClient("Key set successfully");
			}
			
			else if (tokens.size() == 4) {
				if (isInt(tokens[3]))
				{
					GlobalHashMap::set(tokens[1], val, std::stoi(tokens[3]));
					for (int i = 0; i < 4; i++)
					{
						log += tokens[i];
						log += " ";
					}
					logQueuePtr->push(log);
					handler.sendToClient("Key set successfully");
				}
				else
				{
					handler.sendToClient("Invalid arguments: TTL must be a 32 bit number");
				}
			}
			else {
				handler.sendToClient("extra arguments provided");
			}
			};
			
		commands["q"] = [](ClientRequestHandler& handler, const std::vector<std::string>& tokens) {
			
			
			handler.killSession();
			
			};
		commands["lpush"] = [this](ClientRequestHandler& handler, const std::vector<std::string>& tokens) {
			if (tokens.size() < 3) {
				handler.sendToClient("Invalid number of arguments");
				return;
			}
			else if (!isValidVal(tokens[2]))
			{
				handler.sendToClient("Invalid arguments: Value must be inclosed within double quotes");
				return;
			}
			std::string val = tokens[2].substr(1, tokens[2].size() - 2);
			
				ListsManager::pushFront(tokens[1], val);
				std::string log;
				for (int i = 0; i < 3; i++) {
					log += tokens[i];
					log += " ";
				}
				logQueuePtr->push(log);
				handler.sendToClient("Value pushed successfully");
			

			};
		commands["rpush"] = [this](ClientRequestHandler& handler, const std::vector<std::string>& tokens) {
			if (tokens.size() < 3) {
				handler.sendToClient("Invalid number of arguments");
				return;
			}
			else if (!isValidVal(tokens[2])) {
				handler.sendToClient("Invalid arguments: Value must be inclosed within double quotes");
				return;
			}
			std::string val = tokens[2].substr(1, tokens[2].size() - 2);
				ListsManager::pushBack(tokens[1], val);
				std::string log;
				for (int i = 0; i < 3; i++) {
					log += tokens[i];
					log += " ";
				}
				logQueuePtr->push(log);
				handler.sendToClient("Value pushed successfully");
			

			};
		commands["lpop"] = [this](ClientRequestHandler& handler, const std::vector<std::string>& tokens) {
			if (tokens.size() < 2) {
				handler.sendToClient("Invalid number of arguments");
			}
			else {
				ListsManager::popFront(tokens[1]);
				std::string log;
				for (int i = 0; i < 2; i++) {
					log += tokens[i];
					log += " ";
				}
				logQueuePtr->push(log);
				handler.sendToClient("Value popped successfully");
			}

			};
		commands["rpop"] = [this](ClientRequestHandler& handler, const std::vector<std::string>& tokens) {
			if (tokens.size() < 2) {
				handler.sendToClient("Invalid number of arguments");
			}
			else {
				ListsManager::popBack(tokens[1]);
				std::string log;
				for (int i = 0; i < 2; i++)
				{
					log += tokens[i];
					log += " ";
				}
				logQueuePtr->push(log);
				handler.sendToClient("Value popped successfully");
			}

			};
		commands["get-range"] = [](ClientRequestHandler& handler, const std::vector<std::string>& tokens) {
			if (tokens.size() < 4) {
				std::cout << "inside get-range" << std::endl;
				handler.sendToClient("Invalid number of arguments");
			}
			
			else if (!isInt(tokens[2]) || !isInt(tokens[3]))
			{
				handler.sendToClient("Invalid arguments: Range must be a 32 bit number");
			}
			else if (!ListsManager::exists(tokens[1]))
			{
				handler.sendToClient("Key does not exist");
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
		commands["set-ttl-list"] = [this](ClientRequestHandler& handler, const std::vector<std::string>& tokens) {
			if (tokens.size() < 3) {
				handler.sendToClient("Invalid number of arguments");
			}
			else if (!isInt(tokens[2]))
			{
				handler.sendToClient("Invalid arguments: TTL must be a 32 bit number");
			}
			else if (!ListsManager::exists(tokens[1]))
			{
				handler.sendToClient("Key does not exist");
			}
			
			
			else {
				ListsManager::setTtl(tokens[1], std::stoi(tokens[2]));
				std::string log;
				for (int i = 0; i < 3; i++) {
					log += tokens[i];
					log += " ";
				}
				logQueuePtr->push(log);
				handler.sendToClient("TTL set successfully");
			}

			};
		


	}
};
#endif // !PARSER_HPP


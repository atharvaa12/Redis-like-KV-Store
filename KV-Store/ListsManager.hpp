#ifndef LISTS_MANAGER_HPP
#define LISTS_MANAGER_HPP
#include <unordered_map>
#include <string>
#include <list>
#include <memory>
#include <chrono>
class ListsManager {
private:
	static std::unordered_map<std::string,	std::unique_ptr< std::list<std::string>>> lists;
	static std::unordered_map<std::string, std::chrono::steady_clock::time_point> ttlMap;
	static void ttlCheck(const std::string& key);
public:
	static void pushFront(const std::string& key, const std::string& value);
	
	static void pushBack(const std::string& key, const std::string& value);
	static void popFront(const std::string& key);
	static void popBack(const std::string& key);
	static void setTtl(const std::string& key, int ttl);
	static std::string getRange(const std::string& key, int start, int end);
	static int getSize(const std::string& key);
	static bool exists(const std::string& key);
	



};
#endif

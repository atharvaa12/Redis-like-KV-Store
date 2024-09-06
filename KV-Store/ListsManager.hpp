#ifndef LISTS_MANAGER_HPP
#define LISTS_MANAGER_HPP
#include <unordered_map>
#include <string>
#include <list>
#include <memory>
class ListsManager {
private:
	static std::unordered_map<std::string,	std::unique_ptr< std::list<std::string>>> lists;
public:
	static void pushFront(const std::string& key, const std::string& value);
	static void pushBack(const std::string& key, const std::string& value);
	static void popFront(const std::string& key);
	static void popBack(const std::string& key);
	static std::string getRange(const std::string& key, int start, int end);



};
#endif

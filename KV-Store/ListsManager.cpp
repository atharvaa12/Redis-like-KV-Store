#include "ListsManager.hpp"
std::unordered_map<std::string, std::unique_ptr<std::list<std::string>>> ListsManager::lists;
void ListsManager::pushFront(const std::string& key, const std::string& value)
{
	if (lists.find(key) == lists.end())
	{
		lists[key] = std::make_unique<std::list<std::string>>();
		lists[key]->push_front(value);
	}
	lists[key]->push_front(value);
}
void ListsManager::pushBack(const std::string& key, const std::string& value)
{
	if (lists.find(key) == lists.end())
	{
		lists[key] = std::make_unique<std::list<std::string>>();
		lists[key]->push_back(value);
	}
	lists[key]->push_back(value);
}
void ListsManager::popFront(const std::string& key)
{
	if (lists.find(key) == lists.end())
	{
		return;
	}
	lists[key]->pop_front();
}
void ListsManager::popBack(const std::string& key)
{
	if (lists.find(key) == lists.end())
	{
		return;
	}
	lists[key]->pop_back();
}

std::string ListsManager::getRange(const std::string& key, int start, int end)
{	
	std::string result;
	if (start > end)
	{
		return result;
	}
	auto it = lists[key]->begin();
	int i = 1;
	while (it != lists[key]->end() && i < start)
	{
		it++;
		i++;
	}
	while (it != lists[key]->end() && i <= end)
	{
		result += *it + " ";
		it++;
		i++;
	}
	return result;
}

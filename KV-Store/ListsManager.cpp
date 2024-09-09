#include "ListsManager.hpp"
std::unordered_map<std::string, std::unique_ptr<std::list<std::string>>> ListsManager::lists;
std::unordered_map<std::string, std::chrono::steady_clock::time_point> ListsManager::ttlMap;
void ListsManager::ttlCheck(const std::string& key)
{
	auto now = std::chrono::steady_clock::now();
	if (ttlMap.find(key) != ttlMap.end())
	{
		if (now >= ttlMap[key])
		{
			lists.erase(key);
			ttlMap.erase(key);
		}
	}
}
void ListsManager::pushFront(const std::string& key, const std::string& value)
{
	if (lists.find(key) == lists.end())
	{
		lists[key] = std::make_unique<std::list<std::string>>();
		
	}
	
		lists[key]->push_front(value);
	
}
void ListsManager::pushBack(const std::string& key, const std::string& value)
{
	if (lists.find(key) == lists.end())
	{
		lists[key] = std::make_unique<std::list<std::string>>();
		
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
	if (lists[key]->empty())
	{
		lists.erase(key);
	}
}
void ListsManager::popBack(const std::string& key)
{
	if (lists.find(key) == lists.end())
	{
		
		return;
	}
	lists[key]->pop_back();
	if (lists[key]->empty())
	{
		lists.erase(key);
	}
}

void ListsManager::setTtl(const std::string& key, int ttl)
{
	auto now = std::chrono::steady_clock::now();
	ttlMap[key] = now + std::chrono::seconds(ttl);

}

std::string ListsManager::getRange(const std::string& key, int start, int end)
{
	
	std::string result;
	if (start > end || !lists.count(key))
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

int ListsManager::getSize(const std::string& key)
{
	return lists[key]->size();
}

bool ListsManager::exists(const std::string& key)
{
	ttlCheck(key);
	return lists.count(key);
}

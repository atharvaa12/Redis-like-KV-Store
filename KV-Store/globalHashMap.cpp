#include "globalHashMap.hpp"
std::unordered_map<std::string, std::string> GlobalHashMap::globalHashMap;
std::unordered_map<std::string, std::chrono::time_point<std::chrono::steady_clock>> GlobalHashMap::ttlMap;

void GlobalHashMap::ttlCheck(const std::string& key)
{
	auto now = std::chrono::steady_clock::now();
	if (ttlMap.find(key) != ttlMap.end())
	{
		if (now >= ttlMap[key])
		{
			globalHashMap.erase(key);
			ttlMap.erase(key);
		}
	}

}

std::string GlobalHashMap::get(const std::string& key)
{
	ttlCheck(key);
	return globalHashMap[key];
}
void GlobalHashMap::set(const std::string& key, const std::string& value)
{
	globalHashMap[key] = value;
}

void GlobalHashMap::set(const std::string& key, const std::string& value, int ttl)
{
	auto now = std::chrono::steady_clock::now();
	ttlMap[key] = now + std::chrono::seconds(ttl);
	set(key, value);
}
void GlobalHashMap::del(const std::string& key)
{
	
	globalHashMap.erase(key);
	
}
bool GlobalHashMap::exists(const std::string& key)
{
	ttlCheck(key);
	return globalHashMap.find(key) != globalHashMap.end();
}

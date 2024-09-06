#include "globalHashMap.hpp"
std::unordered_map<std::string, std::string> GlobalHashMap::globalHashMap;
std::string GlobalHashMap::get(const std::string& key)
{
	return globalHashMap[key];
}
void GlobalHashMap::set(const std::string& key, const std::string& value)
{
	globalHashMap[key] = value;
}
void GlobalHashMap::del(const std::string& key)
{
	
	globalHashMap.erase(key);
	
}
bool GlobalHashMap::exists(const std::string& key)
{
	return globalHashMap.find(key) != globalHashMap.end();
}

#ifndef GLOBAL_HASHMAP_HPP
#define GLOBAL_HASHMAP_HPP
#include <unordered_map>
#include<string>
#include<chrono>
class GlobalHashMap {
private:
	static std::unordered_map<std::string, std::string> globalHashMap;
	static std::unordered_map<std::string, std::chrono::steady_clock::time_point> ttlMap;
	static void ttlCheck(const std::string &key);
	
public:
	static std::string get(const std::string& key);
	static void set(const std::string& key, const std::string& value);
	static void set(const std::string& key, const std::string& value, int ttl);
	static void del(const std::string& key);
	static bool exists(const std::string& key);



};
#endif // !GLOBAL_HASHMAP_HPP


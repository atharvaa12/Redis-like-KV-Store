#ifndef GLOBAL_HASHMAP_HPP
#define GLOBAL_HASHMAP_HPP
#include <unordered_map>
#include<string>
class GlobalHashMap {
private:
	static std::unordered_map<std::string, std::string> globalHashMap;
public:
	static std::string get(const std::string& key);
	static void set(const std::string& key, const std::string& value);
	static void del(const std::string& key);
	static bool exists(const std::string& key);

};
#endif // !GLOBAL_HASHMAP_HPP


#ifndef LOGGER_HPP
#define LOGGER_HPP
#include <string>
#include <fstream>
#include<queue>
#include<mutex>
#include <string>
class LogQueue {
private:
	std::queue<std::string> logQueue;
	std::mutex logQueueMutex;
	std::condition_variable logQueueCV;
	
public:
	void push(const std::string& log);
	
	std::string pop();
	
	void handleLogQueue();
	LogQueue* getPtr();

		
};
#endif
#include "LogQueue.hpp"

#include<iostream>

void LogQueue::push(const std::string& log)
{
	{
		std::lock_guard<std::mutex> lock(logQueueMutex);
		logQueue.push(log);
	}
	logQueueCV.notify_one();
}

std::string LogQueue::pop()
{
	std::string result;
	{
		std::unique_lock<std::mutex> lock(logQueueMutex);
		logQueueCV.wait(lock, [this] {return !logQueue.empty(); });
		result = logQueue.front();
		logQueue.pop();
	}
	
	return result;
}

void LogQueue::handleLogQueue()
{
	std::ofstream logFile("AOF.log", std::ios::app);
	if (!logFile.is_open())
	{
		std::cerr << "Error opening log file" << std::endl;
		return;
	}
	while (true)
	{
		std::string log;
		
			
			log = pop();
		
		if (log == "q") {
			break;
		}
		std::cout << "logging: " << log << std::endl;
		logFile << log << std::endl;
	}
	logFile.close();
}

LogQueue* LogQueue::getPtr()
{
	return this;
}

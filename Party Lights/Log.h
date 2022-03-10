#pragma once

#include <string>
#include <fstream>
#include <filesystem>

class Log {
public:
	static void OpenLog();
	static void AddLog(std::string line);
};

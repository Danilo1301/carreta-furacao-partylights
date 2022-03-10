#include "Log.h"

std::ofstream LogStream;

std::string PluginPath = std::string(std::filesystem::current_path().string() + "");

std::string GetPath() {
	return PluginPath;
};

void Log::OpenLog() {
	LogStream.open(std::string(GetPath() + "\\PartyLights.log").c_str(), std::fstream::out | std::fstream::trunc);
	LogStream.close();
}

void Log::AddLog(std::string line) {
	LogStream.open(std::string(GetPath() + "\\PartyLights.log").c_str(), std::fstream::app);
	LogStream << line << "\n";
	LogStream.close();
};
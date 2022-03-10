#include "Settings.h"

#include <json/json.h>
#include <fstream>

float Settings::clublightTransparency = 0.7f;
float Settings::lightIntensity = 0.8f;
bool Settings::useLightFlare = true;
float Settings::coronaRadius = 1.0f;

void Settings::LoadJson() {
	auto ppath = std::filesystem::current_path().string();
	auto path = std::string(ppath) + "\\config.json";

	Log::AddLog(path.c_str());

	std::ifstream file(path);

	Json::Value cfg;
	Json::Reader reader;

	if (!reader.parse(file, cfg, true)) {
		std::string errormsg = "Failed to parse configuration\n" + reader.getFormattedErrorMessages();

		MessageBox(HWND_DESKTOP, errormsg.c_str(), "", MB_ICONERROR);
	}
	
	
	clublightTransparency = cfg["clublightTransparency"].asFloat();
	lightIntensity = cfg["lightIntensity"].asFloat();
	useLightFlare = cfg["useLightFlare"].asBool();
	coronaRadius = cfg["coronaRadius"].asFloat();
	

	Log::AddLog("Loaded");
}
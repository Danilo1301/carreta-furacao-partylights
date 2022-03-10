#pragma once

#include "pch.h"

class Settings {
public:
	static float clublightTransparency;
	static float lightIntensity;
	static bool useLightFlare;
	static float coronaRadius;

	static void LoadJson();
};
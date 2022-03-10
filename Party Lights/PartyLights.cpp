#include "PartyLights.h"
#include "SpotLights.h"
#include "Leds.h"
#include "Settings.h"

void PartyLights::Update() {
	Leds::Update();
	SpotLights::Update();
}

void PartyLights::Draw() {
	SpotLights::Draw();
}

PartyLights::PartyLights() {
	Log::OpenLog();
	Log::AddLog("Init");

	Settings::LoadJson();

	SpotLights::Initialize();
	Leds::Initialize();

	Events::processScriptsEvent += Update;
	Events::drawingEvent += Draw;
}

PartyLights mod;

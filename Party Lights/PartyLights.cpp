#include "PartyLights.h"
#include "SpotLights.h"
#include "Leds.h"

void PartyLights::Update() {
	Leds::Update();
	SpotLights::Update();
}

void PartyLights::Draw() {
	SpotLights::Draw();
}

PartyLights::PartyLights() {
	SpotLights::Initialize();
	Leds::Initialize();

	Events::processScriptsEvent += Update;
	Events::drawingEvent += Draw;
}

PartyLights mod;

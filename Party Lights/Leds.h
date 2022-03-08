#pragma once

#include "pch.h"
#include "Led.h"

class Leds {
public:
	static CRGBA m_LedColors[3];
	static std::vector<Led*> m_Leds;
	static std::list<std::pair<unsigned int*, unsigned int>> m_ResetEntries;

	static void Initialize();
	static void Update();
	static void RenderVehicleLeds(CVehicle* vehicle);
	static void ApplyLedColor(Led* led, RpMaterial* material);
	static void AddLed(int offset, float interval, bool slowColorTransition = false);
};
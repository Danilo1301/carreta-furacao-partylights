#pragma once

#include "pch.h"
#include "SpotLight.h"

class SpotLights {
public:
	static std::map<CVehicle*, int> SpotLights::m_NumCoronasRegistered;
	static std::vector<SpotLight*> m_SpotLights;

	static void Initialize();
	static void Update();
	static void Draw();
	static SpotLight* AddSpotLight(CVehicle* vehicle, CVector position, int ledIndex);
	static void RemoveSpotLight(SpotLight* spotlight);
	static int GetNumOfSpotlightsInVehicle(CVehicle* vehicle);

private:
	static void ForceRemoveSpotLight(SpotLight* spotlight);
	static void RemoveSpotLightFromVehicles();
	static void SetObjectColorFromSpotLight(CObject* object, SpotLight* spotlight);
	static void FindDummies(CVehicle* vehicle, RwFrame* frame, bool parent);
};
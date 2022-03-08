#include "Leds.h"

std::vector<Led*> Leds::m_Leds;

CRGBA Leds::m_LedColors[3] = {
	CRGBA(255, 0, 0),
	CRGBA(0, 255, 0),
	CRGBA(0, 0, 255),
};

std::list<std::pair<unsigned int*, unsigned int>> Leds::m_ResetEntries;

void Leds::Initialize() {
	AddLed(0, 200);
	AddLed(1, 200);
	AddLed(2, 200);
	AddLed(3, 300, true);

	Events::vehicleRenderEvent.before += [](CVehicle* vehicle) {
		Leds::RenderVehicleLeds(vehicle);
	};

	Events::vehicleRenderEvent.after += [](CVehicle* ped) {
		for (auto& p : m_ResetEntries) *p.first = p.second;
		m_ResetEntries.clear();
	};
}

void Leds::Update() {
	for (Led* led : m_Leds) led->Update();
}

void Leds::RenderVehicleLeds(CVehicle* vehicle) {
	if (vehicle->m_nModelIndex == 591 || vehicle->m_nModelIndex == 514) {
		if (vehicle->m_pRwClump && vehicle->m_pRwClump->object.type == rpCLUMP) {
			RpClumpForAllAtomics(vehicle->m_pRwClump, [](RpAtomic* atomic, void* data) {
				if (atomic->geometry) {
					atomic->geometry->flags |= rpGEOMETRYMODULATEMATERIALCOLOR;

					RpGeometryForAllMaterials(atomic->geometry, [](RpMaterial* material, void* data) {
						if (material->texture > 0) {
							std::string textureName = material->texture->name;

							if (textureName.find("lights1") != std::string::npos) ApplyLedColor(Leds::m_Leds[0], material);
							if (textureName.find("lights2") != std::string::npos) ApplyLedColor(Leds::m_Leds[1], material);
							if (textureName.find("lights3") != std::string::npos) ApplyLedColor(Leds::m_Leds[2], material);
							if (textureName.find("lights4") != std::string::npos) ApplyLedColor(Leds::m_Leds[3], material);
						}
						return material;
						}, 0);
				}
				return atomic;
				}, 0);
		}
	}
}

void Leds::ApplyLedColor(Led* led, RpMaterial* material) {
	CRGBA color = led->color;

	m_ResetEntries.push_back(std::make_pair(reinterpret_cast<unsigned int*>(&material->color), *reinterpret_cast<unsigned int*>(&material->color)));

	material->color = { color.r, color.g, color.b, color.a };
}

void Leds::AddLed(int offset, float interval, bool slowColorTransition) {
	Led* led = new Led();
	led->currentColorIndex = offset;
	led->changeColorInterval = interval;
	led->slowColorTransition = slowColorTransition;
	m_Leds.push_back(led);
}
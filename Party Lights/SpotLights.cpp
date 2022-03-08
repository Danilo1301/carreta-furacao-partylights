#include "SpotLights.h"
#include "Leds.h"

std::map<CVehicle*, int> SpotLights::m_NumCoronasRegistered;
std::vector<SpotLight*> SpotLights::m_SpotLights;

void SpotLights::Initialize() {
	Events::objectRenderEvent.before += [](CObject* object) {
		SpotLight* spotlight = NULL;

		for (auto s : m_SpotLights) {
			if (s->m_Object == object) {
				spotlight = s;
				break;
			}
		}

		if (spotlight == NULL) return;

		SetObjectColorFromSpotLight(object, spotlight);
	};

	Events::vehicleDtorEvent.after += [](CVehicle* vehicle) {
		for (SpotLight* spotlight : m_SpotLights) {
			if (spotlight->m_Vehicle == vehicle) RemoveSpotLight(spotlight);
		}
	};
}

void SpotLights::Update() {
	AddSpotLightToVehicles();
	RemoveSpotLightFromVehicles();

	static char text[256] = "";
	snprintf(text, sizeof(text), "Spotlights: ");

	for each (SpotLight* spotlight in m_SpotLights) {
		snprintf(text, sizeof(text), "%s %p", text, spotlight->m_Object);

		spotlight->Update();
		spotlight->RenderCoronas();
	}
	//CMessages::AddMessageJumpQ(text, 500, 0, false);

	m_NumCoronasRegistered.clear();
}

void SpotLights::Draw() {
	for (SpotLight* spotlight : m_SpotLights) spotlight->Draw();
}

SpotLight* SpotLights::AddSpotLight(CVehicle* vehicle, CVector position, int ledIndex) {
	SpotLight* spotlight = new SpotLight(vehicle, position);
	spotlight->ledIndex = ledIndex;
	spotlight->targetA = ledIndex % 2 == 0 ? 1 : -1;
	m_SpotLights.push_back(spotlight);
	return spotlight;
}


void SpotLights::RemoveSpotLight(SpotLight* spotlight) {
	spotlight->canBeDeleted = true;
}

void SpotLights::ForceRemoveSpotLight(SpotLight* spotlight) {
	spotlight->Destroy();
	m_SpotLights.erase(std::find(m_SpotLights.begin(), m_SpotLights.end(), spotlight));
	delete spotlight;
}

int SpotLights::GetNumOfSpotlightsInVehicle(CVehicle* vehicle) {
	int count = 0;
	for each (SpotLight* spotlight in m_SpotLights) {
		if (vehicle == spotlight->m_Vehicle) count++;
	}
	return count;
}

void SpotLights::AddSpotLightToVehicles() {
	for (auto vehicle : CPools::ms_pVehiclePool) {
		if (vehicle->m_nModelIndex != 591) continue;

		if (SpotLights::GetNumOfSpotlightsInVehicle(vehicle) == 0) {
			SpotLights::AddSpotLight(vehicle, CVector(0.0f, 3.9978f, 2.92894f), 0);
			SpotLights::AddSpotLight(vehicle, CVector(0.0f, -3.37178, 2.92894f), 1);
			SpotLights::AddSpotLight(vehicle, CVector(0.0f, 1.67875, 0.827247), 1);
			SpotLights::AddSpotLight(vehicle, CVector(0.0f, -1.57401, 0.827247), 2);
		}
	}
}

void SpotLights::RemoveSpotLightFromVehicles() {
	std::vector<SpotLight*> toremove;

	for each (SpotLight * spotlight in m_SpotLights) {
		if (spotlight->canBeDeleted) toremove.push_back(spotlight);
	}

	for each (SpotLight * spotlight in toremove) {
		ForceRemoveSpotLight(spotlight);
	}
}

void SpotLights::SetObjectColorFromSpotLight(CObject* object, SpotLight* spotlight) {
	static SpotLight* s_spotlight;

	s_spotlight = spotlight;

	if (object->m_pRwObject->type == rpCLUMP) {
		RpClumpForAllAtomics(reinterpret_cast<RpClump*>(object->m_pRwObject), [](RpAtomic* atomic, void* data) {
			if (atomic->geometry) {
				atomic->geometry->flags |= rpGEOMETRYMODULATEMATERIALCOLOR;
				RpGeometryForAllMaterials(atomic->geometry, [](RpMaterial* material, void* data) {

					Led* led = Leds::m_Leds[s_spotlight->ledIndex];
					material->color = { led->color.r, led->color.g, led->color.b, led->color.a };

					return material;
					}, 0);
			}

			return atomic;
			}, 0);
	}
	else {
		RpAtomic* atomic = reinterpret_cast<RpAtomic*>(object->m_pRwObject);

		if (atomic->geometry) {
			atomic->geometry->flags |= rpGEOMETRYMODULATEMATERIALCOLOR;
			RpGeometryForAllMaterials(atomic->geometry, [](RpMaterial* material, void* color) {

				Led* led = Leds::m_Leds[s_spotlight->ledIndex];
				material->color = { led->color.r, led->color.g, led->color.b, led->color.a };

				return material;
				}, 0);
		}
	}
}
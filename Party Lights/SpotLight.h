#pragma once

#include "pch.h"

class SpotLight {
public:
	CVehicle* m_Vehicle;
	CVector m_Position;
	CObject* m_Object;

	bool canBeDeleted = false;
	int ledIndex = 0;

	float a = 0;
	float targetA = 0;
	float b = 0;
	float targetB = 0;

	SpotLight(CVehicle* vehicle, CVector position);

	void Update();
	void Draw();
	void Destroy();
	void RenderCoronas();
	CVector GetWorldSpace(CVector offset);
	void PointAtOffset(CVector offset);
	void UpdateSpotlightPosition();
	void RegisterCorona(int lightid, CVector position, CRGBA color);
};
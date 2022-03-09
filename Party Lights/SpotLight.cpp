#include "SpotLight.h"
#include "SpotLights.h"
#include "Leds.h"

SpotLight::SpotLight(CVehicle* vehicle, CVector position) {
	m_Vehicle = vehicle;
	m_Position = position;

	Command<Commands::CREATE_OBJECT_NO_OFFSET>(14870, 0, 0, 0, &m_Object);
	Command<Commands::ATTACH_OBJECT_TO_CAR>(m_Object, m_Vehicle, position.x, position.y, position.z, 0.0f, 0.0f, 0.0f);

	UpdateSpotlightPosition();
}

void SpotLight::Update() {
	float addBy = 0.4f;
	double maxRad = M_PI / 3;

	if (abs(targetA - a) <= 0.2f) targetA = maxRad * (targetA > 0 ? -1 : 1) * (0.4f);
	a = lerp(a, targetA, 0.03f);

	if (abs(targetB - b) <= 0.2f) targetB = maxRad * (targetB > 0 ? -1 : 1) * ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)));
	b = lerp(b, targetB, 0.03f);

	UpdateSpotlightPosition();
}

void SpotLight::Draw() {
	/*
	char text[256];
	sprintf(text, "a=%.4f / %.4f b=%.4f / %.4f", a,targetA,  b,targetB);
	CVector pos = GetWorldSpace(CVector());
	DrawWorldText(text, pos, CRGBA(255, 255, 255));
	*/
}

void SpotLight::Destroy() {

	Command<0x0682>(m_Object, 0.0f, 0.0f, 0.0f, false);
	Command<0x0108>(m_Object);
	//Command<0x09A2>(m_Object);
}

void SpotLight::RenderCoronas() {
	if (!SpotLights::m_NumCoronasRegistered[m_Vehicle]) 
		SpotLights::m_NumCoronasRegistered.insert(std::pair<CVehicle*, int>(m_Vehicle, 0));
	
	SpotLights::m_NumCoronasRegistered[m_Vehicle]++;

	int id = reinterpret_cast<unsigned int>(m_Vehicle) + 40 + SpotLights::m_NumCoronasRegistered[m_Vehicle];
	Led* led = Leds::m_Leds[ledIndex];

	RegisterCorona(id, m_Position, led->color, 1.0f);
}

CVector SpotLight::GetWorldSpace(CVector offset) {
	CVector spotlightPos = m_Vehicle->TransformFromObjectSpace(m_Position + offset + CVector(0, 0, 0));
	return spotlightPos;
}

void SpotLight::UpdateSpotlightPosition() {
	m_Object->m_fScale = 0.03f;
	m_Object->m_qAttachedEntityRotation.Set(0, 0.0f - b, -M_PI/2 + a);
}

void SpotLight::RegisterCorona(int lightid, CVector position, CRGBA color, float radius) {
	CCoronas::RegisterCorona(
		lightid,
		m_Vehicle,
		color.r,
		color.g,
		color.b,
		200,
		position,
		radius,
		100.0f,
		eCoronaType::CORONATYPE_SHINYSTAR,
		eCoronaFlareType::FLARETYPE_SUN,
		false,
		false,
		0,
		0.0f,
		false,
		0.1f,
		0,
		15.0f,
		false,
		false
	);

	CVector fposition = m_Vehicle->TransformFromObjectSpace(position);
	Command< 0x09E5 >(fposition.x, fposition.y, fposition.z, (int)color.r, (int)color.g, (int)color.b, 20.0f);
}

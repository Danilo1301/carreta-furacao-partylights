#pragma once

#include <iomanip>
#include <iostream>
#include <map>
#include <math.h>
#include <fstream>
#include <filesystem>

#include "plugin.h"

#include "CPed.h"
#include "RenderWare.h"
#include "CSprite.h"
#include "CFont.h"
#include "common.h"
#include "CRadar.h"
#include "CMenuManager.h"
#include "CFont.h"
#include "CSprite.h"
#include "CTimer.h"
#include "CMessages.h"
#include "CCoronas.h"

#include "extensions/ScriptCommands.h"

#include "Log.h"

#define M_PI 3.14159265358979323846

using namespace plugin;

//static std::ofstream log_file("log.txt", std::ios_base::app);

static float lerp(float a, float b, float f) {
	return a + f * (b - a);
}

static unsigned char ucharIntensity(unsigned char uc, float intensity) {
	return (unsigned char)std::clamp((int)round( ((float)uc) * intensity ), 0, 255);
}

static void DrawWorldText(char* text, CVector position, CRGBA color = CRGBA(0, 255, 0, 255)) {
	CFont::SetOrientation(ALIGN_CENTER);
	CFont::SetColor(color);
	CFont::SetDropShadowPosition(1);
	CFont::SetBackground(false, false);
	CFont::SetWrapx(500.0);
	CFont::SetScale(0.5, 1.0);
	CFont::SetFontStyle(FONT_SUBTITLES);
	CFont::SetProportional(true);

	RwV3d rwp = { position.x, position.y, position.z };
	RwV3d screenCoors; float w, h;

	CSprite::CalcScreenCoors(rwp, &screenCoors, &w, &h, true, true);
	CFont::PrintString(screenCoors.x, screenCoors.y, text);
}


static void DrawScreenText(char* text, CVector2D position, CRGBA color = CRGBA(0, 255, 0, 255)) {
	CFont::SetOrientation(ALIGN_CENTER);
	CFont::SetColor(color);
	CFont::SetDropShadowPosition(1);
	CFont::SetBackground(false, false);
	CFont::SetWrapx(500.0);
	CFont::SetScale(0.5, 1.0);
	CFont::SetFontStyle(FONT_SUBTITLES);
	CFont::SetProportional(true);

	CFont::PrintString(position.x, position.y, text);
}

static float distance3d(float x1, float y1, float z1, float x2, float y2, float z2) {
	float d = (float)sqrt(pow(x2 - x1, 2) +
		pow(y2 - y1, 2) +
		pow(z2 - z1, 2) * 1.0);
	std::cout << std::fixed;
	std::cout << std::setprecision(2);
	return d;
}

static void DrawObjects() {
	for (auto obj : CPools::ms_pObjectPool)
	{
		auto pos = obj->GetPosition();

		char text[256];
		sprintf(text, "%d", obj->m_nModelIndex);
		DrawWorldText(text, pos, CRGBA(255, 255, 255));
	}
}

static char* (*GetFrameNodeName)(RwFrame* frame) = (char* (*)(RwFrame*))0x72FB30;
#pragma once

#include "pch.h"

class Led {
public:
	float changeColorInterval = 1000;
	bool slowColorTransition = false;

	int currentColorIndex = 0;
	unsigned int lastChangedColor = 0;
	CRGBA color = CRGBA(255, 255, 255);

	void Update();
};
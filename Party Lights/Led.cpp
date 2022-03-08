#include "Led.h"
#include "Leds.h"

void Led::Update() {
	unsigned int now = CTimer::m_snTimeInMilliseconds;

	if (lastChangedColor == 0) lastChangedColor = now;

	unsigned int dt = now - lastChangedColor;

	if (dt >= changeColorInterval) {
		lastChangedColor = now;

		currentColorIndex++;
		if (currentColorIndex >= 3) currentColorIndex = 0;
	}

	CRGBA targetColor = Leds::m_LedColors[currentColorIndex];

	color.r = targetColor.r;
	color.g = targetColor.g;
	color.b = targetColor.b;
	color.a = targetColor.a;

	if (slowColorTransition) {
		float c = min(dt, changeColorInterval) / changeColorInterval;

		color.r = (unsigned char)round(color.r * c);
		color.g = (unsigned char)round(color.g * c);
		color.b = (unsigned char)round(color.b * c);
	}
}
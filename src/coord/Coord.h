#pragma once

#include "sampapi/CVector.h"
#include "dllmain.h"

namespace Coord {
	extern bool enabled;
	extern sampapi::CVector endPoint;
	extern sampapi::CVector currentPoint;
	extern float speed[];
	extern float stepMultiplier;
	extern DWORD delay;
	extern DWORD timeSinceLastUpdate;
	extern DWORD forceDelay;
	extern DWORD timeSinceLastForce;

	void OnUpdate();
}
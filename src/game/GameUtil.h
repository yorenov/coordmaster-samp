#pragma once

#include "dllmain.h"
#include "sampapi/CVector.h"
#include "sampapi/CPed.h"
#include "sampapi/CNetGame.h"

namespace GameUtil {
	bool GetMarkerPosition(sampapi::CVector* position);
	void GetCorrectedPosition(sampapi::CVector* position);
	void LoadScene(sampapi::CVector* position);
	void LoadSceneCollision(sampapi::CVector* position);
	double FindGroundZForCoord(float fX, float fY);
	sampapi::ID GetPlayerVehicleId();
	sampapi::v037r3::CVehicle* GetPlayerVehicle();
	bool IsPlayerInVehicle();
	bool IsPlayerDriver();
	float GetDistance(sampapi::CVector* firstPoint, sampapi::CVector* secondPoint);
	float GetAngle(sampapi::CVector* firstPoint, sampapi::CVector* secondPoint);
}
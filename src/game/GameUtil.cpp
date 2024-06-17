#include "GameUtil.h"
#include <corecrt_math_defines.h>

namespace GameUtil {

	bool GetMarkerPosition(sampapi::CVector* position) {
		if (*(int*)0xBA6774 == 0) return false;

		for (int i = 0; i < (0xAF * 0x28); i += 0x28)
		{
			if (*(short*)(0xBA873D + i) == 4611)
			{
				auto* pos = (float*)(0xBA86F8 + 0x28 + i);
				position->x = *pos;
				position->y = *(pos + 1);
				position->z = 999;
				GetCorrectedPosition(position);

				return true;
			}
		}

		return false;
	}

	void GetCorrectedPosition(sampapi::CVector* position) {
		LoadScene(position);
		LoadSceneCollision(position);
		position->z = FindGroundZForCoord(position->x, position->y);
	}

	void LoadScene(sampapi::CVector* position) {
		return ((void (__cdecl*)(sampapi::CVector*))0x40EB70)(position);
	}

	void LoadSceneCollision(sampapi::CVector* position) {
		return ((void(__cdecl*)(sampapi::CVector*))0x40ED80)(position);
	}

	double FindGroundZForCoord(float fX, float fY) {
		return ((double(__cdecl*)(float, float))0x569660)(fX, fY);
	}

	sampapi::ID GetPlayerVehicleId() {
		auto game = sampapi::v037r3::RefNetGame();
		return game->GetVehiclePool()->Find(game->GetPlayerPool()->GetLocalPlayer()->m_pPed->GetVehicle());
	}

	sampapi::v037r3::CVehicle* GetPlayerVehicle() {
		auto game = sampapi::v037r3::RefNetGame();
		return game->GetVehiclePool()->Get(GetPlayerVehicleId());
	}

	bool IsPlayerInVehicle() {
		return GetPlayerVehicle() != nullptr;
	}

	bool IsPlayerDriver() {
		if (!IsPlayerInVehicle()) return false;
		return GetPlayerVehicle()->DriverIsPlayerPed();
	}

	float GetDistance(sampapi::CVector* firstPoint, sampapi::CVector* secondPoint) {
		return sqrtf(powf(secondPoint->x - firstPoint->x, 2) + powf(secondPoint->y - firstPoint->y, 2) + powf(secondPoint->z - firstPoint->z, 2));
	}

	float GetAngle(sampapi::CVector* firstPoint, sampapi::CVector* secondPoint) {
		return atan2f(secondPoint->y - firstPoint->y, -(secondPoint->x - firstPoint->x)) - M_PI / 2;
	}

}
#include "Coord.h"
#include "sampapi/CNetGame.h"
#include "game/GameUtil.h"
#include "handler/CommandHandler.h"

namespace Coord {

	bool enabled = false;
	sampapi::CVector endPoint;
	sampapi::CVector currentPoint;
	float speed[] = { 0.1f, 0.1f, -0.1f };
	float stepMultiplier = 5;
	DWORD delay = 25;
	DWORD timeSinceLastUpdate;
	DWORD forceDelay = 25;
	DWORD timeSinceLastForce;

	void OnUpdate() {

		if (!GameUtil::IsPlayerInVehicle())
			return CommandHandler::OnCommandCord("");

		if (GetTickCount() - timeSinceLastForce >= forceDelay) {
			forceDelay = GetTickCount();

			if (GameUtil::IsPlayerDriver())
				sampapi::v037r3::RefNetGame()->GetPlayerPool()->GetLocalPlayer()->SendIncarData();
			else {
				sampapi::v037r3::RefNetGame()->GetPlayerPool()->GetLocalPlayer()->SendPassengerData();
				sampapi::v037r3::RefNetGame()->GetPlayerPool()->GetLocalPlayer()->SendUnoccupiedData(GameUtil::GetPlayerVehicleId(), sampapi::v037r3::RefNetGame()->GetPlayerPool()->GetLocalPlayer()->m_passengerData.m_nSeatId);
			}

		}

		if (GetTickCount() - timeSinceLastUpdate >= delay) {
			timeSinceLastUpdate = GetTickCount();

			if (GameUtil::GetDistance(&currentPoint, &endPoint) <= stepMultiplier * 1.5)
				return CommandHandler::OnCommandCord("");

			float angle = GameUtil::GetAngle(&currentPoint, &endPoint);

			currentPoint.x += sinf(angle) * stepMultiplier;
			currentPoint.y += cosf(angle) * stepMultiplier;
			if (currentPoint.z < endPoint.z) currentPoint.z += stepMultiplier; else currentPoint.z -= stepMultiplier;

		}

	}
}
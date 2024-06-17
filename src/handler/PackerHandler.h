#pragma once

#include "RakHook/rakhook.hpp"

namespace PacketHandler {

	bool Init();
	inline bool OnOutcomingPacket(RakNet::BitStream* bs, PacketPriority& priority, PacketReliability& reliability, char& orderingChanel);
}
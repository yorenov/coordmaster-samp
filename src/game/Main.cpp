#include "handler/CommandHandler.h"
#include "handler/PackerHandler.h"
#include "coord/Coord.h"

namespace Main {

	bool init = false;

	void OnUpdate() {
		if (!init && ((*reinterpret_cast<unsigned char*>(0xC8D4C0) == 9))) {

			if (!CommandHandler::Init()) return;
			if (!PacketHandler::Init()) return;
			init = true;

		}
		if (init) {
			if (Coord::enabled)
				Coord::OnUpdate();
		}
	}

}
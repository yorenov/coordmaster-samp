#pragma once

#include "dllmain.h"

namespace CommandHandler {
	bool Init();
	void OnCommandCord(const char* args);
	void SendClientMessage(std::string message);
}
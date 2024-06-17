#include "MinHook.h"
#include "PreRenderHook.h"
#include "game/Main.h"

namespace PreRenderHook {

	typedef void(__cdecl* tPreRender)();
	tPreRender origPreRender = nullptr;

	void Init() {
		MH_Initialize();
		MH_CreateHook((void*)0x553910, &OnPreRender, (void**)&origPreRender);
		MH_EnableHook((void*)0x553910);
	}

	void OnPreRender() {
		Main::OnUpdate();
		return origPreRender();
	}

}
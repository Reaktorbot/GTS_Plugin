#include "papyrus/events.hpp"
#include "managers/modevent.hpp"


using namespace SKSE;
using namespace Gts;
using namespace RE;
using namespace RE::BSScript;

namespace {
	constexpr std::string_view papyrus_class = "GtsEvent";

	void RegisterOnFootstep(StaticFunctionTag* /*unused*/, TESForm* form) {
		if (!form) {
			return;
		}
		auto event_manager = ModEventManager::GetSingleton();
		event_manager.m_onfootstep.Register(form);
	}
	void UnRegisterOnFootstep(StaticFunctionTag* /*unused*/, TESForm* form) {
		if (!form) {
			return;
		}
		auto event_manager = ModEventManager::GetSingleton();
		event_manager.m_onfootstep.Unregister(form);
	}
}

namespace Gts {
	bool RegisterPapyrusEvents(IVirtualMachine* vm) {
		vm->RegisterFunction("RegisterOnFootstep", PapyrusClass, RegisterOnFootstep);
		vm->RegisterFunction("UnRegisterOnFootstep", PapyrusClass, UnRegisterOnFootstep);

		return true;
	}
}

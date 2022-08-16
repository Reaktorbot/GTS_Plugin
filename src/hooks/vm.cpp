#include "hooks/vm.hpp"
#include "managers/GtsManager.hpp"

using namespace RE;
using namespace RE::BSScript;
using namespace RE::BSScript::Internal;
using namespace Gts;

namespace Hooks
{
	// BGSImpactManager
	void Hook_VM::Hook() {
		logger::info("Hooking VirtualMachine");
		REL::Relocation<std::uintptr_t> vtbl{ VTABLE_BSScript__Internal__VirtualMachine[0] };
		_SendEvent = Vtbl.write_vfunc(REL::Relocate(0x24, 0x24, 0x26), SendEvent);
	}

	static void Hook_VM::SendEvent(VirtualMachine* a_this, VMHandle a_handle, const BSFixedString& a_event_name, IFunctionArguments* a_args) {
		_SendEvent(a_this, a_handle, a_eventName, a_args);
		std::string event_name = a_event_name.c_str();
		if (event_name == "OnUpdate") {
			GtsManager::GetSingleton().on_update();
		}
	}
}

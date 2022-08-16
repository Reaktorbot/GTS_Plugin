#include "papyrus/height.hpp"
#include "scale/height.hpp"
#include "util.hpp"


using namespace SKSE;
using namespace Gts;
using namespace RE;
using namespace RE::BSScript;

namespace {
	constexpr std::string_view papyrus_class = "GtsHeight";

	// Target Scales
	void SetTargetHeight(StaticFunctionTag* /*unused*/, Actor* actor, float height) {
		set_target_height(actor, height);
	}

	float GetTargetHeight(StaticFunctionTag* /*unused*/, Actor* actor) {
		return get_target_height(actor);
	}

	void ModTargetHeight(StaticFunctionTag* /*unused*/, Actor* actor, float amt) {
		mod_target_height(actor, amt);
	}

	void SetMaxHeight(StaticFunctionTag* /*unused*/, Actor* actor, float height) {
		set_max_height(actor, height);
	}

	float GetMaxHeight(StaticFunctionTag* /*unused*/, Actor* actor) {
		return get_max_height(actor);
	}

	void ModMaxHeight(StaticFunctionTag* /*unused*/, Actor* actor, float amt) {
		mod_max_height(actor, amt);
	}

	float GetVisualHeight(StaticFunctionTag* /*unused*/, Actor* actor) {
		return get_visual_height(actor);
	}

	void ModTeammateHeight(StaticFunctionTag* /*unused*/, float amt) {
		for (auto actor: find_actors()) {
			if (!actor) {
				continue;
			}
			if (!actor->Is3DLoaded()) {
				continue;
			}
			if (actor->IsPlayerTeammate()) {
				mod_target_height(actor, amt);
			}
		}
	}
}

namespace Gts {
	bool RegisterPapyrusHeight(IVirtualMachine* vm) {
		vm->RegisterFunction("SetTargetHeight", PapyrusClass, SetTargetHeight);
		vm->RegisterFunction("GetTargetHeight", PapyrusClass, GetTargetHeight);
		vm->RegisterFunction("ModTargetHeight", PapyrusClass, ModTargetHeight);

		vm->RegisterFunction("SetMaxHeight", PapyrusClass, SetMaxHeight);
		vm->RegisterFunction("GetMaxHeight", PapyrusClass, GetMaxHeight);
		vm->RegisterFunction("ModMaxHeight", PapyrusClass, ModMaxHeight);

		vm->RegisterFunction("GetVisualHeight", PapyrusClass, GetVisualHeight);

		vm->RegisterFunction("ModTeammateHeight", PapyrusClass, ModTeammateHeight);

		return true;
	}
}

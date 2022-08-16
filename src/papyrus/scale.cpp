#include "papyrus/scale.hpp"
#include "scale/scale.hpp"
#include "scale/modscale.hpp"
#include "data/persistent.hpp"
#include "managers/GtsManager.hpp"


using namespace SKSE;
using namespace Gts;
using namespace RE;
using namespace RE::BSScript;

namespace {
	constexpr std::string_view papyrus_class = "GtsScale";

	// Model Scale
	bool SetModelScale(StaticFunctionTag* /*unused*/, Actor* actor, float scale) {
		bool result = false;
		auto actor_data = Persistent::GetSingleton().GetData(actor);
		if (actor_data) {
			result = set_model_scale(actor, scale);
			actor_data->visual_scale = scale;
			actor_data->visual_scale_v = 0.0;
			actor_data->target_scale = scale;
		}
		return result;
	}
	float GetModelScale(StaticFunctionTag* /*unused*/, Actor* actor) {
		if (actor == nullptr) {
			return 0.0;
		}
		auto result = get_model_scale(actor);
		return result;
	}
	bool ModModelScale(StaticFunctionTag* /*unused*/, Actor* actor, float amt) {
		bool result = false;
		auto actor_data = Persistent::GetSingleton().GetData(actor);
		if (actor_data) {
			auto scale = get_model_scale(actor) + amt;
			result = set_model_scale(actor, scale);
			actor_data->visual_scale = scale;
			actor_data->visual_scale_v = 0.0;
			actor_data->target_scale = scale;
		}
		return result;
	}

	// Node Scale
	bool SetNodeScale(StaticFunctionTag* /*unused*/, Actor* actor, float scale) {
		bool result = false;
		auto actor_data = Persistent::GetSingleton().GetData(actor);
		if (actor_data) {
			result = set_npcnode_scale(actor, scale);
			actor_data->visual_scale = scale;
			actor_data->visual_scale_v = 0.0;
			actor_data->target_scale = scale;
		}
		return result;
	}
	float GetNodeScale(StaticFunctionTag* /*unused*/, Actor* actor) {
		if (actor == nullptr) {
			return 0.0;
		}
		auto result = get_npcnode_scale(actor);
		return result;
	}
	bool ModNodeScale(StaticFunctionTag* /*unused*/, Actor* actor, float amt) {
		bool result = false;
		auto actor_data = Persistent::GetSingleton().GetData(actor);
		if (actor_data) {
			auto scale = get_npcnode_scale(actor) + amt;
			result = set_npcnode_scale(actor, scale);
			actor_data->visual_scale = scale;
			actor_data->visual_scale_v = 0.0;
			actor_data->target_scale = scale;
		}
		return result;
	}

	// Ref scale
	bool SetRefScale(StaticFunctionTag* /*unused*/, Actor* actor, float scale) {
		bool result = false;
		auto actor_data = Persistent::GetSingleton().GetData(actor);
		if (actor_data) {
			set_ref_scale(actor, scale);
			result = true; // Ref scale cannot fail
			actor_data->visual_scale = scale;
			actor_data->visual_scale_v = 0.0;
			actor_data->target_scale = scale;
		}
		return result;
	}
	float GetRefScale(StaticFunctionTag* /*unused*/, Actor* actor) {
		if (actor == nullptr) {
			return 0.0;
		}
		auto result = get_ref_scale(actor);
		return result;
	}
	bool ModRefScale(StaticFunctionTag* /*unused*/, Actor* actor, float amt) {
		bool result = false;
		auto actor_data = Persistent::GetSingleton().GetData(actor);
		if (actor_data) {
			auto scale = get_ref_scale(actor) + amt;
			set_ref_scale(actor, scale);
			result = true;
			actor_data->visual_scale = scale;
			actor_data->visual_scale_v = 0.0;
			actor_data->target_scale = scale;
		}
		return result;
	}

	// Configurable scale
	void SetScaleMethod(StaticFunctionTag* /*unused*/, int size_method) {
		switch (size_method) {
			case 0:
				Persistent::GetSingleton().size_method = SizeMethod::ModelScale;
				break;
			case 1:
				Persistent::GetSingleton().size_method = SizeMethod::RootScale;
				break;
			case 2:
				Persistent::GetSingleton().size_method = SizeMethod::RefScale;
				break;
		}
	}
	int GetScaleMethod(StaticFunctionTag* /*unused*/) {
		switch (Persistent::GetSingleton().size_method) {
			case SizeMethod::ModelScale:
				return 0;
				break;
			case SizeMethod::RootScale:
				return 1;
				break;
			case SizeMethod::RefScale:
				return 2;
				break;
		}
		log::error("Scale method is invalid");
		return Persistent::GetSingleton().size_method;
	}
	bool SetScale(StaticFunctionTag* /*unused*/, Actor* actor, float scale) {
		bool result = false;
		auto actor_data = Persistent::GetSingleton().GetData(actor);
		if (actor_data) {
			result = set_scale(actor, scale);
			actor_data->visual_scale = scale;
			actor_data->visual_scale_v = 0.0;
			actor_data->target_scale = scale;
		}
		return result;
	}
	float GetScale(StaticFunctionTag* /*unused*/, Actor* actor) {
		if (actor == nullptr) {
			return 0.0;
		}
		auto result = get_scale(actor);
		return result;
	}
	bool ModScale(StaticFunctionTag* /*unused*/, Actor* actor, float amt) {
		bool result = false;
		auto actor_data = Persistent::GetSingleton().GetData(actor);
		if (actor_data) {
			auto scale = get_scale(actor) + amt;
			result = set_scale(actor, scale);
			actor_data->visual_scale = scale;
			actor_data->visual_scale_v = 0.0;
			actor_data->target_scale = scale;
		}
		return result;
	}

	// Target Scales
	void SetTargetScale(StaticFunctionTag* /*unused*/, Actor* actor, float scale) {
		set_target_scale(actor, scale);
	}

	float GetTargetScale(StaticFunctionTag* /*unused*/, Actor* actor) {
		return get_target_scale(actor);
	}

	void ModTargetScale(StaticFunctionTag* /*unused*/, Actor* actor, float amt) {
		mod_target_scale(actor, amt);
	}

	void SetMaxScale(StaticFunctionTag* /*unused*/, Actor* actor, float scale) {
		set_max_scale(actor, scale);
	}

	float GetMaxScale(StaticFunctionTag* /*unused*/, Actor* actor) {
		return get_max_scale(actor);
	}

	void ModMaxScale(StaticFunctionTag* /*unused*/, Actor* actor, float amt) {
		mod_max_scale(actor, amt);
	}

	float GetVisualScale(StaticFunctionTag* /*unused*/, Actor* actor) {
		return get_visual_scale(actor);
	}

	void ModTeammateScale(StaticFunctionTag* /*unused*/, float amt) {
		for (auto actor: find_actors()) {
			if (!actor) {
				continue;
			}
			if (!actor->Is3DLoaded()) {
				continue;
			}
			if (actor->IsPlayerTeammate()) {
				mod_target_scale(actor, amt);
			}
		}
	}
}

namespace Gts {
	bool RegisterPapyrusScale(IVirtualMachine* vm) {
		vm->RegisterFunction("SetModelScale", papyrus_class, SetModelScale);
		vm->RegisterFunction("GetModelScale", papyrus_class, GetModelScale);
		vm->RegisterFunction("ModModelScale", papyrus_class, ModModelScale);

		vm->RegisterFunction("SetNodeScale", papyrus_class, SetNodeScale);
		vm->RegisterFunction("GetNodeScale", papyrus_class, GetNodeScale);
		vm->RegisterFunction("ModNodeScale", papyrus_class, ModNodeScale);

		vm->RegisterFunction("SetRefScale", papyrus_class, SetRefScale);
		vm->RegisterFunction("GetRefScale", papyrus_class, GetRefScale);
		vm->RegisterFunction("ModRefScale", papyrus_class, ModRefScale);

		vm->RegisterFunction("SetScaleMethod", papyrus_class, SetScaleMethod);
		vm->RegisterFunction("GetScaleMethod", papyrus_class, GetScaleMethod);
		vm->RegisterFunction("SetScale", papyrus_class, SetScale);
		vm->RegisterFunction("GetScale", papyrus_class, GetScale);
		vm->RegisterFunction("ModScale", papyrus_class, ModScale);

		vm->RegisterFunction("SetTargetScale", papyrus_class, SetTargetScale);
		vm->RegisterFunction("GetTargetScale", papyrus_class, GetTargetScale);
		vm->RegisterFunction("ModTargetScale", papyrus_class, ModTargetScale);

		vm->RegisterFunction("SetMaxScale", papyrus_class, SetMaxScale);
		vm->RegisterFunction("GetMaxScale", papyrus_class, GetMaxScale);
		vm->RegisterFunction("ModMaxScale", papyrus_class, ModMaxScale);

		vm->RegisterFunction("GetVisualScale", papyrus_class, GetVisualScale);

		vm->RegisterFunction("ModTeammateScale", papyrus_class, ModTeammateScale);

		return true;
	}
}

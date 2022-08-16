#include "papyrus/plugin.hpp"
#include "data/persistent.hpp"
#include "managers/GtsManager.hpp"
#include "util.hpp"
#include <math.h>
#include <sstream>
#include <iomanip>


using namespace SKSE;
using namespace Gts;
using namespace RE;
using namespace RE::BSScript;

namespace {
	constexpr std::string_view papyrus_class = "GtsPlugin";
	float GetDistanceToCamera(StaticFunctionTag* /*unused*/, Actor* actor) {
		return get_distance_to_camera(actor);
	}

	bool SetGrowthHalfLife(StaticFunctionTag* /*unused*/, Actor* actor, float halflife) {
		if (actor != nullptr) {
			auto actor_data = Persistent::GetSingleton().GetData(actor);
			if (actor_data) {
				actor_data->half_life = halflife;
				return true;
			}
		}
		return false;
	}

	float GetGrowthHalfLife(StaticFunctionTag* /*unused*/, Actor* actor) {
		if (actor != nullptr) {
			auto actor_data = Persistent::GetSingleton().GetData(actor);
			if (actor_data) {
				return actor_data->half_life;
			}
		}
		return 0.05;
	}

	bool SetAnimSpeed(StaticFunctionTag* /*unused*/, Actor* actor, float animspeed) {
		if (actor != nullptr) {
			auto actor_data = Persistent::GetSingleton().GetData(actor);
			if (actor_data) {
				actor_data->anim_speed = animspeed;
				return true;
			}
		}
		return false;
	}

	// From https://stackoverflow.com/questions/17211122/formatting-n-significant-digits-in-c-without-scientific-notation
	std::string Format(double f, int n)
	{
		if (f == 0) {
			return "0";
		}
		int d = (int)::ceil(::log10(f < 0 ? -f : f)); /*digits before decimal point*/
		double order = ::pow(10., n - d);
		std::stringstream ss;
		ss << std::fixed << std::setprecision(std::max(n - d, 0)) << round(f * order) / order;
		return ss.str();
	}

	std::string SigFig(StaticFunctionTag* /*unused*/, float number, int sf) {
		return Format(number, sf);
	}

	bool GetIsHighHeelEnabled(StaticFunctionTag* /*unused*/) {
		return Persistent::GetSingleton().highheel_correction;
	}

	void SetIsHighHeelEnabled(StaticFunctionTag* /*unused*/, bool enabled) {
		Persistent::GetSingleton().highheel_correction = enabled;
	}

	bool GetIsSpeedAdjusted(StaticFunctionTag* /*unused*/) {
		return Persistent::GetSingleton().is_speed_adjusted;
	}

	void SetIsSpeedAdjusted(StaticFunctionTag* /*unused*/, bool enabled) {
		Persistent::GetSingleton().is_speed_adjusted = enabled;
	}

	void SetSpeedParameterK(StaticFunctionTag* /*unused*/, float k) {
		Persistent::GetSingleton().speed_adjustment.k = k;
	}
	float GetSpeedParameterK(StaticFunctionTag* /*unused*/) {
		return Persistent::GetSingleton().speed_adjustment.k;
	}
	void SetSpeedParameterN(StaticFunctionTag* /*unused*/, float n) {
		Persistent::GetSingleton().speed_adjustment.n = n;
	}
	float GetSpeedParameterN(StaticFunctionTag* /*unused*/) {
		return Persistent::GetSingleton().speed_adjustment.n;
	}
	void SetSpeedParameterS(StaticFunctionTag* /*unused*/, float s) {
		Persistent::GetSingleton().speed_adjustment.s = s;
	}
	float GetSpeedParameterS(StaticFunctionTag* /*unused*/) {
		return Persistent::GetSingleton().speed_adjustment.s;
	}

	bool IsJumping(StaticFunctionTag* /*unused*/, Actor* actor) {
		return Gts::IsJumping(actor);
	}

	bool IsInAir(StaticFunctionTag* /*unused*/, Actor* actor) {
		if (actor == nullptr) { return false;
}
		return actor->IsInMidair();
	}

	float GetTremorScale(StaticFunctionTag* /*unused*/) {
		return Persistent::GetSingleton().tremor_scale;
	}

	void SetTremorScale(StaticFunctionTag* /*unused*/, float value) {
		Persistent::GetSingleton().tremor_scale = value;
	}

	float GetTremorScaleNPC(StaticFunctionTag* /*unused*/) {
		return Persistent::GetSingleton().npc_tremor_scale;
	}

	void SetTremorScaleNPC(StaticFunctionTag* /*unused*/, float value) {
		Persistent::GetSingleton().npc_tremor_scale = value;
	}

	float GetExperimentFloat(StaticFunctionTag* /*unused*/) {
		return GtsManager::GetSingleton().experiment;
	}

	void SetExperimentFloat(StaticFunctionTag* /*unused*/, float value) {
		GtsManager::GetSingleton().experiment = value;
	}
}

namespace Gts {
	bool RegisterPapyrusPlugin(IVirtualMachine* vm) {
		vm->RegisterFunction("GetDistanceToCamera", papyrus_class, GetDistanceToCamera);
		vm->RegisterFunction("SetGrowthHalfLife", papyrus_class, SetGrowthHalfLife);
		vm->RegisterFunction("GetGrowthHalfLife", papyrus_class, GetGrowthHalfLife);
		vm->RegisterFunction("SetAnimSpeed", papyrus_class, SetAnimSpeed);
		vm->RegisterFunction("SigFig", papyrus_class, SigFig);
		vm->RegisterFunction("GetIsHighHeelEnabled", papyrus_class, GetIsHighHeelEnabled);
		vm->RegisterFunction("SetIsHighHeelEnabled", papyrus_class, SetIsHighHeelEnabled);
		vm->RegisterFunction("GetIsSpeedAdjusted", papyrus_class, GetIsSpeedAdjusted);
		vm->RegisterFunction("SetIsSpeedAdjusted", papyrus_class, SetIsSpeedAdjusted);
		vm->RegisterFunction("SetSpeedParameterK", papyrus_class, SetSpeedParameterK);
		vm->RegisterFunction("GetSpeedParameterK", papyrus_class, GetSpeedParameterK);
		vm->RegisterFunction("SetSpeedParameterN", papyrus_class, SetSpeedParameterN);
		vm->RegisterFunction("GetSpeedParameterN", papyrus_class, GetSpeedParameterN);
		vm->RegisterFunction("SetSpeedParameterS", papyrus_class, SetSpeedParameterS);
		vm->RegisterFunction("GetSpeedParameterS", papyrus_class, GetSpeedParameterS);
		vm->RegisterFunction("IsJumping", PapyrusClass, IsJumping);
		vm->RegisterFunction("IsInAir", papyrus_class, IsInAir);
		vm->RegisterFunction("GetTremorScale", papyrus_class, GetTremorScale);
		vm->RegisterFunction("SetTremorScale", papyrus_class, SetTremorScale);
		vm->RegisterFunction("GetTremorScaleNPC", papyrus_class, GetTremorScaleNPC);
		vm->RegisterFunction("SetTremorScaleNPC", papyrus_class, SetTremorScaleNPC);
		vm->RegisterFunction("GetExperimentFloat", papyrus_class, GetExperimentFloat);
		vm->RegisterFunction("SetExperimentFloat", papyrus_class, SetExperimentFloat);

		return true;
	}
}

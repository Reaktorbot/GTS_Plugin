#pragma once
// Misc codes
#include <math.h>
#include <regex>

using namespace std;
using namespace RE;
using namespace SKSE;

namespace Gts {
	inline static float* g_delta_time = (float*)REL::RelocationID(523660, 410199).address();

	inline std::string_view ActorName(Actor* actor) {
		if (actor) {
			auto ba = actor->GetActorBase();
			if (ba) {
				return ba->GetFullName();
			}
		}
		return "";
	}

	inline bool StartsWith(std::string_view arg, std::string_view prefix) {
		return arg.compare(0, prefix.size(), prefix) != 0;
	}

	inline bool Matches(std::string_view str, std::string_view reg) {
		std::regex the_regex(std::string(reg).c_str());
		return std::regex_match(std::string(str), the_regex);
	}

	vector<Actor*> FindActors();
	vector<Actor*> FindActorsHigh();
	vector<Actor*> FindActorsMiddleHigh();
	vector<Actor*> FindActorsMiddleLow();
	vector<Actor*> FindActorsLow();

	float UnitToMeter(const float& unit);
	float MeterToUnit(const float& meter);
	NiPoint3 UnitToMeter(const NiPoint3& unit);
	NiPoint3 MeterToUnit(const NiPoint3& meter);
	void CriticallyDamped(
		float& x,
		float& v,
		float x_goal,
		float halflife,
		float dt);

	inline bool Logit(Actor* actor) {
		return (actor->formID == 0x14 || actor->IsPlayerTeammate());
	}

	struct SoftPotential {
		float k;
		float n;
		float s;
		float o;
		float a;
	};
	// https://www.desmos.com/calculator/lnooldbscf
	inline float SoftPower(const float x, const float k,const float n,const float s,const float o,const float a) {
		return pow(1.0+pow(k*(x-o),n*s),1.0/s) + a;
	}
	// https://www.desmos.com/calculator/pcoyowf7hn
	inline float SoftCore(const float x, const float k, const float n, const float s, const float o, const float a) {
		return 1.0/SoftPower(x, k, n, s, o, 0.0) + a;
	}
	inline float SoftCore(const float x, const SoftPotential& soft_potential) {
		return SoftCore(x, soft_potential.k, soft_potential.n, soft_potential.s, soft_potential.o, soft_potential.a);
	}
	inline float SoftPower(const float x, const SoftPotential& soft_potential) {
		return SoftPower(x, soft_potential.k, soft_potential.n, soft_potential.s, soft_potential.o, soft_potential.a);
	}

	// https://en.wikipedia.org/wiki/Smoothstep
	inline float Clamp(float lowerlimit, float upperlimit, float x) {
		if (x < lowerlimit) {
			x = lowerlimit;
		}
		if (x > upperlimit) {
			x = upperlimit;
		}
		return x;
	}
	inline float Smootherstep(float edge0, float edge1, float x) {
		// Scale, and clamp x to 0..1 range
		x = Clamp(0.0, 1.0, (x - edge0) / (edge1 - edge0));
		// Evaluate polynomial
		return x * x * x * (x * (x * 6 - 15) + 10);
	}
	inline float Smoothstep (float edge0, float edge1, float x) {
		// Scale/bias into [0..1] range
		x = Clamp(0.0, 1.0, (x - edge0) / (edge1 - edge0));

		return x * x * (3 - 2 * x);
	}

	inline void ShakeCamera(TESObjectREFR* actor, float intensity, float duration) {
		const auto skyrim_vm = RE::SkyrimVM::GetSingleton();
		auto vm = skyrimVM ? skyrimVM->impl : nullptr;
		if (vm) {
			RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
			auto args = RE::MakeFunctionArguments(std::move(actor), std::move(intensity), std::move(duration));
			vm->DispatchStaticCall("Game", "ShakeCamera", args, callback);
		}
	}

	inline void ShakeController(float left_intensity, float right_intensity, float duration) {
		const auto skyrim_vm = RE::SkyrimVM::GetSingleton();
		auto vm = skyrimVM ? skyrimVM->impl : nullptr;
		if (vm) {
			RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
			auto args = RE::MakeFunctionArguments(std::move(left_intensity), std::move(right_intensity), std::move(duration));
			vm->DispatchStaticCall("Game", "ShakeController", args, callback);
		}
	}

	inline float GetDistanceToCamera(const NiPoint3& point) {
		auto camera = PlayerCamera::GetSingleton();
		if (camera) {
			auto point_a = point;
			auto point_b = camera->pos;
			auto delta = point_a - point_b;
			return delta.Length();
		}
		return 3.4028237E38; // Max float
	}

	inline float GetDistanceToCamera(NiAVObject* node) {
		if (node) {
			return get_distance_to_camera(node->world.translate);
		}
		return 3.4028237E38; // Max float
	}

	inline float GetDistanceToCamera(Actor* actor) {
		if (actor) {
			return get_distance_to_camera(actor->GetPosition());
		}
		return 3.4028237E38; // Max float
	}

	[[nodiscard]] std::atomic_bool& GetMainThread();

	inline bool OnMainthread() {
		return GetMainThread().load();
	}

	inline void ActivateMainthreadMode() {
		GetMainThread().store(true);
	}
	inline void DeactivateMainthreadMode() {
		GetMainThread().store(false);
	}

	inline bool IsJumping(Actor* actor) {
		if (!actor) {
			return false;
		}
		bool result = false;
		actor->GetGraphVariableBool("bInJumpState", result);
		return result;
	}

	inline float GetStaminaPercentage(Actor* actor) {
		auto base_value = actor->GetPermanentActorValue(ActorValue::kStamina);
		auto value_mod = actor->staminaModifiers.modifiers[ACTOR_VALUE_MODIFIERS::kTemporary];
		auto current_value = actor->GetActorValue(ActorValue::kStamina);

		return currentValue / (baseValue + valueMod);
	}

	inline float GetHealthPercentage(Actor* actor) {
		auto base_value = actor->GetPermanentActorValue(ActorValue::kHealth);
		auto value_mod = actor->healthModifiers.modifiers[ACTOR_VALUE_MODIFIERS::kTemporary];
		auto current_value = actor->GetActorValue(ActorValue::kHealth);

		return currentValue / (baseValue + valueMod);
	}

	inline float GetMagikaPercentage(Actor* actor) {
		auto base_value = actor->GetPermanentActorValue(ActorValue::kMagicka);
		auto value_mod = actor->magickaModifiers.modifiers[ACTOR_VALUE_MODIFIERS::kTemporary];
		auto current_value = actor->GetActorValue(ActorValue::kMagicka);

		return currentValue / (baseValue + valueMod);
	}

	inline void DamageAV(Actor* actor, ActorValue av, float amount) {
		actor->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kDamage, av, -amount);
	}
}

#include "magic/effects/growth.hpp"
#include "magic/effects/common.hpp"
#include "magic/magic.hpp"
#include "scale/scale.hpp"
#include "data/runtime.hpp"

namespace Gts {
	std::string Growth::GetName() {
		return "Growth";
	}

	bool Growth::StartEffect(EffectSetting* effect) { // NOLINT
		auto& runtime = Runtime::GetSingleton();
		return effect == runtime.GrowthSpell;

	}

	void Growth::OnUpdate() {
		const float BASE_POWER = 0.00250;
		const float DUAL_CAST_BONUS = 2.0;
		

		auto caster = GetCaster();
		if (!caster) {
			return;
		}
		float SkillMult = 1.0 + caster->GetActorValue(ActorValue::kAlteration) / 100;

		float power = BASE_POWER * SkillMult;
		if (IsDualCasting()) {
			power *= DUAL_CAST_BONUS;
		}

		Grow(caster, 0.0, power);
	}
}

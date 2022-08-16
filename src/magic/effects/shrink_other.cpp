#include "magic/effects/shrink_other.hpp"
#include "magic/effects/common.hpp"
#include "magic/magic.hpp"
#include "scale/scale.hpp"
#include "data/runtime.hpp"

namespace Gts {
	static bool ShrinkOther::StartEffect(EffectSetting* effect) {
		auto& runtime = Runtime::GetSingleton();
		return effect == runtime.ShrinkAlly;
	}

	void ShrinkOther::OnUpdate() {
		auto caster = GetCaster();
		if (!caster) {
			return;
		}
		auto target = GetTarget();
		if (!target) {
			return;
		}

		auto& runtime = Runtime::GetSingleton();
		float progression_multiplier = runtime.ProgressionMultiplier->value;
		float crush_growth_rate = runtime.CrushGrowthRate->value;
		float caster_scale = get_visual_scale(caster);
		float target_scale = get_visual_scale(target);
		float grow_rate = 0.0;
		float dual_cast = 1.0;
		if (IsDualCasting()) {
			dual_cast = 2.0;
		}
		if (crush_growth_rate >= 1.4) {
			grow_rate = 0.00090;
		}

		if (target_scale > 0.25) {
			mod_target_scale(target, -(0.00180 + GrowRate) * (casterScale * 0.50 + 0.50) * targetScale * ProgressionMultiplier * DualCast);
		}
	}
}

#include "magic/effects/grow_other.hpp"
#include "magic/effects/common.hpp"
#include "magic/magic.hpp"
#include "scale/scale.hpp"
#include "data/runtime.hpp"

namespace Gts {
	static bool GrowOther::StartEffect(EffectSetting* effect) {
		auto& runtime = Runtime::GetSingleton();
		return effect == runtime.GrowAlly;
	}

	void GrowOther::OnUpdate() {
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
		float smt_rate = 1.0;
		float dual_cast = 1.0;
		if (caster->magicCasters[Actor::SlotTypes::kLeftHand]->GetIsDualCasting()) {
			dual_cast = 2.0;
		}
		if (caster->HasMagicEffect(runtime.smallMassiveThreat)) {
			smt_rate = 2.0;
		}
		if (crush_growth_rate >= 1.4) {
			grow_rate = 0.00180;
		}

		float transer_amount = (0.00180 + grow_rate) * (caster_scale * 0.50 + 0.50) * target_scale * progression_multiplier * smt_rate * dual_cast;
		mod_target_scale(target, transer_amount);

		if (caster_scale >= 1.0) {
			mod_target_scale(caster, -transer_amount);
		}
	}
}

#include "magic/effects/shrink_back.hpp"
#include "magic/effects/common.hpp"
#include "magic/magic.hpp"
#include "scale/scale.hpp"
#include "data/runtime.hpp"

namespace Gts {
	static bool ShrinkBack::StartEffect(EffectSetting* effect) {
		auto& runtime = Runtime::GetSingleton();
		return effect == runtime.ShrinkBack;
	}

	void ShrinkBack::OnUpdate() {
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
		float caster_scale = get_visual_scale(caster);
		float transfer_amount = caster_scale * 0.0025 + (0.0001 * 10 * progression_multiplier);
		float natural_scale = 1.0;
		if (fabs(caster_scale - natural_scale) <= transfer_amount) {
			set_target_scale(caster, natural_scale);
			Dispel();
		} else if (caster_scale < natural_scale) {
			mod_target_scale(caster, transfer_amount);
		} else { // if (casterScale > natural_scale) {
			mod_target_scale(caster, -transfer_amount);
		}
	}
}

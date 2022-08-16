#include "magic/effects/shrink_other_button.hpp"
#include "magic/effects/common.hpp"
#include "magic/magic.hpp"
#include "scale/scale.hpp"
#include "data/runtime.hpp"
#include "util.hpp"

namespace Gts {
	static bool ShrinkOtherButton::StartEffect(EffectSetting* effect) {
		auto& runtime = Runtime::GetSingleton();
		return effect == runtime.ShrinkAllySizeButton;
	}

	void ShrinkOtherButton::OnUpdate() {
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
		float target_scale = get_visual_scale(target);
		float magicka_max_check = GetMagikaPercentage(caster);
		if (magicka_max_check <= 0.05)
		{magicka_max_check = 0.05;}
		if (target_scale > 1.0) {
			DamageAV(caster, ActorValue::kMagicka, 0.25 * (targetScale * 0.25 + 0.75) * MagickaMaxCheck);
			mod_target_scale(target, -(0.0025 * targetScale * ProgressionMultiplier));
		}
	}
}

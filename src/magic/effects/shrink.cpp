#include "magic/effects/shrink.hpp"
#include "magic/effects/common.hpp"
#include "magic/magic.hpp"
#include "scale/scale.hpp"
#include "data/runtime.hpp"

namespace Gts {
	static bool Shrink::StartEffect(EffectSetting* effect) {
		auto& runtime = Runtime::GetSingleton();
		return effect == runtime.ShrinkSpell;
	}

	void Shrink::OnUpdate() {
		auto caster = GetCaster();
		if (!caster) {
			return;
		}
		auto target = GetTarget();
		if (!target) {
			return;
		}

		auto& runtime = Runtime::GetSingleton();
		float size_limit = runtime.sizeLimit->value;
		float progression_multiplier = runtime.ProgressionMultiplier->value;
		float caster_scale = get_visual_scale(caster);
		float dual_cast = 1.0;
		if (IsDualCasting()) {
			dual_cast = 2.0;
		}
		if (caster_scale < size_limit) {
			mod_target_scale(caster, -0.0018* ProgressionMultiplier * DualCast);
		}
	}
}

#include "magic/effects/shrink_button.hpp"
#include "magic/effects/common.hpp"
#include "magic/magic.hpp"
#include "scale/scale.hpp"
#include "data/runtime.hpp"
#include "util.hpp"

namespace Gts {
	static bool ShrinkButton::StartEffect(EffectSetting* effect) {
		auto& runtime = Runtime::GetSingleton();
		return effect == runtime.ShrinkPCButton;
	}

	void ShrinkButton::OnUpdate() {
		auto caster = GetCaster();
		if (!caster) {
			return;
		}
		auto target = GetTarget();
		if (!target) {
			return;
		}

		auto& runtime = Runtime::GetSingleton();

		float caster_scale = get_visual_scale(caster);
		float stamina_max_check = GetStaminaPercentage(caster);
		if (caster_scale > 0.25) {
			DamageAV(caster, ActorValue::kStamina, 0.25 * (casterScale * 0.5 + 0.5) * StaminaMaxCheck);
			if (stamina_max_check <= 0.05) {
				stamina_max_check = 0.05;
			}
			mod_target_scale(caster, -0.0025 * casterScale * StaminaMaxCheck);
		}
	}
}

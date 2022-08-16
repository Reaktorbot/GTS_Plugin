#include "magic/effects/SizeRelatedDamage.hpp"
#include "magic/effects/common.hpp"
#include "magic/magic.hpp"
#include "scale/scale.hpp"
#include "data/runtime.hpp"

namespace Gts {

	static bool SizeDamage::StartEffect(EffectSetting* effect) {
		auto& runtime = Runtime::GetSingleton();
		return (effect == runtime.SizeRelatedDamage0 || effect == runtime.SizeRelatedDamage1 || effect == runtime.SizeRelatedDamage2);
	}

	void SizeDamage::OnUpdate() {
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
		float target_scale = get_visual_scale(target);

		float size_difference = caster_scale/target_scale;
		if (target->IsPlayerTeammate() == true && runtime.GtsNPCEffectImmunityToggle->value == 1.0
		    || target->HasMagicEffect(runtime.FakeCrushEffect) == true
		    || target->Is3DLoaded() == false) {
			return;
		} // Do not apply if those are true

		if (SizeDifference >= 24.0 && !target->IsPlayerTeammate()) {
			caster->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(runtime.FakeCrushSpell, false, target, 1.00f, false, 0.0f, caster);
		}
		// ^ Crush anyway, no conditions needed since size difference is too massive
		else if (SizeDifference >= 4.0 && target->IsDead() && !target->IsPlayerTeammate()) {
			// ^ We don't want to crush allies
			caster->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(runtime.FakeCrushSpell, false, target, 1.00f, false, 0.0f, caster);
		}
		// ^ Crush only if size difference is > than 4.0

	}
}

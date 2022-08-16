#include "magic/effects/absorb_effect.hpp"
#include "magic/effects/common.hpp"
#include "magic/magic.hpp"
#include "scale/scale.hpp"
#include "data/runtime.hpp"

namespace Gts {
	Absorb::Absorb(ActiveEffect* effect) : Magic(effect) {
		auto base_spell = GetBaseEffect();
		auto& runtime = Runtime::GetSingleton();

		this->true_absorb = base_spell == runtime.TrueAbsorb;
	}

	static bool Absorb::StartEffect(EffectSetting* effect) {
		auto& runtime = Runtime::GetSingleton();
		return (effect == runtime.AbsorbMGEF || effect == runtime.TrueAbsorb);
	}

	void Absorb::OnUpdate() {
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
		float target_scale = get_visual_scale(target);
		float size_difference = caster_scale/target_scale;
		if (caster->HasMagicEffect(runtime.smallMassiveThreat)) {
			size_difference *= 4.0;
			} // Insta-absorb if SMT is active
		if (SizeDifference >= 4.0 && target->HasMagicEffect(runtime.TrueAbsorb) == false)
		{caster->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(runtime.TrueAbsorbSpell, false, target, 1.00f, false, 0.0f, caster);}
		// ^ Cast true absorb
		if (this->true_absorb) {
			mod_target_scale(target, -0.00825 * ProgressionMultiplier * SizeDifference);
			mod_target_scale(caster,  0.00250 * ProgressionMultiplier * targetScale);
			if (targetScale <= 0.25 && target->HasMagicEffect(runtime.ShrinkToNothing) == false) {
				caster->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(runtime.ShrinkToNothingSpell, false, target, 1.00f, false, 0.0f, caster);
			}
			// ^ Emulate absorption
		} else {
			mod_target_scale(target, -0.0025 * ProgressionMultiplier * SizeDifference);
			mod_target_scale(caster,  0.0005 * ProgressionMultiplier * targetScale);
		}

	}
}

#pragma once
#include "util.hpp"
#include "scale/scale.hpp"
#include "data/runtime.hpp"
// Module that handles footsteps


namespace Gts {
	inline float CalcEffeciency(Actor* caster, Actor* target) {
		auto& runtime = Runtime::GetSingleton();
		float progression_multiplier = runtime.ProgressionMultiplier->value;
		float efficiency = clamp(0.25, 1.25, (caster->GetLevel()/target->GetLevel())) * ProgressionMultiplier;

		if (std::string(target->GetDisplayFullName()).find("ragon") != std::string::npos) {
			efficiency *= 0.14;
		}

		return efficiency;
	}

	inline void TransferSize(Actor* caster, Actor* target, bool dual_casting, float power, float transfer_effeciency, bool small_massive_threat) {
		transfer_effeciency = clamp(0.0, 1.0, transfer_effeciency); // Ensure we cannot grow more than they shrink
		auto& runtime = Runtime::GetSingleton();

		float target_scale = get_visual_scale(target);
		float caster_scale = get_visual_scale(caster);

		float additional_shrink_value = 1.0;
		float smt_rate = 1.0;
		float efficiency = calc_effeciency(caster, target);

		float dual_cast = 1.0;
		if (dual_casting) {
			dual_cast = 2.0;
		}

		if (small_massive_threat) {
			smt_rate = 2.0;
		}

		if (caster->HasPerk(runtime.PerkPart1)) {
			additional_shrink_value = 1.33;
		} else if (caster->HasPerk(runtime.PerkPart2)) {
			additional_shrink_value = 2.0;
		}
		if (Runtime::GetSingleton().ProtectEssentials->value == 1.0 && target->IsEssential() == true) {
			return;
		}
		float alteration_level = (caster->GetActorValue(ActorValue::kAlteration) * 0.00166 / 50) * AdditionalShrinkValue * DualCast;
		//log::info("Caster is {}", caster->GetDisplayFullName());
		//log::info("Target is {}", target->GetDisplayFullName());
		float stolen_amount = (target_scale * 0.0005 + alteration_level * smt_rate * efficiency) * power;
		mod_target_scale(target, -stolen_amount);
		float growth_amount = stolen_amount/3 * transfer_effeciency;
		mod_target_scale(caster, growth_amount);

		if (TargetScale <= 0.10 && target->HasMagicEffect(runtime.ShrinkToNothing) == false && target->IsPlayerTeammate() == false)
		{caster->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(runtime.ShrinkToNothingSpell, false, target, 1.00f, false, 0.0f, caster);
		}
	}
}

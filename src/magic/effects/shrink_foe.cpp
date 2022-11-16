#include "magic/effects/shrink_foe.hpp"
#include "magic/effects/common.hpp"
#include "magic/magic.hpp"
#include "scale/scale.hpp"
#include "data/runtime.hpp"
#include "data/persistent.hpp"

namespace Gts {
	std::string ShrinkFoe::GetName() {
		return "ShrinkFoe";
	}

	ShrinkFoe::ShrinkFoe(ActiveEffect* effect) : Magic(effect) {
		const float SHRINK_POWER = 1.15;
		const float SHRINK_EFFIC = 0.38;
		const float SHRINK_AOE_POWER = 1.40;
		const float SHRINK_AOE_EFFIC = 0.42;
		const float SHRINK_AOE_MASTER_POWER = 1.75;
		const float SHRINK_AOE_MASTER_EFFIC = 0.46;
		const float SHRINK_BOLT_POWER = 28.40;
		const float SHRINK_BOLT_EFFIC = 0.18;
		const float SHRINK_STORM_POWER = 50.80;
		const float SHRINK_STORM_EFFIC = 0.20;

		auto base_spell = GetBaseEffect();
		auto& runtime = Runtime::GetSingleton();

		if (base_spell == runtime.ShrinkEnemy) {
			this->power = SHRINK_POWER;
			this->efficiency = SHRINK_EFFIC;
		} else if (base_spell == runtime.ShrinkEnemyAOE) {
			this->power = SHRINK_AOE_POWER;
			this->efficiency = SHRINK_AOE_EFFIC;
		} else if (base_spell == runtime.ShrinkEnemyAOEMast) {
			// ShrinkEnemyAOEMast
			this->power = SHRINK_AOE_MASTER_POWER;
			this->efficiency = SHRINK_AOE_MASTER_EFFIC;
		}
		else if (base_spell == runtime.ShrinkBolt) {
			// ShrinkBolt
			this->power = SHRINK_BOLT_POWER;
			this->efficiency = SHRINK_BOLT_EFFIC;
		}
		else if (base_spell == runtime.ShrinkStorm) {
			// ShrinkBolt
			this->power = SHRINK_STORM_POWER;
			this->efficiency = SHRINK_STORM_EFFIC;
		}
	}

	bool ShrinkFoe::StartEffect(EffectSetting* effect) { // NOLINT
		auto& runtime = Runtime::GetSingleton();
		return (effect == runtime.ShrinkEnemy || effect == runtime.ShrinkEnemyAOE || effect == runtime.ShrinkEnemyAOEMast || effect == runtime.ShrinkBolt || effect == runtime.ShrinkStorm);
	}

	void ShrinkFoe::OnUpdate() {
		auto caster = GetCaster();
		

		if (!caster) {
			return;
		}
		auto target = GetTarget();
		if (!target) {
			return;
		}
		float SizeDifference = 1.0;

		if (this->power >= 18.00)
		{	auto& Persist = Persistent::GetSingleton();
			auto actor_data = Persist.GetData(target);
			actor_data->half_life = 0.25; // Faster shrink, less smooth.
			SizeDifference = clamp(1.0, 8.0, (get_target_scale(caster)/get_target_scale(target))/2);
		}
		
		float TotalPower = this->power * 10.0;
		float TotalEfficiency = this->efficiency * 1.0;
		
		bool has_smt = caster->HasMagicEffect(Runtime::GetSingleton().SmallMassiveThreat);
		TransferSize(caster, target, IsDualCasting(), TotalPower * SizeDifference, TotalEfficiency, has_smt);
		if (ShrinkToNothing(caster, target)) {
			Dispel();
		}
	}

	void ShrinkFoe::OnFinish() {
		auto Caster = GetCaster();
		auto Target = GetTarget();
		CastTrackSize(Caster, Target);
	}
}

#include "magic/effects/shrink_foe.hpp"
#include "magic/effects/common.hpp"
#include "magic/magic.hpp"
#include "scale/scale.hpp"
#include "data/runtime.hpp"

namespace Gts {
	ShrinkFoe::ShrinkFoe(ActiveEffect* effect) : Magic(effect) {
		auto base_spell = GetBaseEffect();
		auto& runtime = Runtime::GetSingleton();

		if (base_spell == runtime.ShrinkEnemy) {
			this->power = 0.90;
			this->efficiency = 0.34;
		} else if (base_spell == runtime.ShrinkEnemyAOE) {
			this->power = 1.10;
			this->efficiency = 0.36;
		} else if (base_spell == runtime.ShrinkEnemyAOEMast) {
			// ShrinkEnemyAOEMast
			this->power = 1.25;
			this->efficiency = 0.42;
		}
	}

	static bool ShrinkFoe::StartEffect(EffectSetting* effect) {
		auto& runtime = Runtime::GetSingleton();
		return effect == runtime.ShrinkEnemy || effect == runtime.ShrinkEnemyAOE || effect == runtime.ShrinkEnemyAOEMast;
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
		
		bool small_massive_threat = caster->HasMagicEffect(Runtime::GetSingleton().smallMassiveThreat);
		
		transfer_size(caster, target, IsDualCasting(), this->power, this->efficiency, smallMassiveThreat);
	}
}

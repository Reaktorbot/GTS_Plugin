#include "managers/camera.hpp"
#include "managers/Attributes.hpp"
#include "scale/scale.hpp"
#include "util.hpp"
#include "data/runtime.hpp"
#include "data/persistent.hpp"
#include "magic/effects/common.hpp"

using namespace SKSE;
using namespace RE;
using namespace REL;
using namespace Gts;

namespace Gts {
	AttributeManager& AttributeManager::GetSingleton() noexcept {
		static AttributeManager instance;
		return instance;
	}

void AttributeManager::Update() {
	// Reapply Player Only

		auto Player == PlayerCharacter::GetSingleton();
		auto& runtime = Runtime::GetSingleton();

		auto SmallMassiveThreat = runtime.SmallMassiveThreat;

		float AllowTimeChange = runtime.AllowTimeChange->value;
		float bonusHPMultiplier = runtime.bonusHPMultiplier->value;

		float bonusCarryWeightMultiplier = runtime.bonusCarryWeightMultiplier->value;
		float bonusJumpHeightMultiplier = runtime.bonusJumpHeightMultiplier->value;
		float bonusDamageMultiplier = runtime.bonusDamageMultiplier->value;
		float bonusSpeedMultiplier = runtime.bonusSpeedMultiplier->value;
		float bonusSpeedMax = runtime.bonusSpeedMax->value;

		auto ExplGrowthP1 = runtime.explosiveGrowth1;
    	auto ExplGrowthP2 = runtime.explosiveGrowth2;
    	auto ExplGrowthP3 = runtime.explosiveGrowth3;
		auto HealthRegenPerk = runtime.HealthRegenPerk;

		float size = get_visual_scale(Player);

		float HpRegen = Player->GetPermanentActorValue(ActorValue::kHealth) * 0.0005;
		float MaxHealth = Player->GetPermanentActorValue(ActorValue::kHealth);

		if (Player->HasPerk(HealthRegenPerk) && (Player->HasMagicEffect(ExplGrowthP1)||Player->HasMagicEffect(ExplGrowthP2)|| Player->HasMagicEffect(ExplGrowthP3)))
    		{Player->RestoreActorValue(ActorValue::kHealth, HpRegen * TimeScale());}

		float bonusHP = ((Player->GetBaseActorValue(ActorValue::kHealth) * size - Player->GetBaseActorValue(ActorValue::kHealth)) * bonusHPMultiplier);
        float HpCheck = Player->GetBaseActorValue(ActorValue::kHealth) + bonusHP;

		if (bonusHPMultiplier == 0.0)  {
			bonusHP = 0;
			}

		if (size < 1)    
    	{{bonusHP = ((Player->GetBaseActorValue(ActorValue::kHealth) * size - Player->GetBaseActorValue(ActorValue::kHealth)) * bonusHPMultiplier);

    	HpCheck = Player->GetBaseActorValue(ActorValue::kHealth) + bonusHP;}
        if (MaxHealth <= HpCheck)     {
			Player->ModActorValue(ActorValue::kHealth, 1 * size);
			}

     if (MaxHealth > HpCheck + (1 * size) && MaxHealth > HpCheck) {
		Player->ModActorValue(ActorValue::kHealth, -1 * size); Player->RestoreActorValue(ActorValue::kHealth, 1 * size);
		}

	if (MaxHealth <= HpCheck)     {
		Player->ModActorValue(ActorValue::kHealth, 1 * size)
		}
   else if (MaxHealth > HpCheck + (1.0 * size) && MaxHealth > HpCheck && Player->GetActorValueMax(ActorValue::kHealth) >= Player->GetBaseActorValue(ActorValue::kHealth) - 1 * size && MaxHealth > Player->GetBaseActorValue(ActorValue::kHealth)) {
	Player->ModActorValue(ActorValue::kHealth, -1 * size); Player->RestoreActorValue(ActorValue::kHealth, 5 * size);
		}
 	}



	float MaxStamina = Player->GetPermanentActorValue(ActorValue::kCarryWeight);
	float bonusCarryWeight = ((Player->GetBaseActorValue(ActorValue::kCarryWeight) + (MaxStamina * 0.5) -50.0) * (size * bonusCarryWeightMultiplier));
    if (Player->GetBaseActorValue(ActorValue::kCarryWeight) < bonusCarryWeight && Player->GetActorValue(ActorValue::kCarryWeight) < bonusCarryWeight)
        {Player->ModActorValue(ActorValue::kCarryWeight, 1 * size);}    
    if (Player->GetActorValue(ActorValue::kCarryWeight) > bonusCarryWeight)
        {Player->ModActorValue(ActorValue::kCarryWeight, -1 * size);} 


	if (size > 0)
        if (bonusJumpHeightMultiplier != 0.0)
        {
            SetINIFloat("fJumpHeightMin", 76.0 + (76.0 * (size - 1) * bonusJumpHeightMultiplier));
            SetINIFloat("fJumpFallHeightMin", 600.0 + ( 600.0 * (size - 1) * bonusJumpHeightMultiplier));
        }
    else
        if (bonusJumpHeightMultiplier != 0.0)
        {
            SetINIFloat("fJumpHeightMin", 76.0);
            SetINIFloat("fJumpFallHeightMin", 600.0 + ((-size + 1.0) * 300 * bonusJumpHeightMultiplier));
        }	

        if (size >= 0)
    {Player->ForceActorValue(ActorValue::kAttackDamageMult, (size * bonusDamageMultiplier));}

    else
    if (bonusDamageMultiplier == 0.0)
        {Player->ForceActorValue(ActorValue::kAttackDamageMult, (size * bonusDamageMultiplier));}
    else
        {Player->ForceActorValue(ActorValue::kAttackDamageMult, (size * bonusDamageMultiplier));}
    }

  
       if (speedEffectiveSize > 1 && AllowTimeChange>= 1.00)
       {Player->SetActorValue(ActorValue::kSpeedMult, (100 + ((speedEffectiveSize - 1) * (100 * bonusSpeedMultiplier))));}   
       
       else if (speedEffectiveSize < 1 && AllowTimeChange >= 1.00)
        {Player->SetActorValue(ActorValue::kSpeedMult, (100 * size));}

    else
        if (bonusSpeedMultiplier == 0.0 && AllowTimeChange>= 1.00)
            {Player->SetActorValue(ActorValue::kSpeedMult, 100);

    }
}
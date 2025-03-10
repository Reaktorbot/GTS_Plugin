#include "magic/effects/CrushGrowth.hpp"
#include "magic/effects/common.hpp"
#include "magic/magic.hpp"
#include "scale/scale.hpp"
#include "data/runtime.hpp"
#include "util.hpp"


namespace Gts {
	std::string CrushGrowth::GetName() {
		return "CrushGrowth";
	}

	bool CrushGrowth::StartEffect(EffectSetting* effect) { // NOLINT
		auto& runtime = Runtime::GetSingleton();
		return effect == runtime.CrushGrowthMGEF;
	}

	void CrushGrowth::OnStart() {
		auto CrushedFoe = GetTarget();
		this->CrushGrowthAmount += 1.0;
		this->ScaleOnCrush = get_visual_scale(CrushedFoe);
	}

	void CrushGrowth::OnUpdate() {
		auto& runtime = Runtime::GetSingleton();
		auto caster = GetCaster();
        auto target = GetTarget();
		float CrushGrowthActivationCount = this->CrushGrowthAmount;

		if (!caster) {
			return;
		}
		if (!target) {
			return;
		}
        if (CrushGrowthActivationCount <= 1.0)
        
        {CrushGrowthActivationCount = 1.0;} // Just to be safe

        float GrowAmount = this->ScaleOnCrush;
        float Rate = 0.00025 * GrowAmount * CrushGrowthActivationCount;
        if (caster->HasPerk(runtime.AdditionalAbsorption))
		{Rate *= 2.0;}


		float size = get_visual_scale(caster); 
		float size2 = get_visual_scale(target);
		//log::info("Caster {}, target {}, GrowAmount {}, CrushGrowth Amount {}", size, size2, GrowAmount, CrushGrowthAmount);
        CrushGrow(caster, Rate, 0);
	}


    void CrushGrowth::OnFinish() {
        this->CrushGrowthAmount = 0.0;
		this->ScaleOnCrush = 1.0;
    }
}
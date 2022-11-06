#include "Config.hpp"
#include "managers/GrowthTremorManager.hpp"
#include "managers/GtsSizeManager.hpp"
#include "managers/GtsManager.hpp"
#include "managers/highheel.hpp"
#include "managers/Attributes.hpp"
#include "managers/InputManager.hpp"
#include "managers/hitmanager.hpp"
#include "magic/effects/smallmassivethreat.hpp"
#include "data/persistent.hpp"
#include "data/transient.hpp"
#include "data/runtime.hpp"
#include "data/time.hpp"
#include "scale/scale.hpp"
#include "util.hpp"
#include "node.hpp"
#include "timer.hpp"
#include <vector>
#include <string>

using namespace Gts;
using namespace RE;
using namespace SKSE;
using namespace std;

namespace {
	void update_height(Actor* actor, ActorData* persi_actor_data, TempActorData* trans_actor_data) {
		if (!actor) {
			return;
		}
		//if (actor->formID==0x14) {
		//log::info("Player's VS:{}, VS_V: {}", persi_actor_data->visual_scale, persi_actor_data->visual_scale_v);
		//}
		if (!actor->Is3DLoaded()) {
			return;
		}
		if (!trans_actor_data) {
			return;
		}
		if (!persi_actor_data) {
			return;
		}
		float target_scale = persi_actor_data->target_scale;

		// Smooth target_scale towards max_scale if target_scale > max_scale
		float max_scale = persi_actor_data->max_scale;
		if (target_scale > max_scale) {
			float minimum_scale_delta = 0.000005; // 0.00005%
			if (fabs(target_scale - max_scale) < minimum_scale_delta) {
				persi_actor_data->target_scale = max_scale;
				persi_actor_data->target_scale_v = 0.0;
			} else {
				critically_damped(
					persi_actor_data->target_scale,
					persi_actor_data->target_scale_v,
					max_scale,
					persi_actor_data->half_life*1.5,
					Time::WorldTimeDelta()
					);
			}
		} else {
			persi_actor_data->target_scale_v = 0.0;
		}

		if (fabs(target_scale - persi_actor_data->visual_scale) > 1e-5) {
			float minimum_scale_delta = 0.000005; // 0.00005%
			if (fabs(target_scale - persi_actor_data->visual_scale) < minimum_scale_delta) {
				persi_actor_data->visual_scale = target_scale;
				persi_actor_data->visual_scale_v = 0.0;
			} else {
				critically_damped(
					persi_actor_data->visual_scale,
					persi_actor_data->visual_scale_v,
					target_scale,
					persi_actor_data->half_life,
					Time::WorldTimeDelta()
					);
			}
		}
	}
	void apply_height(Actor* actor, ActorData* persi_actor_data, TempActorData* trans_actor_data, bool force = false) {
		if (!actor) {
			return;
		}
		if (!actor->Is3DLoaded()) {
			return;
		}
		if (!trans_actor_data) {
			return;
		}
		if (!persi_actor_data) {
			return;
		}
		float scale = get_scale(actor);
		if (scale < 0.0) {
			return;
		}
		float visual_scale = persi_actor_data->visual_scale;
		float change_requirement = Runtime::GetSingleton().sizeLimit->value + persi_actor_data->bonus_max_size;

		// Is scale correct already?
		if (fabs(visual_scale - scale) <= 1e-5 && !force) {
			return;
		}

		// Is scale too small
		if (visual_scale <= 1e-5) {
			return;
		}

		// log::trace("Scale changed from {} to {}. Updating",scale, visual_scale);
		set_scale(actor, visual_scale);
	}



	void update_effective_multi(Actor* actor, ActorData* persi_actor_data, TempActorData* trans_actor_data) {
		if (!actor) {
			return;
		}
		if (!persi_actor_data) {
			return;
		}
		auto small_massive_threat = Runtime::GetSingleton().SmallMassiveThreat;
		if (!small_massive_threat) {
			return;
		}
		if (actor->HasMagicEffect(small_massive_threat)) {
			persi_actor_data->effective_multi = 2.0;
		} else {
			persi_actor_data->effective_multi = 1.0;
		}
	}

	void update_actor(Actor* actor) {
		auto temp_data = Transient::GetSingleton().GetActorData(actor);
		auto saved_data = Persistent::GetSingleton().GetActorData(actor);
		update_effective_multi(actor, saved_data, temp_data);
		update_height(actor, saved_data, temp_data);
	}

	void apply_actor(Actor* actor, bool force = false) {
		//log::info("Apply_Actor name is {}", actor->GetDisplayFullName());
		auto temp_data = Transient::GetSingleton().GetData(actor);
		auto saved_data = Persistent::GetSingleton().GetData(actor);
		apply_height(actor, saved_data, temp_data, force);
		apply_speed(actor, saved_data, temp_data, force);
	}

	enum ChosenGameMode {
		None,
		Grow,
		Shrink,
		Standard,
		Quest,
	};


	void ApplyGameMode(Actor* actor, const ChosenGameMode& game_mode, const float& GrowthRate, const float& ShrinkRate )  {
		const float EPS = 1e-7;
		if (game_mode != ChosenGameMode::None) {
			float natural_scale = get_natural_scale(actor);
			float Scale = get_visual_scale(actor);
			float maxScale = get_max_scale(actor);
			float targetScale = get_target_scale(actor);
			switch (game_mode) {
				case ChosenGameMode::Grow: {
					float modAmount = Scale * (0.00010 + (GrowthRate * 0.25)) * 60 * Time::WorldTimeDelta();
					if (fabs(GrowthRate) < EPS) {
						return;
					}
					if ((targetScale + modAmount) < maxScale) {
						mod_target_scale(actor, modAmount);
					} else if (targetScale < maxScale) {
						set_target_scale(actor, maxScale);
					} // else let spring handle it
					break;
				}
				case ChosenGameMode::Shrink: {
					float modAmount = Scale * -(0.00025 + (ShrinkRate * 0.25)) * 60 * Time::WorldTimeDelta();
					if (fabs(ShrinkRate) < EPS) {
						return;
					}
					if ((targetScale + modAmount) > natural_scale) {
						mod_target_scale(actor, modAmount);
					} else if (targetScale > natural_scale) {
						set_target_scale(actor, natural_scale);
					} // Need to have size restored by someone
					break;
				}
				case ChosenGameMode::Standard: {
					if (actor->IsInCombat()) {
						float modAmount = Scale * (0.00008 + (GrowthRate * 0.17)) * 60 * Time::WorldTimeDelta();
						if (fabs(GrowthRate) < EPS) {
							return;
						}
						if ((targetScale + modAmount) < maxScale) {
							mod_target_scale(actor, modAmount);
						} else if (targetScale < maxScale) {
							set_target_scale(actor, maxScale);
						} // else let spring handle it
					} else {
						float modAmount = Scale * -(0.00029 + (ShrinkRate * 0.34)) * 60 * Time::WorldTimeDelta();
						if (fabs(ShrinkRate) < EPS) {
							return;
						}
						if ((targetScale + modAmount) > natural_scale) {
							mod_target_scale(actor, modAmount);
						} else if (targetScale > natural_scale) {
							set_target_scale(actor, natural_scale);
						} // Need to have size restored by someone
					}
				}
				case ChosenGameMode::Quest: {
					float modAmount = -ShrinkRate * Time::WorldTimeDelta();
					if (fabs(ShrinkRate) < EPS) {
						return;
					}
					if ((targetScale + modAmount) > natural_scale) {
						mod_target_scale(actor, modAmount);
					} else if (targetScale > natural_scale) {
						set_target_scale(actor, natural_scale);
					} // Need to have size restored by somethig
				}
			}
		}
	}

	void GameMode(Actor* actor)  {
		auto& runtime = Runtime::GetSingleton();

		ChosenGameMode gameMode = ChosenGameMode::None;
		float growthRate = 0.0;
		float shrinkRate = 0.0;
		int game_mode_int = 0;
		float QuestStage = runtime.MainQuest->GetCurrentStageID();
		float BalanceMode = SizeManager::GetSingleton().BalancedMode();
		float scale = get_visual_scale(actor);
		float BonusShrink = 1.0;
		if (BalanceMode >= 2.0) {
			BonusShrink = (2.0 * (scale * 2));
		}

		if (QuestStage < 100.0 || BalanceMode >= 2.0) {
			if (actor->formID == 0x14 && !actor->IsInCombat()) {
				game_mode_int = 4; // QuestMode
				if (QuestStage >= 40 && QuestStage < 60) {
					shrinkRate = 0.00086 * (((BalanceMode) * BonusShrink) * 1.5);
				} else if (QuestStage >= 60 && QuestStage < 70) {
					shrinkRate = 0.00086 * (((BalanceMode) * BonusShrink) * 1.0);
				} else if (BalanceMode >= 2.0 && QuestStage > 70) {
					shrinkRate = 0.00086 * (((BalanceMode) * BonusShrink) * 1.0);
				}


				if (actor->HasMagicEffect(runtime.EffectGrowthPotion)) {
					shrinkRate *= 0.0;
				} else if (actor->HasMagicEffect(runtime.ResistShrinkPotion)) {
					shrinkRate *= 0.25;
				}

				if (fabs(shrinkRate) <= 1e-6) {
					game_mode_int = 0; // Nothing to do
				}
			}
		} else if (QuestStage > 100.0 && BalanceMode <= 1.0) {
			if (actor->formID == 0x14) {
				game_mode_int = runtime.ChosenGameMode->value;
				growthRate = runtime.GrowthModeRate->value;
				shrinkRate = runtime.ShrinkModeRate->value;

			} else if (actor->formID != 0x14 && (actor->IsPlayerTeammate() || actor->IsInFaction(runtime.FollowerFaction))) {
				game_mode_int = runtime.ChosenGameModeNPC->value;
				growthRate = runtime.GrowthModeRateNPC->value;
				shrinkRate = runtime.ShrinkModeRateNPC->value;
			}
		}

		if (game_mode_int >=0 && game_mode_int <= 4) {
			gameMode = static_cast<ChosenGameMode>(game_mode_int);
		}

		ApplyGameMode(actor, gameMode, growthRate, shrinkRate);
	}
}

GtsManager& GtsManager::GetSingleton() noexcept {
	static GtsManager instance;

	static std::atomic_bool initialized;
	static std::latch latch(1);
	if (!initialized.exchange(true)) {
		latch.count_down();
	}
	latch.wait();

	return instance;
}

// Poll for updates
void GtsManager::Update() {
	for (auto actor: find_actors()) {
		if (!actor) {
			continue;
		}
		if (!actor->Is3DLoaded()) {
			continue;
		}
		//log::info("Found Actor {}", actor->GetDisplayFullName());
		update_actor(actor);
		apply_actor(actor);
		GameMode(actor);
		HitManager::GetSingleton().Update();
	}
}

void GtsManager::reapply(bool force) {
	// Get everyone in loaded AI data and reapply
	auto actors = find_actors();
	for (auto actor: actors) {
		if (!actor) {
			continue;
		}
		if (!actor->Is3DLoaded()) {
			continue;
		}
		reapply_actor(actor, force);
	}
}
void GtsManager::reapply_actor(Actor* actor, bool force) {
	// Reapply just this actor
	if (!actor) {
		return;
	}
	if (!actor->Is3DLoaded()) {
		return;
	}
	apply_actor(actor, force);
}

#include "hooks/character.h"
#include "Config.h"
#include "util.h"
#include "GtsManager.h"
#include "persistent.h"


using namespace RE;
using namespace SKSE;
using namespace Gts;

namespace Hooks
{
	void Hook_Character::Hook() {
		logger::info("Hooking Character");
		auto index = Config::GetSingleton().GetExperiment();
		logger::info("  - Hooking table {}", index);
		REL::Relocation<std::uintptr_t> ActorVtbl{ Character::VTABLE[index] };

		_Update = ActorVtbl.write_vfunc(0xAD, Update);
		_UpdateAnimation = ActorVtbl.write_vfunc(0x7D, UpdateAnimation);
	}

	void Hook_Character::Update(RE::Character* a_this, float a_delta) {
		log::info("Hook Character Update: {}", actor_name(a_this));
		float anim_speed = 1.0;
		if (Gts::GtsManager::GetSingleton().enabled) {
			auto saved_data = Gts::Persistent::GetSingleton().GetActorData(a_this);
			if (saved_data) {
				if (saved_data->anim_speed > 0.0) {
					log::info("Adjusting all speed for: {} to {}", actor_name(a_this), saved_data->anim_speed);
					anim_speed = saved_data->anim_speed;
				} else {
					log::info("all speed too low: {}", actor_name(a_this));
				}
			} else {
				log::info("No saved data for: {}", actor_name(a_this));
			}
		} else {
			log::info("Not enabled");
		}
		Update(a_this, a_delta * anim_speed);
	}

	void Hook_Character::UpdateAnimation(RE::Character* a_this, float a_delta) {
		log::info("Hook Character Anim: {}", actor_name(a_this));
		float anim_speed = 1.0;
		if (Gts::GtsManager::GetSingleton().enabled) {
			auto saved_data = Gts::Persistent::GetSingleton().GetActorData(a_this);
			if (saved_data) {
				if (saved_data->anim_speed > 0.0) {
					log::info("Adjusting anim speed for: {} to {}", actor_name(a_this), saved_data->anim_speed);
					anim_speed = saved_data->anim_speed;
				} else {
					log::info("anim speed too low: {}", actor_name(a_this));
				}
			} else {
				log::info("No saved data for: {}", actor_name(a_this));
			}
		} else {
			log::info("Not enabled");
		}
		_UpdateAnimation(a_this, a_delta * anim_speed);
	}
}

#include "hooks/character.h"
#include "util.h"
#include "managers/GtsManager.h"
#include "data/persistent.h"

using namespace RE;
using namespace SKSE;
using namespace Gts;

namespace Hooks
{
	void Hook_Character::Hook() {
		logger::info("Hooking Character");
		REL::Relocation<std::uintptr_t> ActorVtbl{ RE::VTABLE_Character[0] };

		_Update = ActorVtbl.write_vfunc(REL::Relocate(0xAD, 0x0AD, 0x0AF), Update);

		_GetRunSpeed = ActorVtbl.write_vfunc(REL::Relocate(0x0EB, 0x0EB, 0x0ED), GetRunSpeed);
		_GetJogSpeed = ActorVtbl.write_vfunc(REL::Relocate(0x0EC, 0x0EC, 0x0EE), GetJogSpeed);
		_GetFastWalkSpeed = ActorVtbl.write_vfunc(REL::Relocate(0x0ED, 0x0ED, 0x0EF), GetFastWalkSpeed);
		_GetWalkSpeed = ActorVtbl.write_vfunc(REL::Relocate(0x0EE, 0x0EE, 0x0F0), GetWalkSpeed);

		_ProcessTracking = ActorVtbl.write_vfunc(REL::Relocate(0x122, 0x122, 0x124), ProcessTracking);
	}

	// NPC Characters don't call UpdateAnimation like the PlayerCharacter
	// does. I was unable to find where it is updated (maybed in AI)
	// So this is an alternative hack
	// It works by either adding more animation or undoing animations
	// to that which skyrim does naturally
	void Hook_Character::Update(RE::Character* a_this, float a_delta) {
		_Update(a_this, a_delta);
		float current_delta = *g_delta_time;
		if (current_delta> 1e-5) {
			if (Gts::GtsManager::GetSingleton().enabled) {
				auto saved_data = Gts::Persistent::GetSingleton().GetActorData(a_this);
				if (saved_data) {
					float anim_speed = saved_data->anim_speed;
					if ((anim_speed > 0.0) && (fabs(anim_speed - 1.0) > 1e-5)) {
						float adjustment = current_delta * (anim_speed - 1.0);
						if (current_delta + adjustment > 1e-5) {
							a_this->UpdateAnimation(adjustment);
						}
					}
				}
			}
		}
	}

	float Hook_Character::GetRunSpeed(RE::Character* a_this) {
		float value = _GetRunSpeed(a_this);
		log::info("{} GetRunSpeed {}", actor_name(a_this), value);
		return value;
	}

	float Hook_Character::GetJogSpeed(RE::Character* a_this) {
		float value = _GetJogSpeed(a_this);
		log::info("{} GetJogSpeed {}", actor_name(a_this), value);
		return value;
	}

	float Hook_Character::GetFastWalkSpeed(RE::Character* a_this) {
		float value = _GetFastWalkSpeed(a_this);
		log::info("{} GetFastWalkSpeed {}", actor_name(a_this), value);
		return value;
	}

	float Hook_Character::GetWalkSpeed(RE::Character* a_this) {
		float value = _GetWalkSpeed(a_this);
		log::info("{} GetWalkSpeed {}", actor_name(a_this), value);
		return value;
	}

	void Hook_Character::ProcessTracking(RE::Character* a_this, float a_delta, NiAVObject* a_obj3D) {
		if (a_obj3D) {
			log::info("{} is tracking {} (update of {} s)", actor_name(a_this), a_obj3D->name.c_str(), a_delta);
		} else {
			log::info("{} is tracking unknown nullptr (update of {} s)", actor_name(a_this), a_delta);
		}
        if (a_this) {
            auto ai = a_this->currentProcess;
            if (ai) {
                auto high = ai->high;
                if (high) {
                    auto offset = high->headTrackTargetOffset;
                    log::info("  - Headtrack offset: {},{},{} for {}", offset.x, offset.y, offset.z, actor_name(a_this));
					log::info("  - Mutlipier: {}", GtsManager::GetSingleton().experiment);
					high->headTrackTargetOffset.x *= GtsManager::GetSingleton().experiment;
					high->headTrackTargetOffset.y *= GtsManager::GetSingleton().experiment;
					high->headTrackTargetOffset.z *= GtsManager::GetSingleton().experiment;
					auto offsetb = high->headTrackTargetOffset;
                    log::info("  - Headtrack offset changed to: {},{},{} for {}", offsetb.x, offsetb.y, offsetb.z, actor_name(a_this));
                }
            }
        }
		_ProcessTracking(a_this, a_delta, a_obj3D);
	}
}

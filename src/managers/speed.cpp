#pragma once
#include "managers/speed.hpp"
#include "data/persistent.hpp"
#include "util.hpp"

using namespace RE;
using namespace SKSE;

namespace Gts {
	void SpeedManager::DataReady() {
		Persistent::RegisterForSerde('SPED')
	}
	void SpeedManager::Update() {
		for (auto actor: find_actors()) {
			if (!this.is_speed_adjusted) {
				return;
			}
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

			float scale = persi_actor_data->visual_scale;
			if (scale < 1e-5) {
				//log::info("!SCALE IS < 1e-5! {}", actor->GetDisplayFullName());
				return;
			}
			SoftPotential& speed_adjustment = this->speed_adjustment;
			SoftPotential& MS_adjustment = this->MS_adjustment;
			float speed_mult = soft_core(scale, speed_adjustment);
			float MS_mult = soft_core(scale, MS_adjustment);
			float Bonus = Persistent::GetSingleton().GetActorData(actor)->smt_run_speed;
			float MS_mult_sprint_limit = clamp(0.65, 1.0, MS_mult); // For sprint
			float MS_mult_limit = clamp(0.750, 1.0, MS_mult); // For Walk speed
			float Multy = clamp(0.70, 1.0, MS_mult); // Additional 30% ms
			float WalkSpeedLimit = clamp(0.33, 1.0, MS_mult);
			float PerkSpeed = 1.0;

			static Timer timer = Timer(0.10); // Run every 0.10s or as soon as we can
			float IsFalling = Runtime::GetSingleton().IsFalling->value;

			if (actor->formID == 0x14 && IsJumping(actor) && IsFalling == 0.0) {
				Runtime::GetSingleton().IsFalling->value = 1.0;
			} else if (actor->formID == 0x14 && !IsJumping(actor) && IsFalling >= 1.0) {
				Runtime::GetSingleton().IsFalling->value = 0.0;
			}
			if (actor->HasPerk(Runtime::GetSingleton().BonusSpeedPerk)) {
				PerkSpeed = clamp(0.85, 1.0, MS_mult); // Used as a bonus 15% MS if PC has perk.
			}

			if (!actor->IsRunning()) {
				persi_actor_data->anim_speed = MS_mult;
			} else if (actor->IsRunning() && !actor->IsSprinting()) {
				persi_actor_data->anim_speed = speed_mult * WalkSpeedLimit;
			}


			if (timer.ShouldRunFrame()) {
				if (scale < 1.0) {
					actor->SetActorValue(ActorValue::kSpeedMult, trans_actor_data->base_walkspeedmult * scale);
				} else {
					actor->SetActorValue(ActorValue::kSpeedMult, ((trans_actor_data->base_walkspeedmult * (Bonus/3 + 1.0)))/ (MS_mult)/MS_mult_limit/Multy/PerkSpeed);
				}
			}
			// Experiement
			if (false) {
				auto& rot_speed = actor->currentProcess->middleHigh->rotationSpeed;
				if (fabs(rot_speed.x) > 1e-5 || fabs(rot_speed.y) > 1e-5 || fabs(rot_speed.z) > 1e-5) {
					log::info("{} rotationSpeed: {},{},{}", actor_name(actor), rot_speed.x,rot_speed.y,rot_speed.z);
					actor->currentProcess->middleHigh->rotationSpeed.x *= speed_mult;
					actor->currentProcess->middleHigh->rotationSpeed.y *= speed_mult;
					actor->currentProcess->middleHigh->rotationSpeed.z *= speed_mult;
				}
				auto& animationDelta = actor->currentProcess->high->animationDelta;
				if (fabs(animationDelta.x) > 1e-5 || fabs(animationDelta.y) > 1e-5 || fabs(animationDelta.z) > 1e-5) {
					log::info("{} animationDelta: {},{},{}", actor_name(actor), animationDelta.x,animationDelta.y,animationDelta.z);
				}
				auto& animationAngleMod = actor->currentProcess->high->animationAngleMod;
				if (fabs(animationAngleMod.x) > 1e-5 || fabs(animationAngleMod.y) > 1e-5 || fabs(animationAngleMod.z) > 1e-5) {
					log::info("{} animationAngleMod: {},{},{}", actor_name(actor), animationAngleMod.x,animationAngleMod.y,animationAngleMod.z);
				}
				auto& pathingCurrentRotationSpeed = actor->currentProcess->high->pathingCurrentRotationSpeed;
				if (fabs(pathingCurrentRotationSpeed.x) > 1e-5 || fabs(pathingCurrentRotationSpeed.y) > 1e-5 || fabs(pathingCurrentRotationSpeed.z) > 1e-5) {
					log::info("{} pathingCurrentRotationSpeed: {},{},{}", actor_name(actor), pathingCurrentRotationSpeed.x,pathingCurrentRotationSpeed.y,pathingCurrentRotationSpeed.z);
				}
				auto& pathingDesiredRotationSpeed = actor->currentProcess->high->pathingDesiredRotationSpeed;
				if (fabs(pathingDesiredRotationSpeed.x) > 1e-5 || fabs(pathingDesiredRotationSpeed.y) > 1e-5 || fabs(pathingDesiredRotationSpeed.z) > 1e-5) {
					log::info("{} pathingDesiredRotationSpeed: {},{},{}", actor_name(actor), pathingDesiredRotationSpeed.x,pathingDesiredRotationSpeed.y,pathingDesiredRotationSpeed.z);
				}
			}
		}
	}

	void SpeedManager::ser(SerializationInterface* serde, int version) {
		serde->WriteRecordData(&this->is_speed_adjusted, sizeof(this->is_speed_adjusted));

		serde->WriteRecordData(&this->speed_adjustment.k, sizeof(this->speed_adjustment.k));
		serde->WriteRecordData(&this->speed_adjustment.n, sizeof(this->speed_adjustment.n));
		serde->WriteRecordData(&this->speed_adjustment.s, sizeof(this->speed_adjustment.s));
		serde->WriteRecordData(&this->speed_adjustment.o, sizeof(this->speed_adjustment.o));
		serde->WriteRecordData(&this->speed_adjustment.a, sizeof(this->speed_adjustment.a));

		serde->WriteRecordData(&this->MS_adjustment.k, sizeof(this->MS_adjustment.k));
		serde->WriteRecordData(&this->MS_adjustment.n, sizeof(this->MS_adjustment.n));
		serde->WriteRecordData(&this->MS_adjustment.s, sizeof(this->MS_adjustment.s));
		serde->WriteRecordData(&this->MS_adjustment.o, sizeof(this->MS_adjustment.o));
		serde->WriteRecordData(&this->MS_adjustment.a, sizeof(this->MS_adjustment.a));
	}
	void SpeedManager::de(SerializationInterface* serde, int version) {
		serde->ReadRecordData(&this->is_speed_adjusted, sizeof(this->is_speed_adjusted));

		serde->ReadRecordData(&this->speed_adjustment.k, sizeof(this->speed_adjustment.k));
		serde->ReadRecordData(&this->speed_adjustment.n, sizeof(this->speed_adjustment.n));
		serde->ReadRecordData(&this->speed_adjustment.s, sizeof(this->speed_adjustment.s));
		serde->ReadRecordData(&this->speed_adjustment.o, sizeof(this->speed_adjustment.o));
		serde->ReadRecordData(&this->speed_adjustment.a, sizeof(this->speed_adjustment.a));

		serde->ReadRecordData(&this->MS_adjustment.k, sizeof(this->MS_adjustment.k));
		serde->ReadRecordData(&this->MS_adjustment.n, sizeof(this->MS_adjustment.n));
		serde->ReadRecordData(&this->MS_adjustment.s, sizeof(this->MS_adjustment.s));
		serde->ReadRecordData(&this->MS_adjustment.o, sizeof(this->MS_adjustment.o));
		serde->ReadRecordData(&this->MS_adjustment.a, sizeof(this->MS_adjustment.a));
	}
}

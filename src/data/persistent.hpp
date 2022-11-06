#pragma once
// Module that holds data that is persistent across saves

#include "events.hpp"
#include "scale/modscale.hpp"
#include "util.hpp"
#include "data/serde.hpp"

using namespace std;
using namespace SKSE;
using namespace RE;
using namespace Gts;

namespace Gts {
	struct ActorData {
		float native_scale;
		float visual_scale;
		float visual_scale_v;
		float target_scale;
		float target_scale_v;
		float max_scale;
		float half_life;
		float anim_speed;
		float effective_multi;
		float bonus_hp;
		float bonus_carry;
		float bonus_max_size;
		float smt_run_speed;

		ActorData();
		ActorData(Actor* actor);
	};

	struct CameraCollisions {
		bool enable_trees = false;
		bool enable_debris = false;
		bool enable_static = true;
		bool enable_terrain = true;
		bool enable_actor = false;
		float above_scale = 5.0;
	};

	class Persistent : public Gts::EventListener {
		public:
			virtual void Reset() override;
			virtual void ResetActor(Actor* actor) override;

			[[nodiscard]] static Persistent& GetSingleton() noexcept;
			static void OnRevert(SKSE::SerializationInterface*);
			static void OnGameSaved(SKSE::SerializationInterface* serde);
			static void OnGameLoaded(SKSE::SerializationInterface* serde);

			static void RegisterForSerde(long tag, Serde* callback);

			ActorData* GetActorData(Actor* actor);
			ActorData* GetData(TESObjectREFR* refr);

			std::unordered_map<long, Serde*> serde_registry;

			CameraCollisions camera_collisions;
		private:
			Persistent() = default;

			mutable std::mutex _lock;
			std::unordered_map<FormID, ActorData> _actor_data;
	};
}

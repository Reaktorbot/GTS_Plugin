#pragma once
// Module that holds data that is not persistent across saves


using namespace std;
using namespace SKSE;
using namespace RE;

namespace Gts {
	struct TempActorData {
		float base_height;
		float base_volume;
		float last_hh_adjustment;
		float total_hh_adjustment;
		float base_walkspeedmult;
		float char_weight;
		float shoe_weight;
		bool has_hh_bonus_perk;
		bool is_teammate;

		inline bool WearingHh() {
			return fabs(last_hh_adjustment) > 1e-5;
		}
		inline float GetHhBonusFactor() {
			if (WearingHh() && has_hh_bonus_perk) {
				return 1.5;// + shoe_weight/10.0 + char_weight/260;
			} 				return 1.0;
		
		}
	};

	class Transient {
		public:
			[[nodiscard]] static Transient& GetSingleton() noexcept;

			TempActorData* GetData(TESObjectREFR* object);
			TempActorData* GetActorData(Actor* actor);
			void UpdateActorData(Actor* actor);

			void Clear();
		private:

			mutable std::mutex _lock;
			std::unordered_map<FormID, TempActorData> _actor_data;
	};
}

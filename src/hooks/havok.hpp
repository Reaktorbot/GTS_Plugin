#pragma once
#include "hooks/hooks.hpp"

using namespace RE;
using namespace SKSE;

namespace Hooks
{

	class HookHavok
	{
		public:
			static void Hook(Trampoline& trampoline);

		private:
			enum class CollisionFilterComparisonResult : uint8_t
			{
				Continue,  // Do not affect whether the two objects should collide
				Collide,   // Force the two objects to collide
				Ignore,    // Force the two objects to not collide
			};

			static CollisionFilterComparisonResult CompareFilterInfo(bhkCollisionFilter* a_collision_filter, uint32_t a_filter_info_a, uint32_t a_filter_info_b);

			static void ProcessHavokHitJobs(void* a1);
			static inline REL::Relocation<decltype(ProcessHavokHitJobs)> process_havok_hit_jobs;

			static bool BhkCollisionFilterCompareFilterInfo1(RE::bhkCollisionFilter* a_this, uint32_t a_filter_info_a, uint32_t a_filter_info_b);
			static bool BhkCollisionFilterCompareFilterInfo2(RE::bhkCollisionFilter* a_this, uint32_t a_filter_info_a, uint32_t a_filter_info_b);
			static bool BhkCollisionFilterCompareFilterInfo3(RE::bhkCollisionFilter* a_this, uint32_t a_filter_info_a, uint32_t a_filter_info_b);
			static bool BhkCollisionFilterCompareFilterInfo4(RE::bhkCollisionFilter* a_this, uint32_t a_filter_info_a, uint32_t a_filter_info_b);
			static bool BhkCollisionFilterCompareFilterInfo5(RE::bhkCollisionFilter* a_this, uint32_t a_filter_info_a, uint32_t a_filter_info_b);
			static bool BhkCollisionFilterCompareFilterInfo6(RE::bhkCollisionFilter* a_this, uint32_t a_filter_info_a, uint32_t a_filter_info_b);
			static bool BhkCollisionFilterCompareFilterInfo7(RE::bhkCollisionFilter* a_this, uint32_t a_filter_info_a, uint32_t a_filter_info_b);
			static inline REL::Relocation<decltype(bhkCollisionFilter_CompareFilterInfo1)> bhk_collision_filter_compare_filter_info1;
			static inline REL::Relocation<decltype(bhkCollisionFilter_CompareFilterInfo2)> bhk_collision_filter_compare_filter_info2;
			static inline REL::Relocation<decltype(bhkCollisionFilter_CompareFilterInfo3)> bhk_collision_filter_compare_filter_info3;
			static inline REL::Relocation<decltype(bhkCollisionFilter_CompareFilterInfo4)> bhk_collision_filter_compare_filter_info4;
			static inline REL::Relocation<decltype(bhkCollisionFilter_CompareFilterInfo5)> bhk_collision_filter_compare_filter_info5;
			static inline REL::Relocation<decltype(bhkCollisionFilter_CompareFilterInfo6)> bhk_collision_filter_compare_filter_info6;
			static inline REL::Relocation<decltype(bhkCollisionFilter_CompareFilterInfo7)> bhk_collision_filter_compare_filter_info7;

	};
}

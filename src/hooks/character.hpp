#pragma once
#include "hooks/hooks.hpp"

using namespace RE;
using namespace SKSE;

namespace Hooks
{
	class HookCharacter
	{
		public:
			static void Hook();
		private:

			static void Update(RE::Character* a_this, float a_delta);
			static inline REL::Relocation<decltype(Update)> update;

			static float GetRunSpeed(RE::Character* a_this);
			static inline REL::Relocation<decltype(GetRunSpeed)> get_run_speed;

			static float GetJogSpeed(RE::Character* a_this);
			static inline REL::Relocation<decltype(GetJogSpeed)> get_jog_speed;

			static float GetFastWalkSpeed(RE::Character* a_this);
			static inline REL::Relocation<decltype(GetFastWalkSpeed)> get_fast_walk_speed;

			static float GetWalkSpeed(RE::Character* a_this);
			static inline REL::Relocation<decltype(GetWalkSpeed)> get_walk_speed;

			static void ProcessTracking(RE::Character* a_this, float a_delta, NiAVObject* a_obj3_d);
			static inline REL::Relocation<decltype(ProcessTracking)> process_tracking;
	};
}

#pragma once
#include "hooks/hooks.hpp"

using namespace RE;
using namespace SKSE;

namespace Hooks
{
	class HookPlayer
	{
		public:
			static void Hook();
		private:

			static void UpdateAnimation(RE::PlayerCharacter* a_this, float a_delta);
			static inline REL::Relocation<decltype(UpdateAnimation)> update_animation;

			static float GetRunSpeed(RE::Character* a_this);
			static inline REL::Relocation<decltype(GetRunSpeed)> get_run_speed;

			static float GetJogSpeed(RE::Character* a_this);
			static inline REL::Relocation<decltype(GetJogSpeed)> get_jog_speed;

			static float GetFastWalkSpeed(RE::Character* a_this);
			static inline REL::Relocation<decltype(GetFastWalkSpeed)> get_fast_walk_speed;

			static float GetWalkSpeed(RE::Character* a_this);
			static inline REL::Relocation<decltype(GetWalkSpeed)> get_walk_speed;
	};
}

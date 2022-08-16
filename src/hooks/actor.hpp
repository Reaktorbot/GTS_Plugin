#pragma once
#include "hooks/hooks.hpp"

using namespace RE;
using namespace SKSE;

namespace Hooks
{
	class HookActor
	{
		public:
			static void Hook();
		private:

			static void UpdateAnimation(RE::Actor* a_this, float a_delta);
			static inline REL::Relocation<decltype(UpdateAnimation)> update_animation;
	};
}

#pragma once
#include "hooks/hooks.hpp"

using namespace RE;
using namespace SKSE;

namespace Hooks
{
	class HookBgsImpactManager
	{
		public:
			static void Hook();
		private:

			static BSEventNotifyControl ProcessEvent(Hook_BGSImpactManager* a_this, const BGSFootstepEvent* a_event, BSTEventSource<BGSFootstepEvent>* a_eventSource);
			static inline REL::Relocation<decltype(ProcessEvent)> process_event;
	};
}

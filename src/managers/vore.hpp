#pragma once
#include "events.hpp"

using namespace std;
using namespace SKSE;
using namespace RE;

namespace Gts
{

	class Vore : public EventListener
	{
		public:
			[[nodiscard]] static Vore& GetSingleton() noexcept;

			virtual void Update() override;

			// Get's vore target for pred using the crosshair
			// This will only return actors with appropiate distance/scale
			// as based on `CanVore`
			Actor* GeVoreTargetCrossHair(Actor* pred);

			// Get's vore target for any actor based on direction they are facing
			// This will only return actors with appropiate distance/scale
			// as based on `CanVore`
			Actor* GetVoreTargetInFront(Actor* pred);

			// Get's vore target for any actor based on distance from pred
			// This will only return actors with appropiate distance/scale
			// as based on `CanVore`  and can return multiple targets
			Actor* GetVoreTargetsInFront(Actor* pred, std::size_t numberOfPrey);

			// Get's vore target for any actor based on direction they are facing
			// This will only return actors with appropiate distance/scale
			std::vector<Actor*> GetVoreTargetAround(Actor* pred);

			// Get's vore target for any actor based on distance from pred
			// This will only return actors with appropiate distance/scale
			// as based on `CanVore` and can return multiple targets
			std::vector<Actor*> GetVoreTargetsAround(Actor* pred, std::size_t numberOfPrey);

			// Check if they can vore based on size difference and reach distance
			bool CanVore(Actor* pred, Actor* prey);

			// Do the vore (this has no checks make sure they can vore with CanVore first)
			void StartVore(Actor* pred, Actor* prey);
	};
}

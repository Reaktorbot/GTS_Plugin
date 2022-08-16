#pragma once
// Handles the various methods of scaling an actor


using namespace std;
using namespace RE;
using namespace SKSE;

namespace Gts {
	void SetTargetScale(Actor* actor, float height);
	float GetTargetScale(Actor* actor);
	void ModTargetScale(Actor* actor, float amt);

	void SetMaxScale(Actor* actor, float height);
	float GetMaxScale(Actor* actor);
	void ModMaxScale(Actor* actor, float amt);

	float GetVisualScale(Actor* actor);
	float GetEffectiveScale(Actor* actor);
}

#pragma once
// Handles the various methods of scaling an actor


using namespace std;
using namespace RE;
using namespace SKSE;

namespace Gts {
	void SetTargetHeight(Actor* actor, float height);
	float GetTargetHeight(Actor* actor);
	void ModTargetHeight(Actor* actor, float amt);

	void SetMaxHeight(Actor* actor, float height);
	float GetMaxHeight(Actor* actor);
	void ModMaxHeight(Actor* actor, float amt);

	float GetVisualHeight(Actor* actor);
}

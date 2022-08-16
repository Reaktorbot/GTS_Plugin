#pragma once
// Handles the various methods of scaling an actor


using namespace std;
using namespace RE;
using namespace SKSE;

namespace Gts {
	enum SizeMethod {
		ModelScale = 0,
		RootScale = 1,
		RefScale = 2,
	};

	void SetRefScale(Actor* actor, float target_scale);
	bool SetModelScale(Actor* actor, float target_scale);
	bool SetNpcnodeScale(Actor* actor, float target_scale);
	float GetNpcnodeScale(Actor* actor);
	float GetModelScale(Actor* actor);
	float GetRefScale(Actor* actor);
	float GetScale(Actor* actor);
	bool SetScale(Actor* actor, float scale);
}

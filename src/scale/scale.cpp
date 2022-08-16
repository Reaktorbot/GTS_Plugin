#include "scale/height.hpp"
#include "util.hpp"
#include "managers/GtsManager.hpp"
#include "data/persistent.hpp"

using namespace Gts;

namespace Gts {
	void SetTargetScale(Actor* actor, float scale) {
		if (actor != nullptr) {
			auto actor_data = Persistent::GetSingleton().GetData(actor);
			if (actor_data) {
				actor_data->target_scale = scale;
			}
		}
	}

	float GetTargetScale(Actor* actor) {
		if (actor != nullptr) {
			auto actor_data = Persistent::GetSingleton().GetData(actor);
			if (actor_data) {
				return actor_data->target_scale;
			}
		}
		return -1.0;
	}

	void ModTargetScale(Actor* actor, float amt) {
		if (actor != nullptr) {
			auto actor_data = Persistent::GetSingleton().GetData(actor);
			if (actor_data) {
				actor_data->target_scale += amt;
			}
		}
	}

	void SetMaxScale(Actor* actor, float scale) {
		if (actor != nullptr) {
			auto actor_data = Persistent::GetSingleton().GetData(actor);
			if (actor_data) {
				actor_data->max_scale = scale;
			}
		}
	}

	float GetMaxScale(Actor* actor) {
		if (actor != nullptr) {
			auto actor_data = Persistent::GetSingleton().GetData(actor);
			if (actor_data) {
				return actor_data->max_scale;
			}
		}
		return -1.0;
	}
	void ModMaxScale(Actor* actor, float amt) {
		if (actor != nullptr) {
			auto actor_data = Persistent::GetSingleton().GetData(actor);
			if (actor_data) {
				actor_data->max_scale += amt;
			}
		}
	}

	float GetVisualScale(Actor* actor) {
		if (actor != nullptr) {
			auto actor_data = Persistent::GetSingleton().GetData(actor);
			if (actor_data) {
				return actor_data->visual_scale;
			}
		}
		return -1.0;
	}

	float GetEffectiveScale(Actor* actor) {
		if (actor != nullptr) {
			auto actor_data = Persistent::GetSingleton().GetData(actor);
			if (actor_data) {
				return actor_data->visual_scale * actor_data->effective_multi;
			}
		}
		return -1.0;
	}
}

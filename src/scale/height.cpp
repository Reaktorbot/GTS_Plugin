#include "scale/height.hpp"
#include "scale/scale.hpp"
#include "util.hpp"
#include "managers/GtsManager.hpp"
#include "data/transient.hpp"

using namespace Gts;

namespace {
	float HeightToScale(Actor* actor, float height) {
		if (actor == nullptr) {
			return -1.0;
		}
		auto temp_actor_data = Transient::GetSingleton().GetData(actor);
		if (!temp_actor_data) {
			return -1.0;
		}
		return height / temp_actor_data->base_height;
	}

	float ScaleToHeight(Actor* actor, float scale) {
		if (actor == nullptr) {
			return -1.0;
		}
		auto temp_actor_data = Transient::GetSingleton().GetData(actor);
		if (!temp_actor_data) {
			return -1.0;
		}
		return scale * temp_actor_data->base_height;
	}

}

namespace Gts {
	void SetTargetHeight(Actor* actor, float height) {
		float scale = HeightToScale(actor, height);
		set_target_scale(actor, scale);
	}

	float GetTargetHeight(Actor* actor) {
		float scale = get_target_scale(actor);
		return ScaleToHeight(actor, scale);
	}

	void ModTargetHeight(Actor* actor, float amt) {
		float current_scale = get_target_scale(actor);
		float current_height = ScaleToHeight(actor, current_scale);
		float target_height = (current_height + amt);
		float target_scale = HeightToScale(actor, target_height);
		float scale_delta = target_scale - current_scale;
		mod_target_scale(actor, scale_delta);
	}

	void SetMaxHeight(Actor* actor, float height) {
		float scale = HeightToScale(actor, height);
		set_max_scale(actor, scale);
	}

	float GetMaxHeight(Actor* actor) {
		float scale = get_max_scale(actor);
		return ScaleToHeight(actor, scale);
	}
	void ModMaxHeight(Actor* actor, float amt) {
		float current_scale = get_max_scale(actor);
		float current_height = ScaleToHeight(actor, current_scale);
		float target_height = (current_height + amt);
		float target_scale = HeightToScale(actor, target_height);
		float scale_delta = target_scale - current_scale;
		mod_max_scale(actor, scale_delta);
	}

	float GetVisualHeight(Actor* actor) {
		float scale = get_visual_scale(actor);
		return ScaleToHeight(actor, scale);
	}

	float GetEffectiveHeight(Actor* actor) {
		float scale = get_effective_scale(actor);
		return ScaleToHeight(actor, scale);
	}
}

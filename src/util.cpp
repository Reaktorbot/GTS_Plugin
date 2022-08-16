#include "util.hpp"

using namespace Gts;

namespace {
	// Spring code from https://theorangeduck.com/page/spring-roll-call
	float HalflifeToDamping(float halflife, float eps = 1e-5F)
	{
		return (4.0F * 0.69314718056F) / (halflife + eps);
	}

	float DampingToHalflife(float damping, float eps = 1e-5F)
	{
		return (4.0F * 0.69314718056F) / (damping + eps);
	}
	float FastNegexp(float x)
	{
		return 1.0F / (1.0F + x + 0.48F*x*x + 0.235F*x*x*x);
	}
}
namespace Gts {
	/**
	 * Find actors in ai manager that are loaded
	 */
	vector<Actor*> FindActors() {
		vector<Actor*> result;

		auto high_actors = find_actors_high();
		result.insert(result.end(), high_actors.begin(), high_actors.end());

		auto middle_high_actors = find_actors_middle_high();
		result.insert(result.end(), middle_high_actors.begin(), middle_high_actors.end());

		auto middle_low_actors = find_actors_high();
		result.insert(result.end(), middle_low_actors.begin(), middle_low_actors.end());

		auto low_actors = find_actors_high();
		result.insert(result.end(), low_actors.begin(), low_actors.end());

		return result;
	}

	vector<Actor*> FindActorsHigh() {
		vector<Actor*> result;

		auto process_list = ProcessLists::GetSingleton();
		for (ActorHandle actor_handle: process_list->highActorHandles)
		{
			if (!actor_handle) {
				continue;
			}
			auto actor_smartptr = actor_handle.get();
			if (!actor_smartptr) {
				continue;
			}

			Actor* actor = actor_smartptr.get();
			// auto actor = actor_handle.get().get();
			if (actor && actor->Is3DLoaded()) {
				result.push_back(actor);
			}
		}
		auto player = PlayerCharacter::GetSingleton();
		if (player && player->Is3DLoaded()) {
			result.push_back(player);
		}
		return result;
	}

	vector<Actor*> FindActorsMiddleHigh() {
		vector<Actor*> result;

		auto process_list = ProcessLists::GetSingleton();
		for (ActorHandle actor_handle: process_list->middleHighActorHandles)
		{
			if (!actor_handle) {
				continue;
			}
			auto actor_smartptr = actor_handle.get();
			if (!actor_smartptr) {
				continue;
			}

			Actor* actor = actor_smartptr.get();
			// auto actor = actor_handle.get().get();
			if (actor && actor->Is3DLoaded()) {
				result.push_back(actor);
			}
		}
		return result;
	}

	vector<Actor*> FindActorsMiddleLow() {
		vector<Actor*> result;

		auto process_list = ProcessLists::GetSingleton();
		for (ActorHandle actor_handle: process_list->middleLowActorHandles)
		{
			if (!actor_handle) {
				continue;
			}
			auto actor_smartptr = actor_handle.get();
			if (!actor_smartptr) {
				continue;
			}

			Actor* actor = actor_smartptr.get();
			// auto actor = actor_handle.get().get();
			if (actor && actor->Is3DLoaded()) {
				result.push_back(actor);
			}
		}
		return result;
	}

	vector<Actor*> FindActorsLow() {
		vector<Actor*> result;

		auto process_list = ProcessLists::GetSingleton();
		for (ActorHandle actor_handle: process_list->lowActorHandles)
		{
			if (!actor_handle) {
				continue;
			}
			auto actor_smartptr = actor_handle.get();
			if (!actor_smartptr) {
				continue;
			}

			Actor* actor = actor_smartptr.get();
			// auto actor = actor_handle.get().get();
			if (actor && actor->Is3DLoaded()) {
				result.push_back(actor);
			}
		}
		return result;
	}

	float unit_to_meter(const float& unit) {
		// Game reports that the height of a slaughterfish is 0.31861934
		// From inspecting the bounding box of the slaughterfish and applying
		// base actor scales the unit height is 22.300568
		// Assuming 0.31861934 is meters and that bouding box is in model unit space
		// then the conversion factor is 70
		// Slaughterfish was chosen because it has scales of 1.0 (and was in my worldspace)
		// The scaling factor of 70 also applies to actor heights (once you remove)
		// race specific height scaling
		return unit / 70.0;
	}

	float meter_to_unit(const float& meter) {
		// Game reports that the height of a slaughterfish is 0.31861934
		// From inspecting the bounding box of the slaughterfish and applying
		// base actor scales the unit height is 22.300568
		// Assuming 0.31861934 is meters and that bouding box is in model unit space
		// then the conversion factor is 70
		// Slaughterfish was chosen because it has scales of 1.0 (and was in my worldspace)
		// The scaling factor of 70 also applies to actor heights (once you remove)
		// race specific height scaling
		return meter * 70.0;
	}

	NiPoint3 UnitToMeter(const NiPoint3& unit) {
		return unit / 70.0;
	}
	NiPoint3 MeterToUnit(const NiPoint3& meter) {
		return meter * 70.0;
	}

	void critically_damped(
		float& x,
		float& v,
		float x_goal,
		float halflife,
		float dt)
	{
		float y = HalflifeToDamping(halflife) / 2.0F;
		float j0 = x - x_goal;
		float j1 = v + j0*y;
		float eydt = FastNegexp(y*dt);

		x = eydt*(j0 + j1*dt) + x_goal;
		v = eydt*(v - j1*y*dt);
	}

	std::atomic_bool& get_main_thread() {
		static std::atomic_bool main_thread(false);
		return main_thread;
	}
}

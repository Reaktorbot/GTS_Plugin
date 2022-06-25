#include <SKSE/SKSE.h>
#include <Config.h>
#include <GtsManager.h>
#include <vector>
#include <string>

using namespace Gts;
using namespace RE;
using namespace SKSE;
using namespace std;

namespace {
	/**
	 * Find actors in ai manager that are loaded
	 */
	vector<ActorHandle> find_actors() {
		vector<ActorHandle> result;

		auto process_list = ProcessLists::GetSingleton();
		for (ActorHandle actor_handle: process_list->highActorHandles)
		{
			auto actor = actor_handle.get();
			if (actor && actor->Is3DLoaded())
			{
				result.push_back(actor_handle);
			}
		}

		return result;
	}

	float get_height(Actor* actor) {
		auto model = actor->Get3D(false);
		if (model) {
			float previous_radius = model->worldBound.radius;
			model->UpdateWorldBound();
			float new_radius = model->worldBound.radius;
			log::info("Old: {}, New: {}", previous_radius, new_radius);
			float factor = new_radius/previous_radius;
			if (fabs(factor - 1.0) > 1e-4) {
				auto char_controller = actor->GetCharController();
				if (char_controller) {
					log::info("Updating collision bounds");
					char_controller->collisionBound.extents *= factor;
					char_controller->bumperCollisionBound.extents *= factor;
				}
			}
		}
		auto min = actor->GetBoundMin();
		auto max = actor->GetBoundMax();
		auto diff = max.z - min.z;
		auto height = actor->GetBaseHeight() * diff;

		return height;
	}

	void walking_node(NiAVObject* node, std::string& indent) {
		log::info("BEGIN");
		if (!node) {
			return;
		}
		log::info("B");
		std::string name = ""; //node->name.c_str();
		log::info("C");
		if (name.data()) {
			log::info("D");
			if (!node->name.empty()) {
				log::info("{}Node {}", indent, node->name);
			} else {
				log::info("{}Node <Unnamed>", indent);
			}
		} else {
			log::info("{}Node <Invalid>", indent);
		}
		log::info("E");
		NiNode* ni_node = node->AsNode();
		log::info("F");
		if (ni_node) {
			log::info("G");
			const auto children = ni_node->GetChildren();
			log::info("H");
			if (children.begin()) {
				log::info("I");
				if (!children.empty()) {
					log::info("J");
					auto size = children.size();
					NiAVObject* child;
					for(std::size_t i = 0; i < size; ++i) {
						log::info("K");
						log::info("ENTER {} of {} for {}", i +1, size, name);
						child = children[i].get();
						log::info("L");
						indent.push_back(' ');
						indent.push_back(' ');
						log::info("M");
						if (child) {
							walking_node(child, indent);
						}
						indent.pop_back();
						indent.pop_back();
						log::info("EXIT {} of {} for {}", i + 1, size, name);
					}
				} else {
					log::info("{}Empty children", indent);
				}
			} else {
				log::info("{}No children", indent);
			}
		}
		log::info("END");
	}
	void walk_nodes(Actor* actor) {
		if (!actor->Is3DLoaded()) {
			return;
		}
		if (!actor || !actor->loadedData || !actor->loadedData->data3D) {
			return;
		}
		auto model = actor->loadedData->data3D;
		auto name = model->name;
		log::info("Root Node {}!", name);
		std::string indent = "  ";
		walking_node(model.get(), indent);
		log::info("Walk Complete!");
	}
}

GtsManager& GtsManager::GetSingleton() noexcept {
	static GtsManager instance;
	return instance;
}

// Poll for updates
void GtsManager::poll() {
	auto player_char = RE::PlayerCharacter::GetSingleton();
	if (!player_char) {
		return;
	}
	if (!player_char->Is3DLoaded()) {
		return;
	}

	auto ui = RE::UI::GetSingleton();
	if (!ui->GameIsPaused()) {
		log::info("Pre Poll");
		const auto& frame_config = Gts::Config::GetSingleton().GetFrame();
		auto init_delay = frame_config.GetInitDelay();
		auto step = frame_config.GetStep() + 1; // 1 Based index
		log::info("Config: delay: {}, step: {}", init_delay, step);

		auto current_frame = this->frame_count.fetch_add(1);
		log::info("Atomic");
		log::info("Frame: {}", current_frame);
		if (current_frame < init_delay) {
			log::info("Delayed");
			return;
		}
		log::info("Not Delayed");
		if (current_frame % step != 0) {
			log::info("Skipped");
			return;
		}

		log::info("Poll.");

		auto actor_handles = find_actors();
		for (auto actor_handle: actor_handles) {
			auto sptr_actor = actor_handle.get();
			if (sptr_actor) {
				auto actor = sptr_actor.get();
				if (actor) {
					auto base_actor = actor->GetActorBase();
					auto actor_name = base_actor->GetFullName();

					auto race = actor->GetRace();
					auto race_name = race->GetFullName();

					auto height = get_height(actor);

					log::info("Actor {} with race {} found with height {}!", actor_name, race_name, height);
					walk_nodes(actor);
					log::info("Actor {} with race {} found with height {}!", actor_name, race_name, height);
				}
			}
		}

	}
}

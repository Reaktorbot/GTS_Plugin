#pragma once
// Module that handles footsteps

#include "managers/impact.hpp"
#include "data/serde.hpp"

using namespace std;
using namespace SKSE;
using namespace RE;

namespace Gts {
	class TremorManager : public EventListener, public Serde {
		public:
			[[nodiscard]] static TremorManager& GetSingleton() noexcept;

			void OnImpact(const Impact& impact);

			virtual void DataReady() override;
			virtual void ser(SerializationInterface* serde, int version) override;
			virtual void de(SerializationInterface* serde, int version) override;

			float tremor_scale = 1.0;
			float npc_tremor_scale = 1.0;
	};
}

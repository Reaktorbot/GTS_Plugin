#pragma once
#include "data/transient.hpp"
#include "events.hpp"
#include "data/serde.hpp"
// Module that handles high heel

using namespace RE;
using namespace SKSE;

namespace Gts {
	class HighHeelManager : public EventListener, public Serde {
		public:
			[[nodiscard]] static HighHeelManager& GetSingleton() noexcept;

			virtual void DataReady() override;
			virtual void PapyrusUpdate() override;
			virtual void ActorEquip(Actor* actor) override;
			virtual void ActorLoaded(Actor* actor) override;

			virtual void ser(SerializationInterface* serde, int version) override;
			virtual void de(SerializationInterface* serde, int version) override;

			void ApplyHH(Actor* actor, bool force);

			bool highheel_correction = true;
	};
}

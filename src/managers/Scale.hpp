#pragma once
// Module for the Gts Related code
#include <vector>
#include <atomic>
#include <unordered_map>

#include <RE/Skyrim.h>

#include "data/serde.hpp"
#include "events.hpp"
#include "node.hpp"
#include "util.hpp"

using namespace std;
using namespace RE;

namespace Gts {
	class ScaleManager : public EventListener, public Serde  {
		public:

			[[nodiscard]] static ScaleManager& GetSingleton() noexcept;

			virtual void Update() override;
			virtual void DataReady() override;

			virtual void ser(SerializationInterface* serde, int version) override;
			virtual void de(SerializationInterface* serde, int version) override;

			SizeMethod size_method = SizeMethod::ModelScale;
	};
}

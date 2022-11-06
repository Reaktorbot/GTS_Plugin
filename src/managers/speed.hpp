#pragma once
#include "events.hpp"
#include "data/serde.hpp"
// Module that handles actor speed changes

using namespace RE;
using namespace SKSE;

namespace Gts {
	class SpeedManager : public EventListener, public Serde {
		virtual void DataReady() override;
		virtual void Update() override;

		virtual void ser(SerializationInterface* serde, int version) override;
		virtual void de(SerializationInterface* serde, int version) override;

		bool is_speed_adjusted = true;
		SoftPotential speed_adjustment {
			.k = 0.125, // 0.125
			.n = 0.86, // 0.86
			.s = 1.12, // 1.12
			.o = 1.0,
			.a = 0.0,  //Default is 0
		};
		SoftPotential MS_adjustment {
			.k = 0.132, // 0.132
			.n = 0.86, // 0.86
			.s = 1.12, // 1.12
			.o = 1.0,
			.a = 0.0, //Default is 0
		};
	}
}

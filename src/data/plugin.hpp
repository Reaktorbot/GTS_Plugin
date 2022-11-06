#pragma once
// Keeps track of global state like is enabled
//

using namespace std;
using namespace RE;
using namespace SKSE;

namespace Gts {
	class Plugin : public EventListener, public Serde {
		public:
			static bool Enabled();
			static bool InGame();
			static void SetInGame(bool value);
			static bool OnMainThread();
			static void SetOnMainThread(bool value);

			virtual void DataReady() override;

			virtual void ser(SerializationInterface* serde, int version) override;
			virtual void de(SerializationInterface* serde, int version) override;

		private:
			[[nodiscard]] static Plugin& GetSingleton();
			std::atomic_bool enabled = std::atomic_bool(true);
			std::atomic_bool ingame = std::atomic_bool(false);
			std::atomic_bool onmainthread = std::atomic_bool(false);
	};
}

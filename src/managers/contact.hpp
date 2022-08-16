#pragma once
// Module that handles footsteps


using namespace std;
using namespace SKSE;
using namespace RE;

namespace Gts {
	class ContactListener : public ContactListener, public hkpWorldPostSimulationListener
	{

		public:
			void ContactPointCallback(const hkpContactPointEvent& a_event) override;

			void CollisionAddedCallback(const hkpCollisionEvent& a_event) override;

			void CollisionRemovedCallback(const hkpCollisionEvent& a_event) override;

			void PostSimulationCallback(hkpWorld* a_world) override;

			RE::NiPointer<RE::bhkWorld> world = nullptr;

			void Detach();
			void Attach(NiPointer<bhkWorld> world);
			static void EnsureLast();
			void SyncCameraCollisionGroups();
			void EnableBipedCollision();
	};

	class ContactManager {
		public:
			[[nodiscard]] static ContactManager& GetSingleton() noexcept;

			void Update();
			void UpdateCameraContacts();

			ContactListener listener{};
	};
}

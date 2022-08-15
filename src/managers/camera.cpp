#include "managers/camera.hpp"

#include "util.hpp"

using namespace SKSE;
using namespace RE;
using namespace REL;
using namespace Gts;

namespace Gts {
	CameraManager& CameraManager::GetSingleton() noexcept {
		static CameraManager instance;
		return instance;
	}

	void CameraManager::SetfOverShoulderPosX(float value) {
		auto camera = PlayerCamera::GetSingleton();
		if (camera) {
			TESCameraState* camera_state = camera->cameraStates[CameraStates::kThirdPerson];
			if (camera_state) {
				ThirdPersonState* third_person_state = static_cast<ThirdPersonState*>(camera_state);
				third_person_state->posOffsetExpected.x = value;
				third_person_state->Update();
			}
		}
	}
}

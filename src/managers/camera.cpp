#include "managers/camera.hpp"
#include "scale/scale.hpp"
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
			TESCameraState* camera_state = camera->cameraStates[CameraStates::kThirdPerson].get();
			if (camera_state) {
				ThirdPersonState* third_person_state = static_cast<ThirdPersonState*>(camera_state);
				third_person_state->posOffsetExpected.x = value;
			}
		}
	}
	void CameraManager::SetfOverShoulderPosY(float value) {
		auto camera = PlayerCamera::GetSingleton();
		if (camera) {
			TESCameraState* camera_state = camera->cameraStates[CameraStates::kThirdPerson].get();
			if (camera_state) {
				ThirdPersonState* third_person_state = static_cast<ThirdPersonState*>(camera_state);
				third_person_state->posOffsetExpected.y = value;
			}
		}
	}
	void CameraManager::SetfOverShoulderPosZ(float value) {
		auto camera = PlayerCamera::GetSingleton();
		if (camera) {
			TESCameraState* camera_state = camera->cameraStates[CameraStates::kThirdPerson].get();
			if (camera_state) {
				ThirdPersonState* third_person_state = static_cast<ThirdPersonState*>(camera_state);
				third_person_state->posOffsetExpected.z = value;
			}
		}
	}

	// Run every frame
	void CameraManager::Update() {
		auto player = PlayerCharacter::GetSingleton();
		float current_size = get_visual_scale(player);
		if (fabs(current_size - this->last_scale) > 1e-4) {
			this->OnScaleChanged(current_size, this->last_scale);
			this->last_scale = current_size;
		}
	}

	// Run when player size changes
	// Last known size is the size when this camera check was last
	// run
	void CameraManager::OnScaleChanged(float new_size, float last_known_size) {
	}
}

#include "managers/camera.hpp"
#include "scale/scale.hpp"
#include "util.hpp"
#include "data/runtime.hpp"
#include "data/persistent.hpp"

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

	float CameraManager::GetfOverShoulderPosZ(RE::Character* a_this) {
		auto camera = PlayerCamera::GetSingleton();
		if (camera) {
			TESCameraState* camera_state = camera->cameraStates[CameraStates::kThirdPerson].get();
			if (camera_state) {
				ThirdPersonState* third_person_state = static_cast<ThirdPersonState*>(camera_state);
				return third_person_state->posOffsetExpected.z;
			}
		}
	}

	float CameraManager::GetfOverShoulderPosX(RE::Character* a_this) {
		auto camera = PlayerCamera::GetSingleton();
		if (camera) {
			TESCameraState* camera_state = camera->cameraStates[CameraStates::kThirdPerson].get();
			if (camera_state) {
				ThirdPersonState* third_person_state = static_cast<ThirdPersonState*>(camera_state);
				return third_person_state->posOffsetExpected.x;
			}
		}
	}

	float CameraManager::GetfOverShoulderPosY(RE::Character* a_this) {
		auto camera = PlayerCamera::GetSingleton();
		if (camera) {
			TESCameraState* camera_state = camera->cameraStates[CameraStates::kThirdPerson].get();
			if (camera_state) {
				ThirdPersonState* third_person_state = static_cast<ThirdPersonState*>(camera_state);
				return third_person_state->posOffsetExpected.y;
			}
		}
	}

	// Run every frame
	void CameraManager::Update() {
		auto player = PlayerCharacter::GetSingleton();
		auto& runtime = Runtime::GetSingleton();
		bool ImProne = false;
		float current_size = get_visual_scale(player);
		float ScaleMethod = 0.0;
		SizeMethod method = Persistent::GetSingleton().size_method;

		if (method == SizeMethod::ModelScale) {
  			ScaleMethod = 0.0;
		}
		else if (method == SizeMethod::RootScale) {
  			ScaleMethod = 1.0;
		}
		else if (method == SizeMethod::RefScale) {
  			ScaleMethod = 2.0;
		}

		float EnableCamera = runtime.EnableCamera->value;
		float EnableAltCamera = runtime.EnableAltCamera->value;
    	float FeetCamera = runtime.FeetCamera->value;
    	float usingAutoDistance = runtime.usingAutoDistance->value;
    	float ImCrouching = runtime.ImCrouching->value;
		float MinDistance = runtime.MinDistance->value;
   		float MaxDistance = runtime.MaxDistance->value;
   	 	float CameraZoomSpeed = runtime.CameraZoomSpeed->value;
    	float CameraZoomPrecision = runtime.CameraZoomPrecision->value;
    //////////Normal - Prone
    	float proneCameraX = runtime.proneCameraX->value;
    	float proneCameraY = runtime.proneCameraY->value;
    	float proneCombatCameraX = runtime.proneCombatCameraX->value;
    	float proneCombatCameraY = runtime.proneCombatCameraY->value;
    /////////Normal - Normal
 	    float cameraX = runtime.cameraX->value;
   	 	float cameraY = runtime.cameraY->value;
   	 	float combatCameraX = runtime.combatCameraX->value;
   	 	float combatCameraY = runtime.combatCameraY->value;
//------------------------------------------------------------------------------------------------------------------------
    /////////Alternate - Prone
    	float proneCameraAlternateX = runtime.proneCameraAlternateX->value;
    	float proneCameraAlternateY = runtime.proneCameraAlternateY->value;
    	float proneCombatCameraAlternateX = runtime.proneCombatCameraAlternateX->value;
    	float proneCombatCameraAlternateY = runtime.proneCameraAlternateY->value;
    ////////Alternate - Normal
    	float cameraAlternateX = runtime.cameraAlternateX->value;
    	float cameraAlternateY = runtime.cameraAlternateY->value;
    	float combatCameraAlternateX = runtime.combatCameraAlternateX->value;
    	float combatCameraAlternateY = runtime.combatCameraAlternateY->value;


        if (ImCrouching >= 1.0){
            ImProne = true;
        }
        else {
            ImProne = false;
        }
		if (EnableCamera < 1.0)
		{return;}
		else
		if (MinDistance < -200)
        	{MinDistance = -200;}  
    	if (MaxDistance < 50)
       	    {MaxDistance = 50;}


		if (FeetCamera >= 1.0) // Adjustment for Feet Camera
    {
        //Utility.setINIFloat("fMouseWheelZoomIncrement:Camera", CameraZoomPrecision)
        //Utility.setINIFloat("fMouseWheelZoomSpeed:Camera", CameraZoomSpeed/2)
    if (player.isSneaking() == true && ImProne == true)
        {CameraManager::ApplyFeetCameraSettings(size, proneCameraAlternateX, proneCameraAlternateY, proneCombatCameraAlternateX, proneCombatCameraAlternateY, MinDistance, MaxDistance, usingAutoDistance, ImProne);}
        else
         {CameraManager::ApplyFeetCameraSettings(size, cameraAlternateX, cameraAlternateY, combatCameraAlternateX, combatCameraAlternateY, MinDistance, MaxDistance, usingAutoDistance, ImProne);}}

    else if (EnableAltCamera >= 1.0) // Adjustment for Alternate Camera 
    {
        //Utility.setINIFloat("fMouseWheelZoomIncrement:Camera", CameraZoomPrecision)
       // Utility.setINIFloat("fMouseWheelZoomSpeed:Camera", CameraZoomSpeed/2)
        if (player.isSneaking() == true && ImProne == true)
              {CameraManager::ApplyCameraSettings(size, proneCameraAlternateX, proneCameraAlternateY, proneCombatCameraAlternateX, proneCombatCameraAlternateY, MinDistance, MaxDistance, usingAutoDistance, ImProne);}
          else
             {CameraManager::ApplyCameraSettings(size, cameraAlternateX, cameraAlternateY, combatCameraAlternateX, combatCameraAlternateY, MinDistance, MaxDistance, usingAutoDistance, ImProne);}}          

   else if (EnableCamera >= 1.0) // Regular Camera
   {
    //Utility.setINIFloat("fMouseWheelZoomIncrement:Camera", CameraZoomPrecision);
    //Utility.setINIFloat("fMouseWheelZoomSpeed:Camera", CameraZoomSpeed/2);
        if (player.isSneaking() == true && ImProne == true)
            {CameraManager::ApplyCameraSettings(size, proneCameraX, proneCameraY, proneCombatCameraX, proneCombatCameraY, MinDistance, MaxDistance,usingAutoDistance, ImProne);}
        else
            {CameraManager::ApplyCameraSettings(size, cameraX, cameraY, combatCameraX, combatCameraY, MinDistance, MaxDistance, usingAutoDistance, ImProne);}}

    }	


		if (fabs(current_size - this->last_scale) > 1e-4) {
			this->OnScaleChanged(current_size, this->last_scale);
			this->last_scale = current_size;
		}
	

	// Run when player size changes
	// Last known size is the size when this camera check was last
	// run
	void CameraManager::OnScaleChanged(float new_size, float last_known_size) {
	}

}


namespace {
	using namespace Gts;

	void CameraManager::ApplyCameraSettings(size: float, X: float, Y: float, AltX: float, AltY: float, MinDistance: float, MaxDistance: float, usingAutoDistance:float, ImProne: bool)
	{float cameraYCorrection = 121.0;
	float Size = 1.0; float UpDown = 1.0;
    const CalcProne = runtime.CalcProne->value;

    CameraManager::SetfOverShoulderPosX(((X + Side) * size)); 
    CameraManager::SetfOverShoulderPosZ(((Y + UpDown) * size) - cameraYCorrection);

    //Utility.setINIFloat("fOverShoulderCombatPosX:Camera", ((AltX + Side) * size));
    //Utility.setINIFloat("fOverShoulderCombatPosZ:Camera", (((Y + UpDown) * size) - cameraYCorrection));

     CameraManager::SetfOverShoulderPosX(((X + Side) * size)); 
    CameraManager::SetfOverShoulderPosZ(((Y + UpDown) * size) - cameraYCorrection);

    //Utility.setINIFloat("fOverShoulderCombatPosX:Camera", ((AltX + Side) * size));
    //Utility.setINIFloat("fOverShoulderCombatPosZ:Camera", (((AltY + UpDown) * size) - cameraYCorrection2));
    if (usingAutoDistance <= 0.0)
    {
    //Utility.setINIFloat("fVanityModeMinDist:Camera", MinDistance * size);
    //Utility.setINIFloat("fVanityModeMaxDist:Camera", MaxDistance * size);
    }

    if (PlayerCharacter::GetSingleton().isSneaking() == true && ImProne == true)
    {
        float ProneCalc = CameraManager::GetfOverShoulderPosZ(); //Utility.getINIFloat("fOverShoulderPosZ:Camera") 
        float ProneCalcC = CameraManager::GetfOverShoulderPosZ(); //Utility.getINIFloat("fOverShoulderCombatPosZ:Camera")
        CameraManager::SetfOverShoulderPosZ(ProneCalc * CalcProne2); //Utility.setINIFloat("fOverShoulderPosZ:Camera", ProneCalc * CalcProne2)
        CameraManager::SetfOverShoulderPosZ(ProneCalc * CalcProne2); //Utility.setINIFloat("fOverShoulderCombatPosZ:Camera", ProneCalcC * CalcProne2)
    }}

	void CameraManager::ApplyFeetCameraSettings(size: float, X: float, Y: float, AltX: float, AltY: float, MinDistance: float, MaxDistance: float, usingAutoDistance:float, ImProne: bool)
	{
		float cameraYCorrection2 = 205.0 * (size * 0.33) + 70;
    	float CalcProne2 = runtime.CalcProne->value;
		float Size = 1.0; float UpDown = 1.0;
    
    CameraManager::SetfOverShoulderPosX(((X + Side) * size)); 
    CameraManager::SetfOverShoulderPosZ(((Y + UpDown) * size) - cameraYCorrection2);

    //Utility.setINIFloat("fOverShoulderCombatPosX:Camera", ((AltX + Side) * size));
    //Utility.setINIFloat("fOverShoulderCombatPosZ:Camera", (((AltY + UpDown) * size) - cameraYCorrection2));
    if (usingAutoDistance <= 0.0)
    {
    //Utility.setINIFloat("fVanityModeMinDist:Camera", MinDistance * size);
    //Utility.setINIFloat("fVanityModeMaxDist:Camera", MaxDistance * size);
    }

    if (PlayerCharacter::GetSingleton().isSneaking() == true && ImProne == true)
    {
        float ProneCalc = CameraManager::GetfOverShoulderPosZ(); //Utility.getINIFloat("fOverShoulderPosZ:Camera") 
        float ProneCalcC = CameraManager::GetfOverShoulderPosZ(); //Utility.getINIFloat("fOverShoulderCombatPosZ:Camera")
        CameraManager::SetfOverShoulderPosZ(ProneCalc * CalcProne2); //Utility.setINIFloat("fOverShoulderPosZ:Camera", ProneCalc * CalcProne2)
        CameraManager::SetfOverShoulderPosZ(ProneCalc * CalcProne2); //Utility.setINIFloat("fOverShoulderCombatPosZ:Camera", ProneCalcC * CalcProne2)
    }

	}
}
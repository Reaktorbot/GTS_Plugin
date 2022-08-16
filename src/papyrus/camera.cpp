#include "papyrus/camera.hpp"
#include "data/persistent.hpp"


using namespace SKSE;
using namespace Gts;
using namespace RE;
using namespace RE::BSScript;

namespace {
	constexpr std::string_view papyrus_class = "GtsCamera";

	void SetEnableCollisionActor(StaticFunctionTag* /*unused*/, bool enabled) {
		Persistent::GetSingleton().camera_collisions.enable_actor = enabled;
	}

	bool GetEnableCollisionActor(StaticFunctionTag* /*unused*/) {
		return Persistent::GetSingleton().camera_collisions.enable_actor;
	}

	void SetEnableCollisionTree(StaticFunctionTag* /*unused*/, bool enabled) {
		Persistent::GetSingleton().camera_collisions.enable_trees = enabled;
	}

	bool GetEnableCollisionTree(StaticFunctionTag* /*unused*/) {
		return Persistent::GetSingleton().camera_collisions.enable_trees;
	}

	void SetEnableCollisionDebris(StaticFunctionTag* /*unused*/, bool enabled) {
		Persistent::GetSingleton().camera_collisions.enable_debris = enabled;
	}

	bool GetEnableCollisionDebris(StaticFunctionTag* /*unused*/) {
		return Persistent::GetSingleton().camera_collisions.enable_debris;
	}

	void SetEnableCollisionTerrain(StaticFunctionTag* /*unused*/, bool enabled) {
		Persistent::GetSingleton().camera_collisions.enable_terrain = enabled;
	}

	bool GetEnableCollisionTerrain(StaticFunctionTag* /*unused*/) {
		return Persistent::GetSingleton().camera_collisions.enable_terrain;
	}

	void SetEnableCollisionStatic(StaticFunctionTag* /*unused*/, bool enabled) {
		Persistent::GetSingleton().camera_collisions.enable_static = enabled;
	}

	bool GetEnableCollisionStatic(StaticFunctionTag* /*unused*/) {
		return Persistent::GetSingleton().camera_collisions.enable_static;
	}

	void SetCollisionScale(StaticFunctionTag* /*unused*/, float scale) {
		Persistent::GetSingleton().camera_collisions.above_scale = scale;
	}

	float GetCollisionScale(StaticFunctionTag* /*unused*/) {
		return Persistent::GetSingleton().camera_collisions.above_scale;
	}
}

namespace Gts {
	bool RegisterPapyrusCamera(IVirtualMachine* vm) {
		vm->RegisterFunction("SetEnableCollisionActor", PapyrusClass, SetEnableCollisionActor);
		vm->RegisterFunction("GetEnableCollisionActor", PapyrusClass, GetEnableCollisionActor);
		vm->RegisterFunction("SetEnableCollisionTree", PapyrusClass, SetEnableCollisionTree);
		vm->RegisterFunction("GetEnableCollisionTree", PapyrusClass, GetEnableCollisionTree);
		vm->RegisterFunction("SetEnableCollisionDebris", PapyrusClass, SetEnableCollisionDebris);
		vm->RegisterFunction("GetEnableCollisionDebris", PapyrusClass, GetEnableCollisionDebris);
		vm->RegisterFunction("SetEnableCollisionTerrain", PapyrusClass, SetEnableCollisionTerrain);
		vm->RegisterFunction("GetEnableCollisionTerrain", PapyrusClass, GetEnableCollisionTerrain);
		vm->RegisterFunction("SetEnableCollisionStatic", PapyrusClass, SetEnableCollisionStatic);
		vm->RegisterFunction("GetEnableCollisionStatic", PapyrusClass, GetEnableCollisionStatic);
		vm->RegisterFunction("SetCollisionScale", PapyrusClass, SetCollisionScale);
		vm->RegisterFunction("GetCollisionScale", PapyrusClass, GetCollisionScale);

		return true;
	}
}

#pragma once
// Misc codes
#include <math.h>
#include <regex>

using namespace std;
using namespace RE;
using namespace SKSE;

namespace Gts {
	struct HitResult {
		const hkpShape* shape;
		float fraction;
	};

	class RayCollector : public hkpClosestRayHitCollector
	{
		public:
			void AddFilter(NiObject* obj) noexcept;
			bool IsFiltered(NiObject* obj);
			bool IsFilteredAv(NiAVObject* obj);
			void AddRayHit(const hkpCdBody& a_body, const hkpShapeRayCastCollectorOutput& a_hit_info) override;

			std::vector<NiObject*> object_filter;
			std::vector<HitResult> results;
			std::uint32_t filter = 0x40122716; // https://gitlab.com/Shrimperator/skyrim-mod-betterthirdpersonselection/-/blob/main/src/SmoothCamStuff/bhkLinearCastCollector.h
	};

	NiPoint3 CastRay(Actor* actor, NiPoint3 origin, NiPoint3 direction, float length, bool& success);
}

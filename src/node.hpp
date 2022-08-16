#pragma once
// Module that finds nodes and node realated data
using namespace std;
using namespace SKSE;
using namespace RE;

namespace Gts {
	void WalkNodes(Actor* actor);
	NiAVObject* FindNode(Actor* actor, std::string_view node_name, bool first_person = false);
	NiAVObject* FindNodeRegex(Actor* actor, std::string_view node_regex, bool first_person = false);
	NiAVObject* FindNodeAny(Actor* actor, std::string_view node_name);
	NiAVObject* FindNodeRegexAny(Actor* actor, std::string_view node_regex);
	void ScaleHkpnodes(Actor* actor, float prev_scale, float new_scale);
	void CloneBound(Actor* actor);
	BSBound* GetBound(Actor* actor);
	NiAVObject* GetBumper(Actor* actor);

	void UpdateNode(NiAVObject* node);
}

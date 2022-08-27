#include "Functions.h"
#include "InvincibleFrames.h"

namespace MaxsuIFrame
{
	static inline RE::hkbClipGenerator* ToClipGenerator(RE::hkbNode* a_node)
	{
		constexpr char CLASS_NAME[] = "hkbClipGenerator";

		if (a_node && a_node->GetClassType()) {
			if (_strcmpi(a_node->GetClassType()->name, CLASS_NAME) == 0)
				return skyrim_cast<RE::hkbClipGenerator*>(a_node);
		}

		return nullptr;
	}

	bool ActorInIFrames(const RE::Actor* a_actor)
	{
		if (!a_actor)
			return false;

		RE::BSAnimationGraphManagerPtr graphMgr;
		if (a_actor->GetAnimationGraphManager(graphMgr) && graphMgr) {
			auto behaviourGraph = graphMgr->graphs[0] ? graphMgr->graphs[0]->behaviorGraph : nullptr;
			auto activeNodes = behaviourGraph ? behaviourGraph->activeNodes : nullptr;
			if (activeNodes) {
				for (auto nodeInfo : *activeNodes) {
					auto nodeClone = nodeInfo.nodeClone;
					if (nodeClone && nodeClone->GetClassType()) {
						auto clipGenrator = ToClipGenerator(nodeClone);
						if (clipGenrator) {
							return ClipInIFrames(clipGenrator);
						}
					}
				}
			}
		}

		return false;
	}

	bool ClipInIFrames(const RE::hkbClipGenerator* a_clip)
	{
		if (!a_clip)
			return false;

		static constexpr std::string_view prefix = "SpecialFrames_Invincible";

		auto binding = a_clip ? a_clip->binding : nullptr;
		auto animation = binding ? binding->animation : nullptr;

		if (!animation || animation->annotationTracks.empty())
			return false;

		for (auto anno : animation->annotationTracks[0].annotations) {
			std::string_view text{ anno.text.c_str() };
			if (text.starts_with(prefix)) {
				try {
					auto j = json::parse(text.substr(prefix.size()));
					auto iFrames = j.get<InvincibleFrames>();
					iFrames.startTime = anno.time;
					if (iFrames.IsInFrames(a_clip->localTime))
						return true;
				} catch (json::exception& ex) {
					ERROR("Caught an expection when convert annoation: {}", ex.what());
					continue;
				}
			}
		}

		return false;
	}

}
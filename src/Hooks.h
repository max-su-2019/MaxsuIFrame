#pragma once
#include "Functions.h"

namespace MaxsuIFrame
{
	class IsGhostHook
	{
	public:
		static void InstallHook()
		{
			SKSE::AllocTrampoline(1 << 4);
			auto& trampoline = SKSE::GetTrampoline();
			_IsGhost = trampoline.write_call<5>(REL::RelocationID(37673, 38627).address() + REL::Relocate(0x45, 0x47), IsGhost);
			_IsGhost = trampoline.write_call<5>(REL::RelocationID(36715, 37725).address() + REL::Relocate(0x2A, 0x22), IsGhost);
			_IsGhost = trampoline.write_call<5>(REL::RelocationID(39428, 40504).address() + REL::Relocate(0x14, 0x14), IsGhost);
		}

	private:
		static bool IsGhost(const RE::Actor* a_actor)
		{
			DEBUG("IsGhost Trigger!");

			if (ActorInIFrames(a_actor)) {
				DEBUG("{}-{:x} In Annotations I-Frame!", a_actor->GetName(), a_actor->GetFormID());
				return true;
			}

			bool iframeActive = false, iframeSate = false;
			if (a_actor->GetGraphVariableBool("bIframeActive", iframeActive) && iframeActive && a_actor->GetGraphVariableBool("bInIframe", iframeSate) && iframeSate) {
				DEBUG("{}-{:x} In Behavior I-Frame!", a_actor->GetName(), a_actor->GetFormID());
				return true;
			}

			return _IsGhost(a_actor);
		}

		static inline REL::Relocation<decltype(IsGhost)> _IsGhost;
	};
}

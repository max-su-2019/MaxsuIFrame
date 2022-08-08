#pragma once

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
			logger::info("IsGhost Trigger!");

			bool iframeActive = false, iframeSate = false;

			if (a_actor->GetGraphVariableBool("bIframeActive", iframeActive) && iframeActive && a_actor->GetGraphVariableBool("bInIframe", iframeSate) && iframeSate) {
				logger::info("Actor is invulnerable!");
				return true;
			}

			return _IsGhost(a_actor);
		}

		static inline REL::Relocation<decltype(IsGhost)> _IsGhost;
	};
}

#pragma once
#include "nlohmann/json.hpp"

namespace MaxsuIFrame
{
	using json = nlohmann::json;

	struct InvincibleFrames
	{
	private:
		float startTime = 0.f;

		float duration = 0.f;

	public:
		bool IsInFrames(const float a_localTime) const;

		friend void from_json(const json& j, InvincibleFrames& a_iFrames);
		friend bool ClipInIFrames(const RE::hkbClipGenerator* a_clip);
	};

	void from_json(const json& j, InvincibleFrames& a_IFrames);
}
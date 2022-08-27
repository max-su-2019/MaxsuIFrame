#include "InvincibleFrames.h"

namespace MaxsuIFrame
{

	void from_json(const json& j, InvincibleFrames& a_iFrames)
	{
		j.at("Duration").get_to(a_iFrames.duration);
		a_iFrames.duration = max(a_iFrames.duration, 0.f);
	}

	bool InvincibleFrames::IsInFrames(const float a_localTime) const
	{
		return a_localTime >= startTime && a_localTime <= startTime + duration;
	}
}
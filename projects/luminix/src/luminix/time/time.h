#pragma once

#include "lxcore.h"
#include "maths.h"
#include "../window/window.h"

// basic frame manager

namespace Luminix {
	class LX_API Time {
	private:
		static double m_sLastFrameTime;
		static double m_sElapsedTime;
		static double m_sDeltaTime;
		static double m_sFrameTimeAccumulator;

		static uint32_t m_sTargetFrames;
		static uint32_t m_sFrameCount;
		static uint32_t m_sTotalFrames;

	public:
		static void Init();
		static void Update();

		static double GetDeltaTime() { return m_sDeltaTime; }
		static double GetElapsedTime() { return m_sElapsedTime; }
		static uint32_t GetTotalFrames() { return m_sTotalFrames; }
	};
}
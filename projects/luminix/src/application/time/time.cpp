
#include "lxpch.h"
#include "assertion.h"
#include "time.h"

namespace Luminix {
	double Time::m_sLastFrameTime = 0.0;
	double Time::m_sDeltaTime = 0.0;
	double Time::m_sElapsedTime = 0.0;
	double Time::m_sFrameTimeAccumulator = 0.0;

	uint32_t Time::m_sTargetFrames = 0;
	uint32_t Time::m_sFrameCount = 0;
	uint32_t Time::m_sTotalFrames = 0;

	void Time::Init() {
		m_sLastFrameTime = glfwGetTime();
		LX_ASSERT(m_sLastFrameTime != 0.0, "glfwGetTime failed! did you create GLFWwindow context first?");
	}

	void Time::Update() {
		double current_frame_time = glfwGetTime();
		m_sDeltaTime = current_frame_time - m_sLastFrameTime;

		m_sLastFrameTime = current_frame_time;
		m_sElapsedTime += m_sDeltaTime;

		m_sFrameCount++;
		m_sFrameTimeAccumulator += m_sDeltaTime;

		if (m_sFrameTimeAccumulator >= 1.0) {
			m_sTotalFrames = m_sFrameCount;
			m_sFrameCount = 0;
			m_sFrameTimeAccumulator -= 1.0;
		}
	}
}

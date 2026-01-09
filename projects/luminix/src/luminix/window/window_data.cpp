
#include "lxpch.h"
#include "window_data.h"

std::string GetVideoModeString(VideoMode vm) {
	switch (vm) {
	case VideoMode::Default: {
		return "Default";
		break;
	}

	case VideoMode::Windowed: {
		return "Windowed";
		break;
	}

	case VideoMode::Borderless: {
		return "Borderless";
		break;
	}

	case VideoMode::Fullscreen: {
		return "Fullscreen";
		break;
	}
	}
}
#pragma once

// must be included in one src file

#include "core/logger.h"
#include "luminix/application.h"

#if defined(LX_APP_PLATFORM_WINDOWS)

extern Luminix::Application* CreateApplication();

int main() {
	Core::Logger::Init();
	Core::Logger::AddLogger("Luminix");

	Luminix::Application* app = CreateApplication();
	app->Run();
	delete app;
}

#else
#error Your platform is currently not supported !
#endif
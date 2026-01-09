#pragma once

#include "application.h"

#if defined(LX_APP_PLATFORM_WINDOWS)

extern Luminix::Application* CreateApplication();

int main() {
	Luminix::Logger::Init();
	Luminix::Logger::CreateCoreLogger();

	Luminix::Application* app = CreateApplication();
	app->Run();
	delete app;
}

#else
#error Your platform is currently not supported !
#endif
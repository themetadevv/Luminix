

#include <iostream>
#include <format>

#include "Application/Window.h"
#include "Application/Input.h"
#include "Application/FrameManager.h"
#include "Application/Logger.h"

const std::string client_name = "Sandbox";

#define CLIENT_TRACE(...)    ::af::Logger::GetClient(client_name)->trace(__VA_ARGS__)
#define CLIENT_INFO(...)     ::af::Logger::GetClient(client_name)->info(__VA_ARGS__)
#define CLIENT_WARN(...)     ::af::Logger::GetClient(client_name)->warn(__VA_ARGS__)
#define CLIENT_ERROR(...)    ::af::Logger::GetClient(client_name)->error(__VA_ARGS__)
#define CLIENT_CRITICAL(...) ::af::Logger::GetClient(client_name)->critical(__VA_ARGS__)

int main() {
	
	WindowSpecs Specs;
	Specs.Title = "Siuu";
	Specs.Size = { 1600, 900 };
	Specs.Position = { 1600 / 2, 900 / 2 };
	Specs.State = WindowState::Maximized;
	Specs.VidMode = VideoMode::Windowed;
	Specs.VSync = true;

	af::Logger::Init();
	af::Logger::CreateCoreLogger();
	af::Logger::AddClient(client_name);

	Scope<af::Window> window = CreateScope<af::Window>(Specs);
	af::InputManager::Init(window->GetNativeWindowHandle());
	af::FrameManager::Init(window.get());

	while (window->IsRunning())
	{
		if (af::InputManager::KeyPressed(KeyCode::Escape))
			window->Shutdown();

		if (af::InputManager::KeyPressed(KeyCode::F11))
			window->SetVideoMode(VideoMode::Fullscreen);

		if (af::InputManager::KeyPressed(KeyCode::F10))
			window->SetVideoMode(VideoMode::Borderless);

		if (af::InputManager::KeyPressed(KeyCode::F9)) {
			window->SetVideoMode(VideoMode::Windowed);
		}	

		CLIENT_INFO("Client Count : {}", af::Logger::GetClientsCount());

		af::FrameManager::Update();
		window->Update();
		af::InputManager::Update();
	}

	af::Logger::DeleteClient(client_name);
	CLIENT_INFO("Client Count : {}", af::Logger::GetClientsCount());
}


#include <iostream>
#include <format>

#include "application/window/window.h"
#include "application/input/input.h"
#include "application/frames_manager.h"
#include "application/logger.h"

#include "application/audio/audio_device.h"
#include "application/audio/audio.h"

#include "application/ui/ui_context.h"
#include "application/ui/ui.h"

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
	Specs.Position = { 500, 300 };
	Specs.State = WindowState::Default;
	Specs.VidMode = VideoMode::Windowed;
	Specs.VSync = true;
	Specs.CustomHeader = false;

	af::Logger::Init();
	af::Logger::CreateCoreLogger();
	af::Logger::AddClient(client_name);

	Scope<af::window::Window> window = CreateScope<af::window::Window>(Specs);
	af::InputManager::Init(window->GetNativeWindowHandle());
	af::FrameManager::Init(window.get());

	std::vector<std::string> devices;
	af::GetAvailableSoundDevices(devices);

	Scope<af::AudioDevice> sound_dev = CreateScope<af::AudioDevice>(USE_DEFAULT_SOUND_DEVICE);

	af::ui::UISpecs ui_specs;
	ui_specs.Theme = af::ui::Theme::Dark;
	Scope<af::ui::UIContext> ui_ctx = CreateScope<af::ui::UIContext>(window.get(), ui_specs);

	af::Audio audio;
	bool audio_loaded = false;

	char path[256] = "";
	float gain = 0.0f;

	while (window->IsRunning())
	{
		ui_ctx->BeginRender();

		if (af::InputManager::KeyPressed(KeyCode::Escape))
			window->Shutdown();

		if (af::InputManager::KeyPressed(KeyCode::F11))
			window->SetVideoMode(VideoMode::Fullscreen);

		if (af::InputManager::KeyPressed(KeyCode::F10))
			window->SetVideoMode(VideoMode::Borderless);

		if (af::InputManager::KeyPressed(KeyCode::F9)) {
			window->SetVideoMode(VideoMode::Windowed);
		}

		af::ui::BeginUIContainer("Audio", nullptr);

		af::ui::InputText("Audio Path", path, sizeof(path));

		if (!audio_loaded) {
			if (af::ui::Button("Load Audio")) {
				if ((path[0] != '\0')) {
					audio = af::Audio::LoadAudio(path);
					audio_loaded = true;
				}
			}
		}
		
		af::ui::SliderFloat("Gain", &gain, 0.0f, 1.0f, "%.1f");


		if (audio_loaded) {
			if (af::ui::Button("Play")) {
				audio.SetGain(gain);
				audio.Play();
			}
		}

		af::ui::EndUIContainer();

		af::ui::BeginUIContainer("Device");

		std::string current_device_name = std::string(sound_dev->GetCurrentDeviceName());
		af::ui::Text(Color(255.f), current_device_name.c_str());

		if (af::ui::Button("Switch Device")) {
			if (current_device_name != devices[1]) {
				audio.Destroy();
				sound_dev->SetDevice(devices[1].c_str());
				sound_dev->SetContext();
			}
			else if (current_device_name != devices[0]) {
				audio.Destroy();
				sound_dev->SetDevice(devices[0].c_str());
				sound_dev->SetContext();
			}

			audio = af::Audio::LoadAudio(path);
		}

		af::ui::EndUIContainer();
		
		af::InputManager::Update();
		af::FrameManager::Update();
		ui_ctx->EndRender();
		window->Update();
	}

	af::Logger::DeleteClient(client_name);
}
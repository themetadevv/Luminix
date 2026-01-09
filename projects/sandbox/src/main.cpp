

#include <iostream>
#include <format>

#include "utils.h"

#include "core/file_system.h"

#include "luminix/application.h"
#include "luminix/entry.h"

#include "luminix/editor/editor.h"

#include "luminix/audio/audio_device.h"
#include "luminix/audio/audio.h"

// not optimal
class AudioManager : public Luminix::Layer {
private:
	std::vector<std::string> m_AudioDevices;
	std::string m_DeviceComboString;
	int m_AudioDeviceIndex = 0;
	std::vector<Luminix::Audio> m_Sounds;

public:
	AudioManager() : Layer("Audio Manager") 
	{ }

	~AudioManager() 
	{ }

	void OnAttach() override {
		m_AudioDevices.clear();
		Luminix::GetAvailableSoundDevices(m_AudioDevices);

		m_DeviceComboString.clear();
		for (const auto& device : m_AudioDevices) {
			m_DeviceComboString += device;
			m_DeviceComboString.push_back('\0');
		}
	}

	void OnEditorRender() override {
		Luminix::BeginUIContainer(this->GetLayerName().c_str(), nullptr);

		Luminix::Application& App = Luminix::Application::Get();

		std::string sound_device_name = std::string(App.GetAudioDevice().GetCurrentDeviceName());

		Luminix::Text(Color(255.0f), "Sound Device: %s", sound_device_name.c_str());

		if (Luminix::ComboBox("Sound Devices", &m_AudioDeviceIndex, m_DeviceComboString.c_str())) {
			for (auto& audios : m_Sounds) {
				audios.Destroy();
			}

			m_Sounds.clear();

			Luminix::Application& App = Luminix::Application::Get();
			App.GetAudioDevice().SetDevice(m_AudioDevices[m_AudioDeviceIndex].c_str());
			App.GetAudioDevice().SetContext();
		}

		static char v[256] = {};
		Luminix::InputText("Audio Path", v, sizeof(v));

		if (Luminix::Button("Load Sound")) {
			Luminix::Audio temp_sound = Luminix::Audio::LoadAudio(v, v);
			m_Sounds.emplace_back(std::move(temp_sound));
		}

		for (auto& sounds : m_Sounds) {
			std::string sound_name = std::string(sounds.GetAudioName());
			std::string play_button_name = "Play: " + std::string(Core::FileSystem::GetFileNameFromPath(sound_name.c_str()));
			std::string stop_button_name = "Stop: " + std::string(Core::FileSystem::GetFileNameFromPath(sound_name.c_str()));

			if (Luminix::Button(play_button_name.c_str())) {
				sounds.Stop();
				sounds.Play();
			}

			if (Luminix::Button(stop_button_name.c_str())) {
				sounds.Stop();
			}
		}

		Luminix::EndUIContainer();
	}
};

class Sandbox : public Luminix::Application {
public:
	Sandbox(const Luminix::ApplicationSetting& app_setting = Luminix::ApplicationSetting()) 
		: Application(app_setting)
	{
		AddLayer(new AudioManager());
	}
};

Luminix::Application* CreateApplication() {
	Luminix::ApplicationSetting AppSetting;
	AppSetting.AppName = "Sandbox";
	AppSetting.AppState = APP_STATE_DEFAULT;
	AppSetting.AppMode = APP_MODE_DEFAULT;
	AppSetting.AppVSync = LX_TRUE;

	return new Sandbox(AppSetting);
}
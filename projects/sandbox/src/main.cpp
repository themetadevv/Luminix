

#include <iostream>
#include <format>

#include "utils.h"
#include "application/application.h"
#include "application/EntryPoint.h"

#include "application/editor/editor.h"

#include "application/audio/audio_device.h"
#include "application/audio/audio.h"

class AudioManager : public Luminix::Layer {
private:
	Scope<Luminix::AudioDevice> m_AudioDevice;
	std::vector<Luminix::Audio> m_Sounds;
public:
	AudioManager() : Layer("Audio Manager") 
	{ }

	~AudioManager() 
	{ }

	void OnAttach() override {
		m_AudioDevice = CreateScope<Luminix::AudioDevice>(nullptr); // nullptr = default sound device
	}

	void OnEditorRender() override {
		Luminix::BeginUIContainer(this->GetLayerName().c_str(), nullptr);

		static char v[256] = {};
		Luminix::InputText("Audio Path", v, sizeof(v));

		if (Luminix::Button("Load Sound")) {
			Luminix::Audio temp_sound = Luminix::Audio::LoadAudio(v, v);
			m_Sounds.emplace_back(std::move(temp_sound));
		}

		for (auto& sounds : m_Sounds) {
			std::string sound_name = std::string(sounds.GetAudioName());
			std::string play_button_name = "Play: " + std::string(util::get_file_name_from_path(sound_name.c_str()));
			std::string stop_button_name = "Stop: " + std::string(util::get_file_name_from_path(sound_name.c_str()));

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
	return new Sandbox();
}
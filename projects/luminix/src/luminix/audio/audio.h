#pragma once

#include "core.h"
#include "maths.h"

#include "AL/al.h"

#include "audio_device.h"

namespace Luminix {
	class LX_API Audio {
	private:
		std::string m_AudioName;
		ALuint m_AudioBufferID;
		ALuint m_AudioSourceID;

		Audio(std::string_view audio_name, ALuint audio_buffer_id, ALuint audio_src_id);

	public:
		Audio(const Audio&) = delete;
		Audio& operator=(const Audio&) = delete;

		Audio(Audio&& other) noexcept;
		Audio& operator=(Audio&& other) noexcept;

		Audio(std::string_view audio_name) : m_AudioName(audio_name), m_AudioBufferID(0), m_AudioSourceID(0) {}
		~Audio();

		static Audio LoadAudio(std::string_view audio_name, std::string_view sound_path);
		std::string_view GetAudioName() const { return m_AudioName; }

		void Destroy();
		void SetPitch(float pitch = 1.0f);
		void SetGain(float gain = 1.0f);
		void SetLooping(bool loop = false);
		void SetPosition(const Vec3<float>& position = { 0.0f, 0.0f, 0.0f });
		void SetVelocity(const Vec3<float>& velocity = { 0.0f, 0.0f, 0.0f });	
		void Play();
		void Stop();

	private:
		static Audio LoadAudioDataFromWaveFile(std::string_view audio_name, std::string_view sound_path);
		static Audio LoadAudioDataFromMp3File(std::string_view audio_name, std::string_view sound_path);
	};
}
 
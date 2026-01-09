
#include "lxpch.h"
#include "assertion.h"

#include "audio_file_loader.h"
#include "audio_debug.h"
#include "audio.h"

namespace Luminix {
	enum class AudioFormat {
		None = 0,
		WAV,
		MP3
	};

	// static methods

	static AudioFormat GetFileFormat(std::string_view file_path) {
		std::filesystem::path path = file_path;
		std::string extension = path.extension().string();
		if (extension == ".wav" || extension == ".WAV")
			return AudioFormat::WAV;
		else if (extension == ".mp3" || extension == ".MP3")
			return AudioFormat::MP3;

		return AudioFormat::None;
	}

	static ALenum GetOpenALFormat_FromWavAudioFormat(WAVE_AUDIO& wave_audio_header) {
		ALenum format = AL_NONE;

		if (wave_audio_header.num_channels == 1 && wave_audio_header.bits_per_sample == 8)      
			format = AL_FORMAT_MONO8;
		else if (wave_audio_header.num_channels == 1 && wave_audio_header.bits_per_sample == 16) 
			format = AL_FORMAT_MONO16;
		else if (wave_audio_header.num_channels == 2 && wave_audio_header.bits_per_sample == 8)  
			format = AL_FORMAT_STEREO8;
		else if (wave_audio_header.num_channels == 2 && wave_audio_header.bits_per_sample == 16) 
			format = AL_FORMAT_STEREO16;
		else {
			LX_ERROR(
				"Unknown WAV format detected. Channels: {}, Bits per sample: {}"
				"Ensure the file is a proper WAV and has not been converted from any another audio format!\n",
				wave_audio_header.num_channels,
				wave_audio_header.bits_per_sample
			);
			format = AL_NONE;
		}

		return format;
	}

	static ALenum GetOpenALFormat_FromMp3AudioFormat(MP3_AUDIO& mp3_audio) {
		ALenum format = AL_NONE;

		if (mp3_audio.num_channels == 1)
			format = AL_FORMAT_MONO16;
		else if (mp3_audio.num_channels == 2)
			format = AL_FORMAT_STEREO16;
		else
		{
			LX_ERROR(
				"Unknown MP3 channel layout. Channels: {}",
				mp3_audio.num_channels
			);
			format = AL_NONE;
		}

		return format;
	}

	// Constructors/Destructors

	Audio::Audio(std::string_view audio_name, ALuint audio_buffer_id, ALuint audio_src_id) {
		m_AudioName = audio_name;
		m_AudioBufferID = audio_buffer_id;
		m_AudioSourceID = audio_src_id;
	}

	Audio::Audio(Audio&& other) noexcept {
		m_AudioName = other.m_AudioName;
		m_AudioBufferID = other.m_AudioBufferID;
		m_AudioSourceID = other.m_AudioSourceID;

		other.m_AudioName.clear();
		other.m_AudioBufferID = 0;
		other.m_AudioSourceID = 0;
	}

	Audio& Audio::operator=(Audio&& other) noexcept {
		if (this == &other)
			return *this;

		Destroy();

		m_AudioName = other.m_AudioName;
		m_AudioBufferID = other.m_AudioBufferID;
		m_AudioSourceID = other.m_AudioSourceID;

		other.m_AudioName.clear();
		other.m_AudioBufferID = 0;
		other.m_AudioSourceID = 0;

		return *this;
	}

	Audio::~Audio() {
		Destroy();
	}

	// static Load Audio function
	Audio Audio::LoadAudio(std::string_view audio_name, std::string_view sound_path) {
		AudioFormat audio_file_format = GetFileFormat(sound_path);

		switch (audio_file_format) {
			case AudioFormat::WAV: return LoadAudioDataFromWaveFile(audio_name, sound_path);
			case AudioFormat::MP3: return LoadAudioDataFromMp3File(audio_name, sound_path);
		}

		LX_ASSERT(false, "Unsupported audio format: {}", sound_path);
		return { audio_name, 0, 0};
	}

	// Audio Functions
	void Audio::Destroy() {
		if (m_AudioSourceID != 0) {
			alCall(alDeleteSources(1, &m_AudioSourceID));
			m_AudioSourceID = 0;
		}
			
		if (m_AudioBufferID != 0) {
			alCall(alDeleteBuffers(1, &m_AudioBufferID));
			m_AudioBufferID = 0;
		}
	}

	void Audio::SetPitch(float pitch) {
		alCall(alSourcef(m_AudioSourceID, AL_PITCH, pitch));
	}

	void Audio::SetGain(float gain) {
		alCall(alSourcef(m_AudioSourceID, AL_GAIN, gain));
	}

	void Audio::SetLooping(bool loop) {
		alCall(alSourcef(m_AudioSourceID, AL_LOOPING, loop));
	}

	void Audio::SetPosition(const Vec3<float>& position) {
		alCall(alSource3f(m_AudioSourceID, AL_POSITION, position.x, position.y, position.z));
	}

	void Audio::SetVelocity(const Vec3<float>& velocity) {
		alCall(alSource3f(m_AudioSourceID, AL_VELOCITY, velocity.x, velocity.y, velocity.z));
	}

	void Audio::Play() {
		ALint src_state = AL_NONE;
		alCall(alGetSourcei(m_AudioSourceID, AL_SOURCE_STATE, &src_state));

		if (src_state != AL_PLAYING) {
			alCall(alSourcePlay(m_AudioSourceID));
		}
	}

	void Audio::Stop() {
		ALint src_state = AL_NONE;
		alCall(alGetSourcei(m_AudioSourceID, AL_SOURCE_STATE, &src_state));

		if (src_state == AL_PLAYING) {
			alCall(alSourceStop(m_AudioSourceID));
		}
	}

	// Getting Audio Data functions
	Audio Audio::LoadAudioDataFromWaveFile(std::string_view audio_name, std::string_view sound_path) {
		WAVE_AUDIO wave_audio_header_data;
		std::vector<char> wave_raw_audio_data;
		bool load_wave = LoadWave(sound_path, &wave_audio_header_data, wave_raw_audio_data);
		LX_ASSERT(load_wave != false, "Luminix::LoadWave Call Failed! for: {}", sound_path);

		ALuint audio_buffer;
		alCall(alGenBuffers(1, &audio_buffer));
		alCall(alBufferData(
			audio_buffer,
			GetOpenALFormat_FromWavAudioFormat(wave_audio_header_data),
			wave_raw_audio_data.data(), wave_raw_audio_data.size(),
			wave_audio_header_data.sample_rate
		));
		wave_raw_audio_data.clear();

		ALuint source_handle;
		alCall(alGenSources(1, &source_handle));
		alCall(alSourcei(source_handle, AL_BUFFER, audio_buffer));

		Audio gen_src = { audio_name, audio_buffer, source_handle };
		return gen_src;
	}

	Audio Audio::LoadAudioDataFromMp3File(std::string_view audio_name, std::string_view sound_path) {
		MP3_AUDIO mp3_audio_info;
		int size;
		bool load_mp3_audio = LoadMP3(sound_path, &mp3_audio_info, size);
		LX_ASSERT(load_mp3_audio != false, "Luminix::LoadMP3 Call Failed! for: {}", sound_path);

		ALuint audio_buffer;
		alCall(alGenBuffers(1, &audio_buffer));
		alCall(alBufferData(
			audio_buffer,
			GetOpenALFormat_FromMp3AudioFormat(mp3_audio_info),
			mp3_audio_info.buffer, size,
			mp3_audio_info.sample_rate
		));

		ALuint source_handle;
		alCall(alGenSources(1, &source_handle));
		alCall(alSourcei(source_handle, AL_BUFFER, audio_buffer));

		Audio gen_src = { audio_name, audio_buffer, source_handle };
		return gen_src;
	}

}
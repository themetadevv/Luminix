
#include "lxpch.h"
#include "assertion.h"

#include "audio_debug.h"
#include "audio_file_loader.h"

#define MINIMP3_IMPLEMENTATION
#define MINIMP3_ONLY_MP3
#include <minimp3.h>
#include <minimp3_ex.h>

namespace Luminix {
	bool LoadWave(std::string_view audio_path, WAVE_AUDIO* wave_audio_header, std::vector<char>& pcm) {
		if (!std::filesystem::exists(audio_path)) {
			LX_ERROR("Failed to locate '.wav' file '{}'. The file does not exists at the specified path!", audio_path);
			return false;
		}

		std::ifstream audio_file(std::string(audio_path), std::ios::binary);

		if (!audio_file.is_open()) {
			LX_ERROR("Failed to load '.wav' audio file '{}'. file may be corrupted, or lack read permissions!", audio_path);
			return false;
		}

		audio_file.read(reinterpret_cast<char*>(wave_audio_header), sizeof(WAVE_AUDIO));

		if (std::memcmp(wave_audio_header->chunk_id, "RIFF", 4) != 0 || std::memcmp(wave_audio_header->format, "WAVE", 4) != 0) {
			LX_ERROR(
				"WAV header validation failed\n"
				"Path: '{}'\n"
				"Expected: RIFF / WAVE identifiers\n",
				audio_path
			);
			return false;
		}

		pcm.clear();
		pcm.resize(wave_audio_header->sub_chunk2_size);
		audio_file.read(reinterpret_cast<char*>(pcm.data()), pcm.size());

		audio_file.close();
		return true;
	}

	static mp3dec_t s_Mp3d;

	bool LoadMP3(std::string_view audio_path, MP3_AUDIO* mp3_file_info, int& pcm_size) {
		if (!std::filesystem::exists(audio_path)) {
			LX_ERROR("Failed to locate '.mp3' file '{}'. The file does not exists at the specified path!", audio_path);
			return false;
		}

		std::string path = std::string(audio_path);
		mp3dec_file_info_t info;
		int load_mp3 = mp3dec_load(&s_Mp3d, path.c_str(), &info, NULL, NULL);

		if (load_mp3 != 0) {
			LX_ERROR("Failed to load '.mp3' audio file '{}'. file may be corrupted, or lack read permissions!", audio_path);
			return false;
		}

		if (!info.buffer) {
			LX_ERROR("null buffer*: {}", audio_path);
			return false;
		}
			
		mp3_file_info->buffer = info.buffer;
		mp3_file_info->samples = info.samples;
		mp3_file_info->num_channels = info.channels;
		mp3_file_info->sample_rate = info.hz;
		mp3_file_info->layer = info.layer;
		mp3_file_info->avg_bitrate_kbps = info.avg_bitrate_kbps;

		pcm_size = mp3_file_info->samples * sizeof(mp3d_sample_t);
		return true;
	}

}


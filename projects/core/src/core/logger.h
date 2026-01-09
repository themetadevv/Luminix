#pragma once

#include "def.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Core {
	class CORE_API Logger {
	private:
		static std::vector<spdlog::sink_ptr> m_LogSinks;
		static std::unordered_map<std::string, std::shared_ptr<spdlog::logger>> m_sLoggers;

	public:
		static void Init();
		static bool AddLogger(std::string_view client_name);
		static bool DeleteLogger(std::string_view client_name);

		static std::shared_ptr<spdlog::logger>& GetLogger(std::string_view client_name) {
			auto client = m_sLoggers.find(std::string(client_name));
			if (client == m_sLoggers.end()) {
				std::cout << "Failed to get client: " << client_name << '\n';
				__debugbreak();
			}

			if (client->second == nullptr) {
				std::cout << "Core::Logger::GetClientLogger Call failed! Did u initialized the client logger for your client ?\n";
				__debugbreak();
			}

			return client->second;
		}
	};
}

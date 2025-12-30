#pragma once

#include "core.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>


namespace af {
	class AF_API Logger {
	private:
		static std::vector<spdlog::sink_ptr> m_LogSinks;
		static Ref<spdlog::logger> m_sCoreLogger;
		static std::unordered_map<std::string, Ref<spdlog::logger>> m_sClients;

		static uint32_t m_sClientsCount;

	public:
		static void Init();
		static bool CreateCoreLogger();
		static bool AddClient(std::string_view client_name);
		static bool DeleteClient(std::string_view client_name);

		static Ref<spdlog::logger>& GetCoreLogger() { 
			if (m_sCoreLogger == nullptr) {
				std::cout << "GetFrameworkLogger failed! Did u initialized the framework logger first ?\n";
				__debugbreak();
			}
			return m_sCoreLogger;
		}

		static Ref<spdlog::logger>& GetClient(std::string_view client_name) {
			auto client = m_sClients.find(std::string(client_name));
			if (client == m_sClients.end()) {
				std::cout << "Failed to get client: " << client_name << '\n';
				__debugbreak();
			}

			if (client->second == nullptr) {
				std::cout << "GetClientLogger failed! Did u initialized the client logger for your client ?\n";
				__debugbreak();
			}

			return client->second;
		}

		static uint32_t GetClientsCount() { return m_sClientsCount; }
	};
}

#ifdef ENABLE_LOGGING
	#define AF_TRACE(...)    ::af::Logger::GetCoreLogger()->trace(__VA_ARGS__)
	#define AF_INFO(...)     ::af::Logger::GetCoreLogger()->info(__VA_ARGS__)
	#define AF_WARN(...)     ::af::Logger::GetCoreLogger()->warn(__VA_ARGS__)
	#define AF_ERROR(...)    ::af::Logger::GetCoreLogger()->error(__VA_ARGS__)
	#define AF_CRITICAL(...) ::af::Logger::GetCoreLogger()->critical(__VA_ARGS__)
#else
	#define AF_TRACE(...)
	#define AF_INFO(...)
	#define AF_WARN(...)
	#define AF_ERROR(...)
	#define AF_CRITICAL(...)
#endif


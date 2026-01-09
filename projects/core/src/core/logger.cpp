
#include "corepch.h"
#include "logger.h"

namespace Core {	
	// static members 

	std::vector<spdlog::sink_ptr> Logger::m_LogSinks = {};
	std::unordered_map<std::string, std::shared_ptr<spdlog::logger>> Logger::m_sLoggers = {};

	// static methods

	void Logger::Init() {
		m_LogSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		m_LogSinks[0]->set_pattern("%^[%T] %n: %v%$");
	}

	bool Logger::AddLogger(std::string_view client_name) {
		if (m_sLoggers.contains(std::string(client_name))) {
			std::cout << "Logger '{}' already exists. Creation request ignored." << client_name << '\n';
			return false;
		}

		if (m_LogSinks.empty()) {
			std::cout << "Core::Logger::CreateLogger() Call failed, Did you call Core::Logger::Init() ?" << client_name << '\n';
			return false;
		}

		auto logger = std::make_shared<spdlog::logger>(std::string(client_name), begin(m_LogSinks), end(m_LogSinks));

		spdlog::register_logger(logger);
		logger->set_level(spdlog::level::trace);
		logger->flush_on(spdlog::level::trace);
		m_sLoggers.emplace(client_name, logger);

		return true;
	}

	bool Logger::DeleteLogger(std::string_view client_name) {
		std::string name = std::string(client_name);
		if (!m_sLoggers.contains(name)) {
			std::cout << "Luminix::Logger::DeleteClient() Call failed: client logger '{}' does not exist!" << client_name << '\n';
			return false;
		}
		
		spdlog::drop(name);
		m_sLoggers.erase(name);

		return true;
	}
}


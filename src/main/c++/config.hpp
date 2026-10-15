/**
 * config.hpp
 */
 
#pragma once

#include <string>

class Config {
public:
	inline int getHttpPort() const {
		return std::stoi(getRequiredEnv("HTTP_PORT"));
	}
	inline std::string getDatabaseHost() const {
		return getRequiredEnv("DB_HOST");
	}
	inline std::string getDatabasePort() const {
		return getRequiredEnv("DB_PORT");
	}
	inline std::string getDatabase() const {
		return getRequiredEnv("DB_DATABASE");
	}
	inline std::string getDatabaseUser() const {
		return getRequiredEnv("DB_USER");
	}
	inline std::string getDatabasePassword() const {
		return getRequiredEnv("DB_PASSWORD");
	}
	inline std::string getSslKeyPath() const {
		return getRequiredEnv("SSL_KEY_PATH");
	}
	inline std::string getSslCetrificatePath() const {
		return getRequiredEnv("SSL_CERT_PATH");
	}
	
private:
	static std::string getRequiredEnv(const char *name);
};


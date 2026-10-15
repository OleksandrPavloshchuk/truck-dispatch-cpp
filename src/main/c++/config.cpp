/**
 * config.cpp
 */
 
#include <iostream> 
 
#include "config.hpp"

std::string Config::getRequiredEnv(const char *name) {
    const char *value = std::getenv(name);
    if (value == nullptr || *value == '\0') {
        throw std::runtime_error(
            std::string("Required environment variable is not set: ") + name
        );
    }
    return value;
}

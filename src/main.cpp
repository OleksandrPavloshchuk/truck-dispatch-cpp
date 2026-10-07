/**
 * main.cpp
 */
 
#include <string>
#include <iostream>
#include <drogon/drogon.h>

using Callback = std::function<void(const drogon::HttpResponsePtr&)>;

// Get required parameter from configuration:
std::string getRequiredEnv(const char *name) {
    const char *value = std::getenv(name);

    if (value == nullptr || *value == '\0') {
        throw std::runtime_error(
            std::string("Required environment variable is not set: ") + name
        );
    }

    return value;
}

// Entry point:
int main() {

	const int port = std::stoi(getRequiredEnv("HTTP_PORT"));
	
	std::cout << "Configuration:" << std::endl;
	std::cout << "\tHTTP port: " << port << std::endl;
	

	drogon::app()
		.addListener("0.0.0.0", port)
		.registerHandler("/hello", 
			[](const drogon::HttpRequestPtr &request, Callback &&callback) {
				auto response = drogon::HttpResponse::newHttpResponse();
				response->setBody("Hello drogon!");
				callback(response);
			}
		)
		.run();

	return 0;
}

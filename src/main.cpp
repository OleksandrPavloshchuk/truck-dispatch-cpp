/**
 * main.cpp
 */
 
#include <drogon/drogon.h>

using Callback = std::function<void(const drogon::HttpResponsePtr&)>;

int main() {

	drogon::app()
		.addListener("0.0.0.0", 3001)
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

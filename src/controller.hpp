/**
 * controller.hpp
 */
 
#pragma once

#include <string>
#include <variant>
#include <drogon/drogon.h>

using Callback = std::function<void(const drogon::HttpResponsePtr&)>;

class Controller {
public:
	void handle(const drogon::HttpRequestPtr& request, Callback &&callback);
protected:
	virtual bool validate(const Json::Value &json) = 0;
	virtual void doHandle(const Json::Value &src, Callback &callback) = 0;
private:
	void invalidJson(Callback &callback);
	void invalidInput(Callback &callback);
};

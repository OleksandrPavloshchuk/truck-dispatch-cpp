/**
 * metrics.cpp
 */
 
#include "metrics.hpp"
 
const std::string TEMPLATE = R"(
# HELP td_shipments_created_total Total created shipments.
# TYPE td_shipments_created_total counter
td_shipments_created_total )";

std::string getDatabaseMetrics(const DatabaseMetrics &metrics) {
	return TEMPLATE + std::to_string(metrics.shipmentsTotal_) + "\n";
}

void MetricsController::handle(Callback &&callback) {

	LOG_DEBUG << "MetricsController::handle";

	service_.getDatabaseMetrics(
		[this, callback](const DatabaseMetrics &metrics) mutable {
			success(metrics, callback);
		},
		[this, callback](const std::string &error) mutable {
		    databaseError(error, callback);
		}		
	);
	
}

void MetricsController::success(const DatabaseMetrics &metrics, Callback &callback) {
	auto response = drogon::HttpResponse::newHttpResponse();
	response->setStatusCode(drogon::k200OK);
	response->setContentTypeCode(drogon::CT_TEXT_PLAIN);
	response->setBody(getDatabaseMetrics(metrics));
	callback(response);	
}

void MetricsController::databaseError(const std::string &error, Callback &callback) {
	auto response = drogon::HttpResponse::newHttpResponse();
	response->setStatusCode(drogon::k500InternalServerError);
	response->setContentTypeCode(drogon::CT_TEXT_PLAIN);
	response->setBody("Database error: " + error);
        callback(response);
}

/*
# HELP td_shipments_created_total Total created shipments.
# TYPE td_shipments_created_total counter
td_shipments_created_total 42
*/

/*

#include <sstream>

std::string getMetrics(long total) {
    std::ostringstream out;

    out << "# HELP td_shipments_total Total shipments.\n"
        << "# TYPE td_shipments_total gauge\n"
        << "td_shipments_total " << total << '\n';

    return out.str();
}

*/


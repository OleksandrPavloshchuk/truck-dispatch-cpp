/**
 * metrics.cpp
 */
 
#include "metrics.hpp"

const std::string TEMPLATE = R"(
# HELP td_shipments_created_total Total created shipments.
# TYPE td_shipments_created_total counter
td_shipments_created_total )";

std::string getMetrics(long total) {
	return TEMPLATE + std::to_string(total) + "\n";
}

void MetricsController::handle(Callback &&callback) {

	service_.getShipmentsTotal(
		[this, callback](long shipmentsTotal) mutable {
			success(shipmentsTotal, callback);
		},
		[this, callback](const std::string &error) mutable {
		    databaseError(error, callback);
		}		
	); 	
}

void MetricsController::success(long shipmentsTotal, Callback &callback) {
	auto response = drogon::HttpResponse::newHttpResponse();
	response->setStatusCode(drogon::k200OK);
	response->setContentTypeCode(drogon::CT_TEXT_PLAIN);
	response->setBody( getMetrics(shipmentsTotal));
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


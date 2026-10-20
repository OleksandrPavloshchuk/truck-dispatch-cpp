/**
 * metrics.cpp
 */
 
#include "metrics.hpp"

std::string getDatabaseMetrics(const DatabaseMetrics &metrics) {
    std::ostringstream out;

    out 
    	<< "# HELP td_shipments_total Total shipments.\n"
        << "# TYPE td_shipments_total gauge\n"
        << "td_shipments_total " << metrics.shipmentsTotal_ << '\n'
    	<< "# HELP td_trucks_total Total trucks.\n"
        << "# TYPE td_trucks_total gauge\n"
        << "td_trucks_total " << metrics.trucksTotal_ << '\n'
    	<< "# HELP td_assignments_total Total assignments.\n"
        << "# TYPE td_assignments_total gauge\n"
        << "td_assignments_total " << metrics.assignmentsTotal_ << '\n';

    return out.str();
}

void MetricsController::handle(Callback &&callback) {
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

